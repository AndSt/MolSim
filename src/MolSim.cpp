#include "outputWriter/VTKWriter.h"
#include "FileReader.h"

#include "Particle.h"
#include "Cuboid.h"
#include "Sphere.h"

#include "utils/Vector.h"
#include "utils/ParticleContainer.h"
#include "utils/ParticleIterator.h"
#include "utils/ParticleGenerator.h"
#include "utils/LCParticleContainer.h"
#include "utils/LCInnerParticleIterator.h"
#include "utils/LCOuterParticleIterator.h"
#include "utils/Thermostat.h"
#include "utils/BoundaryHandler.h"

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

#include "tests/ParticleIteratorTest.h"
#include "tests/ParticleContainerTest.h"
#include "tests/ParticleGeneratorTest.h"
#include "tests/LCParticleContainerTest.h"
#include "tests/LCInnerParticleIteratorTest.h"
#include "tests/LCOuterParticleIteratorTest.h"
#include "tests/ThermostatTest.h"
#include "tests/FileReaderTest.h"
#include "tests/MembraneTest.h"

#include <list>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <sys/time.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**** forward declaration of the calculation functions ****/

void simulate();
void LCsimulate();

/**
 * calculate the force for all particles, according to Lennard-Jones
 */
void calculateFLJ();
void LCcalculateFLJ();

/**
 * calculate the position for all particles
 */
void calculateX();
void LCcalculateX();

/**
 * calculate the velocity for all particles
 */
void calculateV();
void LCcalculateV();

void computeForce(Particle* p1, Particle* p2);

void getIntegerInput(string &str, int &input);

void getDoubleInput(string &str, double &input);

void resizeEpsSig(int inSize);

void fillEpsSig(int inSize);

// plot the particles to VTKWriter-File
void plotVTK(int iteration);
void LCplotVTK(int iteration);

void writeOutputFile(list<Particle *> parList);

double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;

//{InputCuboids, InputParticles, InputSpheres}
list<string> inputNames;

//{cuboids, particles, spheres}
list<string> inputTypes;

string outputMask = "MD_vtk";
int freq = 10;

// For Linked Cell Algorithm
double R_CUTOFF = 3.0;
utils::Vector<double, 3> domainSize;
bool outflow_flag = false;
const double h = 1.2;
int depth = 0;

// For gravity
bool gravity = false;
vector<double> mass;
double G_CONST = -12.44;
//only for cuboids and spheres, not for particles alone
//type = index
double gDirMass[] = { 0.0, 1.0, 0.0 }; //will store mass (without G_CONST*)
vector<utils::Vector<double, 3> > gravForce;
vector<vector<double> > EPS;
vector<vector<double> > SIG;

// For membrane
double current_time = 0.0;
double k = 300;
double rDirect = 2.2;
double rDiag = 2.2*sqrt(2);
double rFLJ = pow(2, 1.0/6.0);
double FZUpArr[] = {0.0, 0.0, 0.8};
utils::Vector<double, 3> FZUp(FZUpArr);
int id1, id2, id3, id4;
bool isMembrane = false;

int inputSize = 0;
list<Particle*> particleList;
utils::ParticleContainer container;
utils::ParticleGenerator pgen;
utils::LCParticleContainer lcContainer;

vector<int> domainCondition;
// 0: left	1: right
// 2: ground/lower	3:upper
// 4: front	5: behind/gear
// Value: 1 = outflow, 2= reflecting
// 3 = periodic

string fileName;

//used to check the length of the simulation
struct timeval tim;
double t1;

// Thermostat option: only called when thermo.getEnabled() == true
Thermostat thermo;

log4cxx::LoggerPtr molsimlogger(log4cxx::Logger::getLogger("molsim"));

/**
 * @param argsv the first parameter is the file. ( here "eingabe-sonne.txt")
 * The second parameter is the end_time.
 * The third parameter is delta_t.
 */
