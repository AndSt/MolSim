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
#include <omp.h>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**** forward declaration of the calculation functions ****/

void simulate();
void LCsimulate();

/**
 * force calculation methods(with and without linked-cell)
 */
void calculateFLJ();
void LCcalculateF();

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

/**
 * function pointer to the used force calculation method
 */
void (*computeForce)(Particle&, Particle&);

/**
 * lennard jones force calculation
 */
void computeLennardJones(Particle& p1, Particle& p2);

void computeSmoothedLennardJones(Particle& p1, Particle& p2);

void calculateDiffusion();

void calculateRDF();

void getIntegerInput(string &str, int &input);

void getDoubleInput(string &str, double &input);

void resizeEpsSig(int inSize);

void fillEpsSig(int inSize);

// plot the particles to VTKWriter-File
void plotVTK(int iteration);
void LCplotVTK(int iteration);

void writeOutputFile(list<Particle *> parList);

void runAllTests();
void initializeSimulation(string inpFile);

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

int inputSize = 0;
list<Particle> particleList;
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

	PropertyConfigurator::configure("Log4cxxConfig.cfg");
	LOG4CXX_INFO(molsimlogger, "Arrived @ main.");

	/* Format input command line:
	 *
	 * ./MolSim								: normal running
	 *
	 * ./MolSim --test						: for test
	 *
	 * ./MolSim --falling-drop-init			: for initialization of falling drop experiment
	 *
	 * ./MolSim --falling-drop-end			: for the falling drop experiment
	 *
	 * ./MolSim --rayleigh-taylor-small		: for the small Rayleigh-Taylor experiment
	 *
	 * ./MolSim --rayleigh-taylor-big		: for the big Rayleigh-Taylor experiment
	 *
	 * ./MolSim --rayleigh-taylor-3D		: for the Rayleigh-Taylor experiment in 3D
	 *
	 * ./MolSim --membrane					: for the membrane experiment
	 *
	 * ./MolSim --cooling-argon-init		: for initialization of cooling argon experiment
	 *
	 * ./MolSim --cooling-argon-1			: for the cooling argon experiment
	 *
	 * ./MolSim --cooling-argon-2			: for the super cooling argon experiment
	 */

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
					<< "Hint: If you enter '1' or '2' you will return to this menu";
			cout << endl << endl;
			while (option != 3) {
				cout << "Enter '1' to test all unit tests." << endl;
				cout << "Enter '2' to test a specific unit test." << endl;
				cout << "Enter '3' to exit the 'test suite'." << endl;
				cout << endl;

				//Check for correct input
				getIntegerInput(str, option);

				if (option == 1) {
					LOG4CXX_DEBUG(molsimlogger, "Running all Tests.");
					runAllTests();

				} else if (option == 2) {
					cout << "Enter '1' to test the ParticleContainer." << endl;
					cout << "Enter '2' to test the ParticleIterator." << endl;
					cout << "Enter '3' to test the ParticleGenerator." << endl;
					cout << "Enter '4' to test the Thermostat." << endl;
					cout << "Enter '5' to test the FileReader." << endl;
					//TODO: Alle wählbaren Tests einfügen

					//Check for correct input
					int opT;
					getIntegerInput(str, opT);

					CppUnit::TextUi::TestRunner runner;
					switch (opT) {
					case 1:
						LOG4CXX_DEBUG(molsimlogger,
								"Testing ParticleContainer alone.")
						;
						runner.addTest(ParticleContainerTest::suite());
						break;
					case 2:
						LOG4CXX_DEBUG(molsimlogger,
								"Testing ParticleIterator alone.")
						;
						runner.addTest(ParticleIteratorTest::suite());
						break;
					case 3:
						LOG4CXX_DEBUG(molsimlogger,
								"Testing ParticleGenerator alone.")
						;
						runner.addTest(ParticleGeneratorTest::suite());
						break;
					case 4:
						LOG4CXX_DEBUG(molsimlogger, "Testing Thermostat alone.")
						;
						runner.addTest(ThermostatTest::suite());
						break;
					case 5:
						LOG4CXX_DEBUG(molsimlogger, "Testing FileReader alone.")
						;
						runner.addTest(FileReaderTest::suite());
						break;
					}
					runner.run();
				} else if (option == 3) {
					LOG4CXX_DEBUG(molsimlogger, "Stopped testing.");
					cout << "Alright! Goodbye then!" << endl;
				}

				else {
					cout << "Invalid number, please try again.\n" << endl;
				}
			}
		} else if ((arg1 == "--falling-drop-init") ||
					(arg1 == "--cooling-argon-init")){
			if (arg1 == "--falling-drop-init"){
				LOG4CXX_INFO(molsimlogger, "Doing FallingDropInit.");
				fileName = "input/FallingDropInitSetting.xml";
			}else{
				LOG4CXX_INFO(molsimlogger, "Doing CoolingArgonInit.");
				fileName = "input/CoolingArgonInitSetting.xml";
			}

			pgen.extractSetting(fileName, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);
			particleList.clear();

			//initialize the size of gravForce
			gravForce.resize(1);
			resizeEpsSig(1);

			pgen.extractCuboids(*inputNames.begin());
			list<Cuboid>::iterator itC = pgen.getCuboidList().begin();

			//==================G + MIXING RULE====================
			gDirMass[1] = G_CONST * ((*itC).getMass());
			gravForce[0] = utils::Vector<double, 3>(gDirMass);
			EPS[0][0] = (*itC).getEpsilon();
			SIG[0][0] = (*itC).getSigma();
			fillEpsSig(1);

			pgen.cuboidsToList();
			particleList = pgen.getParticleList();
		}

		else if (arg1 == "--falling-drop-end") {
			LOG4CXX_INFO(molsimlogger, "Doing FallingDropEnd.");
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
			fileName = "input/FallingDropEndSetting.xml";
			pgen.extractSetting(fileName, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);

			//initialize the size of gravForce
			gravForce.resize(2);
			resizeEpsSig(2);

			gDirMass[1] = G_CONST * ((*particleList.begin()).getM());
			gravForce[0] = utils::Vector<double, 3>(gDirMass);
			EPS[0][0] = eps1;
			SIG[0][0] = sig1;

			pgen.extractSpheres(*inputNames.begin());
			list<Sphere>::iterator itS = pgen.getSphereList().begin();

			//==================G + MIXING RULE====================
			gDirMass[1] = G_CONST * ((*itS).getM());
			gravForce[1] = utils::Vector<double, 3>(gDirMass);
			EPS[1][1] = (*itS).getEpsilon();
			SIG[1][1] = (*itS).getSigma();

			fillEpsSig(2);

			pgen.spheresToList();
			pgen.mergeWithParticleList(particleList);
		}
 
		else if ((arg1 == "--rayleigh-taylor-small") ||
				(arg1 == "--rayleigh-taylor-big") ||
				(arg1 == "--rayleigh-taylor-3D")){
			if (arg1 == "--rayleigh-taylor-small"){
				LOG4CXX_INFO(molsimlogger, "Doing RayleighTaylorSmall.");
				fileName = "input/RayleighTaylorSmallSetting.xml";
			}
			else if (arg1 == "--rayleigh-taylor-big"){
				LOG4CXX_INFO(molsimlogger, "Doing RayleighTaylorBig.");
				fileName = "input/input/RayleighTaylorBigSetting.xml";
			}
			else{
				LOG4CXX_INFO(molsimlogger, "Doing RayleighTaylor3D.");
				fileName = "input/input/RayleighTaylor3DSetting.xml";
			}

			pgen.extractSetting(fileName, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);
			particleList.clear();

			//initialize the size of gravForce
			gravForce.resize(inputSize);
			resizeEpsSig(inputSize);

			pgen.extractCuboids(*inputNames.begin());
			// For each type
			for (list<Cuboid>::iterator itCB = pgen.getCuboidList().begin();
					itCB != pgen.getCuboidList().end(); itCB++) {
				gDirMass[1] = G_CONST * ((*itCB).getMass());
				gravForce[(*itCB).getType()] = utils::Vector<double, 3>(
						gDirMass);
				// fill the diagonal first
				EPS[(*itCB).getType()][(*itCB).getType()] =
						(*itCB).getEpsilon();
				SIG[(*itCB).getType()][(*itCB).getType()] = (*itCB).getSigma();
			}

			fillEpsSig(inputSize);

			pgen.cuboidsToList();
			particleList = pgen.getParticleList();
		} 

		else if ((arg1 == "--cooling-argon-1") ||
				(arg1 == "--cooling-argon-2")) {
			if (arg1 == "--cooling-argon-1"){
				LOG4CXX_INFO(molsimlogger, "Doing CoolingArgon1.");
				fileName = "input/CoolingArgon1Setting.xml";
			}
			else{
				LOG4CXX_INFO(molsimlogger, "Doing CoolingArgon2.");
				fileName = "input/CoolingArgon2Setting.xml";
			}

			pgen.getParticleList().clear();
			double eps1 = 1.0;
			double sig1 = 1.0;
			FileReader fileReader;
			string inTextS = "ParListStatus.txt";
			char *inText = new char[inTextS.length() + 1];
			strcpy(inText, inTextS.c_str());
			fileReader.readStatus(pgen.getParticleList(), eps1, sig1, inText);

			particleList = pgen.getParticleList();

			pgen.extractSetting(fileName, start_time, end_time, delta_t,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST, inputSize);

			//initialize the size of gravForce
			gravForce.resize(1);
			resizeEpsSig(1);

			pgen.extractCuboids(*inputNames.begin());
			list<Cuboid>::iterator itC = pgen.getCuboidList().begin();

			//==================G + MIXING RULE====================
			gDirMass[1] = G_CONST * ((*itC).getMass());
			gravForce[0] = utils::Vector<double, 3>(gDirMass);
			EPS[0][0] = (*itC).getEpsilon();
			SIG[0][0] = (*itC).getSigma();
			fillEpsSig(1);
		}
		
		else {
			LOG4CXX_ERROR(molsimlogger, "Invalid number input.");
			cout << arg1 << " invalid!" << endl;
			return -1;
		}
	} else {		
		cout << "Invalid argument!" << endl;
		cout << "Try:" << endl;
		cout << "\t./MolSim --falling-drop-init" << endl;
		cout << "\t./MolSim --falling-drop-end" << endl;
		cout << "\t./MolSim --rayleigh-taylor-small" << endl;
		cout << "\t./MolSim --rayleigh-taylor-big" << endl;
		cout << "\t./MolSim --rayleigh-taylor-3D" << endl;
		cout << "\t./MolSim --membrane" << endl;
		cout << "\t./MolSim --cooling-argon-init" << endl;
		cout << "\t./MolSim --cooling-argon-1" << endl;
		cout << "\t./MolSim --cooling-argon-2" << endl;
		return -1;
	}

	thermo = Thermostat(fileName);

	lcContainer.initialize(particleList, domainSize, R_CUTOFF);
	LOG4CXX_INFO(molsimlogger, "Arrived @ simulation call.");
	LCsimulate();
	if ((fileName == "input/FallingDropInitSetting.xml")
		|| (fileName == "input/CoolingArgonInitSetting.xml")) {
		writeOutputFile((lcContainer.getList()));
	}

	LOG4CXX_INFO(molsimlogger, "Simulation ended successfully.");

	return 0;
}