int main(int argc, char* argsv[]) {

	//for membrane test
	/*
	std::string fileName = "src/tests/testFiles/TestMembrane.xml";
	char *cstr = new char[fileName.length() + 1];
	strcpy(cstr, fileName.c_str());

	pgen.extractCuboids(cstr);
	Cuboid cub = *pgen.getCuboidList().begin();
	*/

	Particle p1(utils::Vector<double, 3>(0.0), utils::Vector<double, 3>(0.0), 0.1, 0, 100);
	Particle p2(utils::Vector<double, 3>(0.0), utils::Vector<double, 3>(0.0), 0.1, 0, 200);
	cout << p1 << endl;
	cout << p2 << endl;
	std::list<Particle *> pp;
	pp.push_back(&p1);
	pp.push_back(&p2);
	std::list<Particle *>::iterator i0 = pp.begin();
	cout << "list:\n" << **i0 << endl;
	i0++;
	cout << **i0 << endl << endl;

	cin.ignore();
	Cuboid cub1(5, 5, 1, 1.0, 1.0,
			utils::Vector<double, 3>((double) 0), utils::Vector<double, 3>((double) 0),
			0.1, 0, 1.0, 5.0);
	//cub.initNeighbors();
	std::list<Particle *> li = cub1.getCuboid();
	li.push_back(&p1);
	std::list<Particle *>::iterator it = li.begin();
	cout << "now:\n" << *it << endl;
	it++;
	cout << *it << endl;
	it++;
	cout << *it << endl;

	for (std::list<Particle *>::iterator it = li.begin();
			it != li.end(); it++){
		cout << **it << endl;
	}
	return 0;
	//end of test membrane

	PropertyConfigurator::configure("Log4cxxConfig.cfg");
	LOG4CXX_INFO(molsimlogger, "Arrived @ main.");

	/* Format input command line:
	 *
	 * ./MolSim								: normal running
	 *
	 * ./MolSim --test						: for test
	 *
	 * ./MolSim --falling-drop-init			: for initilization of falling drop experiment
	 *
	 * ./MolSim --falling-drop-end			: for the falling drop experiment
	 *
	 * ./MolSim --rayleigh-taylor-small		: for the small Rayleigh-Taylor experiment
	 *
	 * ./MolSim --rayleigh-taylor-big		: for the big Rayleigh-Taylor experiment
	 */

	//bool test = false;
	gettimeofday(&tim, NULL);
	t1 = tim.tv_sec + (tim.tv_usec / 1000000.0);
	if (argc > 2) {
		cout << "Maximal 2 arguments." << endl;
		return -1;
	}

	if (argc == 2) {
		string arg1 = argsv[1];
		if (arg1 == "--test") {
			/*
			 * "Testing suite": Read in the Options and run the TestRunner
			 */
			LOG4CXX_INFO(molsimlogger, "Arrived @ testsuite.");

			string str;
			int option = 0;

			cout << "Here are the testing options: " << endl;
			cout
					<< "Tipp: If you Enter Option '1' or '2' you will get back to this menu";
			cout << endl << endl;
			while (option != 3) {
				cout << "Enter '1', if you want to test all unit tests."
						<< endl;
				cout << "Enter '2', if you want to test a specific unit test."
						<< endl;
				cout << "Enter '3', if you want to exit the 'test suite'."
						<< endl;
				cout << endl;

				//Check for correct input
				getIntegerInput(str, option);

				if (option == 1) {

					CppUnit::TextUi::TestRunner runner;
					runner.addTest(ParticleIteratorTest::suite());
					runner.addTest(ParticleContainerTest::suite());
					runner.addTest(ParticleGeneratorTest::suite());
					runner.addTest(LCParticleContainerTest::suite());
					runner.addTest(LCInnerParticleIteratorTest::suite());
					runner.addTest(LCOuterParticleIteratorTest::suite());
					runner.addTest(ThermostatTest::suite());
					runner.addTest(FileReaderTest::suite());
					runner.addTest(MembraneTest::suite());
					runner.run();

				} else if (option == 2) {
					cout
							<< "Enter '1', if you want to test the ParticleContainer."
							<< endl;
					cout
							<< "Enter '2', if you want to test the ParticleIterator."
							<< endl;
					cout
							<< "Enter '3', if you want to test the ParticleGenerator."
							<< endl;
					cout << "Enter '4', if you want to test the Thermostat."
							<< endl;
					cout << "Enter '5', if you want to test the FileReader."
							<< endl;
					cout << "Enter '6', if you want to test the Membrane functions."
							<< endl;

					//Check for correct input
					int opT;
					getIntegerInput(str, opT);

					CppUnit::TextUi::TestRunner runner;
					switch (opT) {
					case 1:
						runner.addTest(ParticleContainerTest::suite());
						break;
					case 2:
						runner.addTest(ParticleIteratorTest::suite());
						break;
					case 3:
						runner.addTest(ParticleGeneratorTest::suite());
						break;
					case 4:
						runner.addTest(ThermostatTest::suite());
						break;
					case 5:
						runner.addTest(FileReaderTest::suite());
						break;
					case 6:
						runner.addTest(MembraneTest::suite());
						break;
					}
					runner.run();
				}
			}
		} else if (arg1 == "--falling-drop-init") {
			//getting information from InputSetting first
			string inpInit = "FallingDropInitSetting.xml";
			pgen.extractSetting(inpInit, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);
			particleList.clear();

			//initialize the size of gravForce
			gravForce.resize(1);
			resizeEpsSig(1);

			pgen.extractCuboids(*inputNames.begin());
			list<Cuboid*>::iterator itC = pgen.getCuboidList().begin();

			//==================G + MIXING RULE====================
			gDirMass[1] = G_CONST * ((*(*itC)).getMass());
			gravForce[0] = utils::Vector<double, 3>(gDirMass);
			EPS[0][0] = (*(*itC)).getEpsilon();
			SIG[0][0] = (*(*itC)).getSigma();
			fillEpsSig(1);

			pgen.cuboidsToList();
			particleList = pgen.getParticleList();

			//======================THERMOSTAT=====================
			thermo = Thermostat(inpInit);

			lcContainer.initialize(particleList, domainSize, R_CUTOFF);
			LCsimulate();
			writeOutputFile((lcContainer.getList()));
		}

		else if (arg1 == "--falling-drop-end") {
			pgen.getParticleList().clear();
			double eps1 = 1.0;
			double sig1 = 1.2;
			FileReader fileReader;
			string inTextS = "ParListStatus.txt";
			char *inText = new char[inTextS.length() + 1];
			strcpy(inText, inTextS.c_str());
			fileReader.readStatus(pgen.getParticleList(), eps1, sig1, inText);

			particleList = pgen.getParticleList();

			//getting information from InputSetting first
			string inpEnd = "FallingDropEndSetting.xml";
			pgen.extractSetting(inpEnd, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);

			//initialize the size of gravForce
			gravForce.resize(2);
			resizeEpsSig(2);

			gDirMass[1] = G_CONST * ((*(*particleList.begin())).getM());
			gravForce[0] = utils::Vector<double, 3>(gDirMass);
			EPS[0][0] = eps1;
			SIG[0][0] = sig1;

			pgen.extractSpheres(*inputNames.begin());
			list<Sphere*>::iterator itS = pgen.getSphereList().begin();

			//==================G + MIXING RULE====================
			gDirMass[1] = G_CONST * ((*(*itS)).getM());
			gravForce[1] = utils::Vector<double, 3>(gDirMass);
			EPS[1][1] = (*(*itS)).getEpsilon();
			SIG[1][1] = (*(*itS)).getSigma();

			fillEpsSig(2);

			pgen.spheresToList();
			pgen.mergeWithParticleList(particleList);

			//======================THERMOSTAT=====================
			thermo = Thermostat(inpEnd);

			lcContainer.initialize(particleList, domainSize, R_CUTOFF);
			LCsimulate();
		}

		else if (arg1 == "--rayleigh-taylor-small") {
			//getting information from InputSetting first
			string inpCubSmall = "RayleighTaylorSmallSetting.xml";
			pgen.extractSetting(inpCubSmall, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);
			particleList.clear();

			//initialize the size of gravForce
			gravForce.resize(inputSize);
			resizeEpsSig(inputSize);

			pgen.extractCuboids(*inputNames.begin());
			// For each type
			for (list<Cuboid*>::iterator itCS = pgen.getCuboidList().begin();
					itCS != pgen.getCuboidList().end(); itCS++) {
				gDirMass[1] = G_CONST * ((*(*itCS)).getMass());
				gravForce[(*(*itCS)).getType()] = utils::Vector<double, 3>(
						gDirMass);
				// fill the diagonal first
				EPS[(*(*itCS)).getType()][(*(*itCS)).getType()] =
						(*(*itCS)).getEpsilon();
				SIG[(*(*itCS)).getType()][(*(*itCS)).getType()] = (*(*itCS)).getSigma();
			}

			fillEpsSig(inputSize);

			pgen.cuboidsToList();
			particleList = pgen.getParticleList();

			thermo = Thermostat(inpCubSmall);

			lcContainer.initialize(particleList, domainSize, R_CUTOFF);
			LCsimulate();
		}

		else if (arg1 == "--rayleigh-taylor-big") {
			//getting information from InputSetting first
			string inpCubBig = "RayleighTaylorBigSetting.xml";
			pgen.extractSetting(inpCubBig, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);
			particleList.clear();

			//initialize the size of gravForce
			gravForce.resize(inputSize);
			resizeEpsSig(inputSize);

			pgen.extractCuboids(*inputNames.begin());
			// For each type
			for (list<Cuboid*>::iterator itCB = pgen.getCuboidList().begin();
					itCB != pgen.getCuboidList().end(); itCB++) {
				gDirMass[1] = G_CONST * ((*(*itCB)).getMass());
				gravForce[(*(*itCB)).getType()] = utils::Vector<double, 3>(
						gDirMass);
				// fill the diagonal first
				EPS[(*(*itCB)).getType()][(*(*itCB)).getType()] =
						(*(*itCB)).getEpsilon();
				SIG[(*(*itCB)).getType()][(*(*itCB)).getType()] = (*(*itCB)).getSigma();
			}

			fillEpsSig(inputSize);

			pgen.cuboidsToList();
			particleList = pgen.getParticleList();

			thermo = Thermostat(inpCubBig);

			lcContainer.initialize(particleList, domainSize, R_CUTOFF);
			LCsimulate();

		}

		else if (arg1 == "--membrane"){
			isMembrane = true;
			//getting information from MembraneSetting first
			string inpMem = "MembraneSetting.xml";
			pgen.extractSetting(inpMem, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);
			particleList.clear();

			//initialize the size of gravForce
			gravForce.resize(1);
			resizeEpsSig(1);

			pgen.extractCuboids(*inputNames.begin());
			list<Cuboid*>::iterator itC = pgen.getCuboidList().begin();
			(*(*itC)).initNeighbors();

			//==================G + MIXING RULE====================
			gDirMass[1] = G_CONST * ((*(*itC)).getMass());
			gravForce[0] = utils::Vector<double, 3>(gDirMass);
			EPS[0][0] = (*(*itC)).getEpsilon();
			SIG[0][0] = (*(*itC)).getSigma();
			//fillEpsSig(1);

			//set the IDs of 4 special particles
			id1 = 24*((*(*itC)).getWidth()) + 17;	//(17, 24)
			id2 = 25*((*(*itC)).getWidth()) + 17;	//(17, 25)
			id3 = 24*((*(*itC)).getWidth()) + 18;	//(18, 24)
			id4 = 25*((*(*itC)).getWidth()) + 18;	//(18, 25)

			pgen.cuboidsToList();
			particleList = pgen.getParticleList();

			thermo = Thermostat(inpMem);

			lcContainer.initialize(particleList, domainSize, R_CUTOFF);
			LCsimulate();
		}

		else {
			cout << arg1 << " invalid!" << endl;
			return -1;
		}
	}

	LOG4CXX_INFO(molsimlogger, "Arrived @ ending simulation.");

	return 0;
}

void simulate() {
// the forces are needed to calculate x, but are not given in the input file.
//calculateF();
	LOG4CXX_INFO(molsimlogger,
			"Size of container: " << container.size() << " particles.");
	LOG4CXX_DEBUG(molsimlogger,
			"Starting force calculation for the first time...");
	calculateFLJ();
	//addGravity(container.getList());

	current_time = start_time;

	int iteration = 0;

	double temperature = thermo.getT_init();
	bool target_temp_reached = false;

// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		//const clock_t beginTime = clock();

		calculateX();

		calculateFLJ();
		//addGravity(container.getList());

		calculateV();

		iteration++;
		cout << "\r" << "Iteration " << iteration << " completed." << flush;

		// Thermostat
//		if (thermo.getEnabled()) {
//			if (!target_temp_reached) {
//				if (iteration % thermo.getn_delta() == 0) {
//					temperature += thermo.getDelta_T();
//					if (temperature > thermo.getT_target()) {
//						temperature -= thermo.getDelta_T();
//						target_temp_reached = true;
//					}
//				}
//			}
//
//			if (iteration % thermo.getn_thermo() == 0) {
//				thermo.setThermo(container.getList(), 2, temperature);
//			}
//		}

		if (iteration % freq == 0) {
			plotVTK(iteration);
		}
		//cout << "Iteration " << iteration << " finished." << endl;
		LOG4CXX_TRACE(molsimlogger, "Iteration " << iteration << " finished.");

		current_time += delta_t;

		//cout << float( clock () - beginTime ) /  CLOCKS_PER_SEC;
		//cin.ignore();
	}

	cout << "\nOutput written. Terminating..." << endl;
}