void runAllTests() {
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(ParticleIteratorTest::suite());
	runner.addTest(ParticleContainerTest::suite());
	runner.addTest(ParticleGeneratorTest::suite());
	runner.addTest(LCParticleContainerTest::suite());
	runner.addTest(LCInnerParticleIteratorTest::suite());
	runner.addTest(LCOuterParticleIteratorTest::suite());
	runner.addTest(ThermostatTest::suite());
	runner.addTest(FileReaderTest::suite());
	runner.run();
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

	double current_time = start_time;

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

			double tempDSigDivNormPowSix = pow(SIG[0][0] / tempDNorm, 6);
			utils::Vector<double, 3> tempF =
					24 * EPS[0][0] * pow(1 / tempDNorm, 2)
							* (tempDSigDivNormPowSix
									- 2 * pow(tempDSigDivNormPowSix, 2))
							* tempD;

			sumF[i] += tempF;
			sumF[j] += (-1) * tempF;

			++innerIterator;
			++j;
		}
		// GRAVITY (G_CONST = 0 when gravity is disabled)
		//(*iterator).setF(gravForce[(*iterator).getType()] + sumF[i]);
		++iterator;
		++i;
		//TODO: Eps und Sig abklären
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

	LOG4CXX_INFO(molsimlogger, "lcContainer.size: " << lcContainer.size());
	LOG4CXX_INFO(molsimlogger, "particleList.size: " << particleList.size());
	//assert(lcContainer.size() == particleList.size());

	utils::BoundaryHandler boundHandler(domainCondition, lcContainer, h,
			computeLennardJones);

	LCcalculateF();
	//addGravity(lcContainer.getList());

	double current_time = start_time;

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
		LCcalculateF();

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

//		if (iteration % freq == 0) {
//			LCplotVTK(iteration);
//		}

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

void LCcalculateF() {

	utils::Vector<double, 3> zero((double) 0);
	utils::Vector<double, 3> sumF((double) 0);

#ifndef _OPENMP
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();

	while (iterator != lcContainer.endOuter()) {
		sumF = zero;
		utils::LCInnerParticleIterator innerIterator = lcContainer.beginInner(
				iterator);
		while (innerIterator != lcContainer.endInner(iterator.getCellNumber())) {

			Particle& p1 = *iterator;
			Particle& p2 = *innerIterator;

			if (p1 == p2) {
				++innerIterator;
				continue;
			} else {
				assert(!(p1 == p2));
				computeLennardJones(p1, p2);
			}
			++innerIterator;
		}
		++iterator;
	}
#endif
#ifdef _OPENMP
	utils::LCOuterParticleIterator iterator;
	utils::LCInnerParticleIterator innerIterator;
	int i, j;
#pragma omp parallel private(i, j, iterator, innerIterator, zero, sumF)
	{
#pragma omp for schedule(dynamic)
		for (i = 0; i < omp_get_num_threads(); i++) {
			iterator = lcContainer.beginOuter(i);

			while (iterator != lcContainer.endOuter(i)) {
//#pragma omp critical
//			{
//				std::cout << iterator.getCellNumber() << " | " << lcContainer.endOuter(i).getCellNumber() << std::endl;
//			}
				assert(iterator.getCellNumber() <= lcContainer.endOuter(i).getCellNumber());
				j = iterator.getCellNumber();
				sumF = zero;
				innerIterator = lcContainer.beginInner(iterator);
				while (innerIterator
						!= lcContainer.endInner(j)) {

					assert(innerIterator.getCellNumber() <= lcContainer.endInner(j).getCellNumber());

					Particle& p1 = *iterator;
					Particle& p2 = *innerIterator;
					if (p1 == p2) {
						++innerIterator;
						continue;
					} else {
						computeLennardJones(p1, p2);
					}
					++innerIterator;
				}
				++iterator;
			}

		}
	}

#endif

	//setF
	utils::LCOuterParticleIterator iterator2 = lcContainer.beginOuter();
	while (iterator2 != lcContainer.endOuter()) {
		(*iterator2).setF(
				gravForce[(*iterator2).getType()] + (*iterator2).getTempF());
		(*iterator2).deleteTempF();
		++iterator2;
	}
}