/**
 * This method calculates the forces between the particles.
 * The calculation obeys the Lennard-Jones force between two molecules.
 */
void calculateFLJ() {

//initialize outer Iterator and index
	utils::Vector<double, 3> zero((double) 0);
	utils::ParticleIterator iterator;
	utils::Vector<double, 3> sumF[container.size()];
	for (int i = 0; i < container.size(); i++) {
		sumF[i] = zero;
	}
	iterator = container.begin();
	int i = 0;
	while (iterator != container.end()) {

		//initialize inner Iterator and Index
		utils::ParticleIterator innerIterator;
		innerIterator = iterator;
		++innerIterator;
		int j = i + 1;

		while (innerIterator != container.end()) {

			Particle& p1 = *iterator;
			Particle& p2 = *innerIterator;

			//calculations
			utils::Vector<double, 3> tempD = p2.getX() - p1.getX();
			double tempDNorm = tempD.L2Norm();

			double tempDSigDivNormPowSix = pow(
					SIG[p1.getType()][p2.getType()] / tempDNorm, 6);
			utils::Vector<double, 3> tempF =
					24 * EPS[p1.getType()][p2.getType()] * pow(1 / tempDNorm, 2)
							* (tempDSigDivNormPowSix
									- 2 * pow(tempDSigDivNormPowSix, 2))
							* tempD;

			sumF[i] += tempF;
			sumF[j] += (-1) * tempF;

			++innerIterator;
			++j;
		}
		// GRAVITY (G_CONST = 0 when gravity is disabled)
		(*iterator).setF(gravForce[(*iterator).getType()] + sumF[i]);
		++iterator;
		++i;
	}
}