void LCcalculateX() {
//#ifndef _OPENMP
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	while (iterator != lcContainer.endOuter()) {

		Particle& p = *iterator;

		utils::Vector<double, 3> tempX = p.getX() + delta_t * p.getV()
				+ ((delta_t) * (delta_t) / (2 * p.getM())) * p.getOldF();

		/*if (tempX[0] < 0 || tempX[1] < 0) {
		 cout << iterator.getCellNumber() << " " << (*iterator).toString();
		 }*/
		p.getX() = tempX;

		++iterator;
	}
	/*#else
	 #pragma omp parallel
	 {
	 #pragma omp for schedule(dynamic)
	 for(int i = 0; i < omp_get_num_threads(); i++) {
	 utils::LCOuterParticleIterator iterator = lcContainer.beginOuter(i);
	 while (iterator != lcContainer.endOuter(i)) {
	 Particle& p = *iterator;
	 utils::Vector<double, 3> tempX = p.getX() + delta_t * p.getV()
	 + ((delta_t) * (delta_t) / (2 * p.getM())) * p.getOldF();

	 //				if (tempX[0] < 0 || tempX[1] < 0) {
	 //				 cout << iterator.getCellNumber() << " " << (*iterator).toString();
	 //				 }
	 p.getX() = tempX;

	 ++iterator;
	 }
	 }
	 }
	 #endif*/
}