/**
 *  This method calculates the position of the particles.
 *  It obeys the Velocity-Stoermer-Verlet-Algorithm.
 */
void calculateX() {

	utils::ParticleIterator iterator;
	iterator = container.begin();
	while (iterator != container.end()) {

		Particle& p = *iterator;

		utils::Vector<double, 3> tempX = p.getX() + delta_t * p.getV()
				+ ((delta_t) * (delta_t) / (2 * p.getM())) * p.getOldF();

		p.getX() = tempX;

		++iterator;
	}
}

/**
 *  This method calculates the position of the particles.
 *  It obeys the Velocity-Stoermer-Verlet-Algorithm.
 */
void calculateV() {

	utils::ParticleIterator iterator;
	iterator = container.begin();
	while (iterator != container.end()) {

		Particle& p = *iterator;

		utils::Vector<double, 3> tempV = p.getV()
				+ (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());

		p.getV() = tempV;
		++iterator;
	}
}

void getIntegerInput(string &str, int &input) {
	while (true) {
		getline(cin, str);
		stringstream myStream(str);
		if (myStream >> input)
			break;
		cout << "Invalid number, please try again" << endl;
	}
}

void getDoubleInput(string &str, double &input) {
	while (true) {
		getline(cin, str);
		stringstream myStream(str);
		if (myStream >> input)
			break;
		cout << "Invalid number, please try again" << endl;
	}
}

/**
 * This method writes the output VTK files.
 */
void plotVTK(int iteration) {

	LOG4CXX_TRACE(molsimlogger, "Arrived @ plotVTK.");

	outputWriter::VTKWriter writer;
	utils::ParticleIterator iterator;
	iterator = container.begin();
	writer.initializeOutput(container.size());
	while (iterator != container.end()) {
		Particle& p = *iterator;
		//cout << "Check X: " << p.getX() << endl;
		//cout << "Check V: " << p.getV() << endl;
		//cout << "Check F: " << p.getF() << endl;
		//cin.ignore();		

		writer.plotParticle(p);
		++iterator;
	}
	string out_name(outputMask);
	writer.writeFile(out_name, iteration);
}

//=========================================================
// LINKED CELL ALGORITHM

/*! To compare the execution time between naive and LC Algorithm:
 *  \image html GraphLCWithoutPlot.jpg
 *  \image html GraphLCWithPlot.jpg
 */

void LCsimulate() {
// the forces are needed to calculate x, but are not given in the input file.
//calculateF();

	LOG4CXX_INFO(molsimlogger, "lcContainer.size: " << lcContainer.size());
	LOG4CXX_INFO(molsimlogger, "particleList.size: " << particleList.size());
	//assert(lcContainer.size() == particleList.size());

	utils::BoundaryHandler boundHandler(domainCondition, lcContainer, h,
			computeForce);

	LCcalculateFLJ();
	//addGravity(lcContainer.getList());

	current_time = start_time;

	double temperature = thermo.getT_init();
	bool target_temp_reached = false;

	int iteration = 0;
// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		//const clock_t beginTime = clock();

		// calculate new x
		LCcalculateX();

		boundHandler.applyOutflow();
		boundHandler.applyPeriodicMoving();

		lcContainer.updateCells();

		boundHandler.applyReflecting();
		boundHandler.applyPeriodic();

		// calculate new f
		LCcalculateFLJ();
		// calculate new v
		LCcalculateV();

		iteration++;
		cout << "\r" << "Iteration " << iteration << " completed." << flush;

		// Thermostat
		if (thermo.getEnabled()) {
			if (!target_temp_reached) {
				if (iteration % thermo.getn_delta() == 0) {
					temperature += thermo.getDelta_T();
					if (temperature > thermo.getT_target()) {
						temperature -= thermo.getDelta_T();
						target_temp_reached = true;
					}
				}
			}

			if (iteration % thermo.getn_thermo() == 0) {
				thermo.setThermo(lcContainer.getList(), 2, temperature);
			}
		}

		if (iteration % freq == 0) {
			LCplotVTK(iteration);
		}

		LOG4CXX_TRACE(molsimlogger, "Iteration " << iteration << " finished.");

//		if(iteration == 1000){
//			gettimeofday(&tim, NULL);
//			double t2=tim.tv_sec+(tim.tv_usec/1000000.0);
//			cout << (t2-t1) << endl;
//		}
		current_time += delta_t;

		//cout << float( clock () - beginTime ) /  CLOCKS_PER_SEC;
		//cin.ignore();
	}

	cout << "\nOutput written. Terminating..." << endl;
}