void LCcalculateV() {
//#ifndef _OPENMP
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	while (iterator != lcContainer.endOuter()) {
		Particle& p = *iterator;

		utils::Vector<double, 3> tempV = p.getV()
				+ (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());

		p.getV() = tempV;

		++iterator;
	}
	/*#else
	 #pragma omp parallel
	 {
	 #pragma omp for schedule(dynamic)
	 for(int i = 0; i < omp_get_num_threads(); i++) {
	 utils::LCOuterParticleIterator iterator = lcContainer.beginOuter(i);
	 while (iterator != lcContainer.endOuter(i)) {
	 Particle& p = *iterator;

	 utils::Vector<double, 3> tempV = p.getV()
	 + (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());

	 p.getV() = tempV;

	 ++iterator;
	 }
	 }
	 }
	 #endif*/
}

/**
 *
 * @param p1 the particle of the outer iterator
 * @param p2 the particle of the inner iterator
 */
void computeLennardJones(Particle& p1, Particle& p2) {
	utils::Vector<double, 3> tempD = p2.getX() - p1.getX();
	double tempDNorm = tempD.L2Norm();

	if (tempDNorm < R_CUTOFF) {

		double tempDSigDivNorm = pow(
				SIG[p1.getType()][p2.getType()] / tempDNorm, 6);

		utils::Vector<double, 3> tempF = 24 * EPS[p1.getType()][p2.getType()]
				* pow(1 / tempDNorm, 2)
				* (tempDSigDivNorm - 2 * pow(tempDSigDivNorm, 2)) * tempD;

		p2.updateTempF((-1) * tempF);
		p1.updateTempF(tempF);
	}
}

void computeSmoothedLennardJones(Particle& p1, Particle& p2) {
	utils::Vector<double, 3> tempD = p2.getX() - p1.getX();
	double tempDNorm = tempD.L2Norm();

	double rl = 1.3;
	utils::Vector<double, 3> tempS;
	if (tempDNorm < rl) {
		tempS = 1.0;
	} else if (tempDNorm < R_CUTOFF) {
		tempS = 1
				- (tempDNorm - rl) * (tempDNorm - rl)
						* ((3 * R_CUTOFF - rl - (2 * tempDNorm))
								/ pow(R_CUTOFF - rl, 3));
	} else {
		tempS = 0.0;

	}

	double tempDSigDivNorm = pow(SIG[p1.getType()][p2.getType()] / tempDNorm,
			6);

	utils::Vector<double, 3> tempF = 24 * EPS[p1.getType()][p2.getType()]
			* pow(1 / tempDNorm, 2)
			* (tempDSigDivNorm - 2 * pow(tempDSigDivNorm, 2)) * tempS * tempD;

	p2.updateTempF((-1) * tempF);
	p1.updateTempF(tempF);
}

void LCplotVTK(int iteration) {

	outputWriter::VTKWriter writer;
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	writer.initializeOutput(lcContainer.size());
	while (iterator != lcContainer.endOuter()) {
		Particle& p = *iterator;
		writer.plotParticle(p);
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

void calculateDiffusion() {
	utils::Vector<double, 3> diffusion = 0.0;
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	int i = 0;
	//number of particles
	while (iterator != lcContainer.endOuter()) {
		Particle& p = *iterator;
		diffusion += (p.getX() - p.getX0()) * (p.getX() - p.getX0());
		++i;
		++iterator;
	} //TODO: //diff[t] = (1/(double)i) * diffusion;
}

void calculateRDF() {

	double r = 1.0;
	double deltaR = 0.1;

	std::vector<double> number;
	number.resize((r / deltaR));		//Check if the cast is correct
	for (int i = 0; i < number.size(); i++) {
		number[i] = 0;
	}

	utils::LCOuterParticleIterator outerIterator = lcContainer.beginOuter();

	while (outerIterator != lcContainer.endOuter()) {

		utils::LCInnerParticleIterator innerIterator = lcContainer.beginInner(
				outerIterator);

		while (innerIterator != lcContainer.endInner(outerIterator.getCellNumber())) {

			utils::Vector<double, 3> tempD = (*innerIterator).getX()
					- (*outerIterator).getX();
			double tempDNorm = tempD.L2Norm();

			if (tempDNorm <= r) {
				number[(tempDNorm / deltaR)] += 2;
			}

			++innerIterator;
		}

		++outerIterator;
	}

	for(int i = 0; i < number.size(); i++){
		number[i] = number[i] / ((double)lcContainer.size());
	}
}