void LCcalculateFLJ() {

	utils::Vector<double, 3> zero((double) 0);
	utils::Vector<double, 3> sumF((double) 0);
	utils::Vector<double, 3> FZ((double) 0);
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	int i = 0;
	while (iterator != lcContainer.endOuter()) {
		i = iterator.getCellNumber();
		sumF = zero;
		utils::LCInnerParticleIterator innerIterator
					= lcContainer.beginInner(iterator);
		while (innerIterator != lcContainer.endInner(i)) {
			assert(innerIterator != lcContainer.endInner(i));
			if (innerIterator.getCellNumber()
					   > lcContainer.endInner(i).getCellNumber()
					   || innerIterator.getCellNumber()
					   > lcContainer.endOuter().getCellNumber()) {
			   break;
			}
			Particle* p1 = &(*iterator);
			Particle* p2 = &(*innerIterator);
			//cout << *p1 << endl;
			//cout << *p2 << endl;
				/*cout << "Element: " << innerIterator.getCellNumber() << " "
								<< (*p2).toString() << endl;
				cout << "EndInner: " << ((*(lcContainer.endInner(i))).toString())
								<< endl;
								*/
			if (*p1 == *p2) {
				//cout << "ok" << endl;
				++innerIterator;
				continue;
			} else {
				assert(!(*p1 == *p2));

				computeForce(p1, p2);

				++innerIterator;
			}
		}

	   //FZUp
	   if (isMembrane){
		   if (current_time <= 150){
			   if (	((*iterator).getID() == id1) ||
					((*iterator).getID() == id2) ||
					((*iterator).getID() == id3) ||
					((*iterator).getID() == id4)){
				   FZ[3] = FZUp[3];
			   }
		   }
	   }


	   // GRAVITY (G_CONST = 0 when gravity is disabled)
	   (*iterator).setF(
			   FZ + gravForce[(*iterator).getType()] + (*iterator).getTempF());
	   (*iterator).deleteTempF();
	   ++iterator;
	}
}

void LCcalculateX() {

	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	while (iterator != lcContainer.endOuter()) {
		int i = iterator.getCellNumber();
		Particle& p = *iterator;

		utils::Vector<double, 3> tempX = p.getX() + delta_t * p.getV()
				+ ((delta_t) * (delta_t) / (2 * p.getM())) * p.getOldF();

		/*if (tempX[0] < 0 || tempX[1] < 0) {
		 cout << iterator.getCellNumber() << " " << (*iterator).toString();
		 }*/
		p.getX() = tempX;

		++iterator;
	}
}

void LCcalculateV() {

	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	while (iterator != lcContainer.endOuter()) {

		int i = iterator.getCellNumber();
		Particle& p = *iterator;

		utils::Vector<double, 3> tempV = p.getV()
				+ (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());

		p.getV() = tempV;
		++iterator;
	}
}

/**
 *
 * @param p1 the particle of the outer iterator
 * @param p2 the particle of the inner iterator
 */
void computeForce(Particle* p1, Particle* p2) {
	utils::Vector<double, 3> tempD = (*p2).getX() - (*p1).getX();
	double tempDNorm = tempD.L2Norm();

	if (tempDNorm < R_CUTOFF) {
		double tempDSigDivNorm = pow(
				SIG[(*p1).getType()][(*p2).getType()] / tempDNorm, 6);
		utils::Vector<double, 3> tempF = 24 * EPS[(*p1).getType()][(*p2).getType()]
				* pow(1 / tempDNorm, 2)
				* (tempDSigDivNorm - 2 * pow(tempDSigDivNorm, 2)) * tempD;

		if (isMembrane){

			if ((*p1).isDirectNeighborTo(p2)){
				tempF = k*(1 - rDirect/tempDNorm)*tempD;
			}
			else if ((*p1).isDiagNeighborTo(p2)){
				tempF = k*(1 - rDiag/tempDNorm)*tempD;
			}
			else if (tempDNorm > rFLJ){
				tempF = utils::Vector<double, 3> ((double) 0);
			}
		}

		(*p2).updateTempF((-1) * tempF);
		(*p1).updateTempF(tempF);


	}
}

void LCplotVTK(int iteration) {

	outputWriter::VTKWriter writer;
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	writer.initializeOutput(lcContainer.size());
	while (iterator != lcContainer.endOuter()) {
		Particle* p = &(*iterator);
		writer.plotParticle(*p);
		++iterator;
	}
	string out_name(outputMask);
	writer.writeFile(out_name, iteration);
}

void writeOutputFile(list<Particle *> parList) {
	ofstream file;
	file.open("ParListStatus.txt", ios::trunc);
	file << "# file format:\n"
			<< "# Lines of comment start with '#' and are only allowed at the beginning of the file\n"
			<< "# Empty lines are not allowed.\n"
			<< "# The first line not being a comment has to be "
			<< "# <int: number of particles> <double: epsilon> <double: sigma>\n"
			<< "# molecule data sets.\n" << "#\n"
			<< "# Molecule data consists of\n"
			<< "# * xyz-coordinates (3 double values)\n"
			<< "# * velocities (3 double values)\n"
			<< "# * force (3 double values)\n"
			<< "# * old force (3 double values)\n"
			<< "# * mass (1 double value)\n" << "# * type (1 int value)\n"
			<< "#\n" << "# " << setw(45) << "xyz-coord" << setw(45)
			<< "velocity" << setw(45) << "force" << setw(45) << "old force"
			<< setw(15) << "mass" << setw(10) << "type\n" << setw(10)
			<< parList.size() << setw(10)
			<< EPS[(*parList.begin())->getType()][(*parList.begin())->getType()]
			<< setw(10)
			<< SIG[(*parList.begin())->getType()][(*parList.begin())->getType()]
			<< endl;
	for (list<Particle *>::iterator it = parList.begin(); it != parList.end();
			it++) {
		file << setw(15) << (*it)->getX()[0] << setw(15) << (*it)->getX()[1]
				<< setw(15) << (*it)->getX()[2]

				<< setw(15) << (*it)->getV()[0] << setw(15) << (*it)->getV()[1]
				<< setw(15) << (*it)->getV()[2]

				<< setw(15) << (*it)->getF()[0] << setw(15) << (*it)->getF()[1]
				<< setw(15) << (*it)->getF()[2]

				<< setw(15) << (*it)->getOldF()[0] << setw(15)
				<< (*it)->getOldF()[1] << setw(15) << (*it)->getOldF()[2]

				<< setw(15) << (*it)->getM() << setw(10) << (*it)->getType()
				<< endl;
	}
	file.close();
}

void resizeEpsSig(int inSize) {
	EPS.resize(inSize);
	SIG.resize(inSize);
	for (int i = 0; i < inSize; i++) {
		EPS[i].resize(inSize);
		SIG[i].resize(inSize);
	}
}

// the diagonal of the 2D matrix must have been filled before
void fillEpsSig(int inSize) {
	for (int i = 0; i < inSize; i++) {
		for (int j = 0; j < inSize; j++) {
			//Lorentz-Berthelot Mixing rule
			EPS[i][j] = (EPS[i][i] + EPS[j][j]) / 2;
			SIG[i][j] = sqrt(SIG[i][i] * SIG[j][j]);
		}
	}
}
