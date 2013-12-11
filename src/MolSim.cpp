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

void computeForce(Particle& p1, Particle& p2);

void getIntegerInput(string &str, int &input);

void getDoubleInput(string &str, double &input);

// plot the particles to VTKWriter-File
void plotVTK(int iteration);
void LCplotVTK(int iteration);

void writeOutputFile();

double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;

//{InputCuboids, InputParticles, InputSpheres}
list<string> inputNames;

//{cuboids, particles, spheres}
list<string> inputTypes;

string outputMask = "MD_vtk";
int freq = 10;

// For Lennard-Jones
double SIGMA = 1.0;
double EPSILON = 5.0;
double G_CONST = -12.44;

// For Linked Cell Algorithm
double R_CUTOFF = 3.0;
utils::Vector<double, 3> domainSize;
bool outflow_flag = false;
const double h = (pow(2, (1 / 6)) * SIGMA);
int depth = 0;

bool gravity = false;

list<Particle> particleList;
utils::ParticleContainer container;
utils::ParticleGenerator pgen;
utils::LCParticleContainer lcContainer;

vector<int> domainCondition;
// 0: left	1: right
// 2: ground/lower	3:upper
// 4: front	5: behind/gear
// Value: 1 = outflow, 2= reflecting
// default = "outflow"

string fileName;

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
	 * for running:
	 * ./MolSim
	 *
	 * for testing:
	 * ./MolSim -test
	 */

	bool test = false;
	if (argc >= 2) {
		string arg1 = argsv[1];
		if (arg1 == "-test")
			test = true;
	}

	/*
	 * "Testing suite": Read in the Options and run the TestRunner
	 */
	if (test == true) {

		LOG4CXX_INFO(molsimlogger, "Arrived @ testsuite.");

		string str;
		int option = 0;

		cout << "Here are the testing options: " << endl;
		cout
				<< "Tipp: If you Enter Option '1' or '2' you will get back to this menu";
		cout << endl << endl;
		while (option != 3) {
			cout << "Enter '1', if you want to test all unit tests." << endl;
			cout << "Enter '2', if you want to test a specific unit test."
					<< endl;
			cout << "Enter '3', if you want to exit the 'test suite'." << endl;
			cout << endl;

			//Check for correct input
			getIntegerInput(str, option);

			if (option == 1) {

				CppUnit::TextUi::TestRunner runner;
				runner.addTest(ParticleIteratorTest::suite());
				runner.addTest(ParticleContainerTest::suite());
				runner.addTest(ParticleGeneratorTest::suite());
				runner.addTest(LCParticleContainerTest::suite());
				//runner.addTest(LCInnerParticleIteratorTest::suite());
				runner.addTest(LCOuterParticleIteratorTest::suite());
				runner.addTest(ThermostatTest::suite());
				runner.run();

			} else if (option == 2) {
				cout << "Enter '1', if you want to test the ParticleContainer."
						<< endl;
				cout << "Enter '2', if you want to test the ParticleIterator."
						<< endl;
				cout << "Enter '3', if you want to test the ParticleGenerator."
						<< endl;

				//Check for correct input
				getIntegerInput(str, option);

				CppUnit::TextUi::TestRunner runner;
				switch (option) {
				case 1:
					runner.addTest(ParticleContainerTest::suite());
					break;
				case 2:
					runner.addTest(ParticleIteratorTest::suite());
					break;
				case 3:
					runner.addTest(ParticleGeneratorTest::suite());
					option = 2;
					break;
				}
				runner.run();
			}
		}
	}

	/*
	 * "Running suite":
	 * 	reads in options, fills particle container and runs the simulation
	 */

	else {
		LOG4CXX_INFO(molsimlogger, "Arrived @ filedecision.");
		string str;
		FileReader fileReader;
		cout << "Hello from Andreas, Matthias and Son!" << endl;
		cout << endl;
		//variable for Level 1 Options:
		int option1;
		//Level 1 Options:
		//[1] - run from particle file
		//[2] - run from cuboid file
		//[3] - run from XML input files
		cout
				<< "Enter '1', if you want to run the program with a particle file."
				<< endl;
		cout << "Enter '2', if you want to run program with a cuboid file."
				<< endl;
		cout << "Enter '3', if you want to run program with xml input files."
				<< endl;

		getIntegerInput(str, option1);

		switch (option1) {
		case 1:
			cout << "Enter '1', if you want the default configuration: "
					<< endl;
			cout << "         file -'eingabe-sonne.txt'" << endl;
			cout << "         end time - 1000" << endl;
			cout << "         delta t - 0.014" << endl;
			cout
					<< "Enter '2', if you 'eingabe-sonne.txt' with different options"
					<< endl;
			cout << "Enter '3', if you want completely different options"
					<< endl;

			break;
		case 2:
			cout << "Enter '1', if you want the default configuration: "
					<< endl;
			cout << "         file -'eingabe-brownian.txt'" << endl;
			cout << "         end time - 5" << endl;
			cout << "         delta t - 0.0002" << endl;
			cout
					<< "Enter '2', if you 'eingabe-brownian.txt' with different options"
					<< endl;
			cout << "Enter '3', if you want completely different options"
					<< endl;
			break;
		case 3:
			cout << "XML input files are stored in MolSim." << endl;
			cout << "There are 3 sources of input files:" << endl;
			cout
					<< "\tInputSetting: contains start_time, end_time, delta_t,\
					\n\t\t inputfile name, inputfile type, output mask\
				 	\n\t\t and output frequency."
					<< endl;
			cout
					<< "\tInputParticles: contains all information needed for particles."
					<< endl;
			cout
					<< "\tInputCuboids: contains all information needed for cuboids."
					<< endl;
			cout
					<< "\tInputSpheres: contains all information needed for spheres."
					<< endl;
			cout << "\nPress 1 to use Linked Cell Algorithm." << endl;
			cout << "Press 2 to simulate without Linked Cell Algorithm." << endl;
			break;
		}

		//variable for Level 2 Options:
		int option2;

		//level 2 Options:
		//[1] - default configuration
		//[2] - define delta_t, end_time by yourself
		//[3] - define fileName, delta_t and end_time by yourself
		getIntegerInput(str, option2);

		//for particle file:
		if (option1 == 1) {
			switch (option2) {
			case 1:
				fileName = "eingabe-sonne.txt";
				delta_t = 0.014;
				end_time = 1000;
				break;
			case 2:
				fileName = "eingabe-sonne.txt";
				cout << "Please enter the value of delta_t:" << endl;
				getDoubleInput(str, delta_t);
				cout << "Please enter the value of end_time:" << endl;
				getDoubleInput(str, end_time);
				break;
			case 3:
				cout << "Please enter the name of your file:" << endl;
				getline(cin, fileName);
				cout << "Please enter the value of delta_end:" << endl;
				getDoubleInput(str, delta_t);
				cout << "Please enter the value of end_time:" << endl;
				getDoubleInput(str, end_time);
				break;
			}
			char *cstr = new char[fileName.length() + 1];
			strcpy(cstr, fileName.c_str());
			fileReader.readFile(particleList, cstr);
		}
		//for cuboid list:
		else if (option1 == 2) {
			switch (option2) {
			case 1:
				fileName = "eingabe-brownian.txt";
				delta_t = 0.0002;
				end_time = 5;
				break;
			case 2:
				fileName = "eingabe-brownian.txt";
				cout << "Please enter the value of delta_t:" << endl;
				getDoubleInput(str, delta_t);
				cout << "Please enter the value of end_time:" << endl;
				getDoubleInput(str, end_time);
				break;
			case 3:
				cout << "Please enter the name of your file:" << endl;
				getline(cin, fileName);
				cout << "Please enter the value of delta_t:" << endl;
				getDoubleInput(str, delta_t);
				cout << "Please enter the value of end_time:" << endl;
				getDoubleInput(str, end_time);
				break;
			}

			char *cstr = new char[fileName.length() + 1];
			strcpy(cstr, fileName.c_str());
			pgen.readCuboids(cstr);
			pgen.cuboidsToList();
			particleList = pgen.getParticleList();
		}

		//for XML input:
		else if (option1 == 3) {
			//getting information from InputSetting first
			pgen.extractSetting(start_time, end_time, delta_t, EPSILON, SIGMA,
					inputNames, inputTypes, outputMask, freq, domainSize,
					R_CUTOFF, domainCondition, G_CONST);
			particleList.clear();
			list<string>::iterator itT = inputTypes.begin();
			int i = 1;

			for (list<string>::iterator itN = inputNames.begin();
					itN != inputNames.end(); itN++) {
				if (*itT == "particles") {
					cout << i << ". input file: " << "[particles]." << endl;
					pgen.extractParticles(*itN);
					pgen.mergeWithParticleList(particleList);
				} else if (*itT == "cuboids") {
					cout << i << ". input file: " << "[cuboids]" << endl;
					pgen.extractCuboids(*itN);
					pgen.cuboidsToList();
					pgen.mergeWithParticleList(particleList);
				} else {
					cout << i << ". input file: " << "[spheres]" << endl;
					pgen.extractSpheres(*itN);
					pgen.spheresToList();
					pgen.mergeWithParticleList(particleList);
				}
				itT++;
				i++;
			}

			cout << "Press enter to continue..." << endl;
			cin.ignore();

			//======================GRAVITY=====================
			int ag;
			cout << "Do you want to add gravity?\nPress 1 to confirm, 2 to ignore." << endl;
			getIntegerInput(str, ag);
			if (ag==1){
				cout 	<< "Gravity enabled.\n"
						<< "G = " << G_CONST << "." << endl;
			}else{
				cout 	<< "Gravity disabled." << endl;
				G_CONST = 0;
			}
			//======================GRAVITY=====================

			//======================FALLING DROP=====================
			int fd;
			cout << "\nDo you want to simulate the falling drop?\n"
					<< "Note: ParListStatus.txt must exist!\n"
					<< "Press 1 to confirm, 2 to ignore." << endl;
			getIntegerInput(str, fd);
			if (fd==1){
				cout << "Falling drop chosen." << endl;
				pgen.getParticleList().clear();
				fileReader.readStatus(pgen.getParticleList(),"ParListStatus.txt");
				pgen.mergeWithParticleList(particleList);
				cout << "Input data from ParListStatus imported." << endl;
			}else{
				cout << "Falling drop disabled." << endl;
			}
			//======================FALLING DROP=====================
		}

		cout << "\nReading input file..." << endl;

		//initialize container with particle list
		LOG4CXX_INFO(molsimlogger, "Arrived @ initialization call.");

		//start simulation
		LOG4CXX_INFO(molsimlogger, "Arrived @ simulation call.");

		//======================THERMOSTAT=====================
		int thermoOption;
		cout << "Do you want to use Thermostat?\nPress 1 to confirm, 2 to ignore." << endl;
		getIntegerInput(str, thermoOption);

		if (thermoOption==1){
			//initialize thermostat to get enabled flag (true --> call, false --> ignore)
			thermo = Thermostat();
			thermo.getEnabled()=true;
			cout << "Thermostat enabled. Target temperature: "
							<< thermo.getT_target() << ".\n" << endl;
		}else{
			cout << "Thermostat disabled.\n" << endl;
		}
		//======================THERMOSTAT=====================

		cout << "Running simulation..." << endl;

		if (option1 == 3 && option2 == 1) {
			lcContainer.initialize(particleList, domainSize, R_CUTOFF);
			LCsimulate();
		} else {
			container.initialize(particleList);
			simulate();
		}

		int wo;
		cout << "\nWrite ParListStatus.txt out?" << endl;
		cout << "Press 1 to confirm, 2 to ignore." << endl;
		getIntegerInput(str, wo);
		if (wo==1){
			writeOutputFile();
			cout << "ParListStatus.txt written." << endl;
		}

		LOG4CXX_INFO(molsimlogger, "Arrived @ ending simulation.");
	}
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

	double current_time = start_time;

	int iteration = 0;

	double temperature = thermo.getT_init();
	bool target_temp_reached = false;

// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		//const clock_t beginTime = clock();

		calculateX();

		calculateFLJ();

		calculateV();

		iteration++;
		cout << "\r" << "Iteration " << iteration << " completed." << flush;

		// Thermostat
		if (thermo.getEnabled()){
			if (!target_temp_reached){
				if (iteration % thermo.getn_delta() == 0){
					temperature += thermo.getDelta_T();
					if (temperature > thermo.getT_target()){
						temperature -= thermo.getDelta_T();
						target_temp_reached = true;
					}
				}
			}


			if (iteration % thermo.getn_thermo() == 0){
				thermo.setThermo(particleList, 2, temperature);
			}
		}

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

			//if(tempDNorm < R_CUTOFF) {
			double tempDSigDivNormPowSix = pow(SIGMA / tempDNorm, 6);
			utils::Vector<double, 3> tempF =
					24 * EPSILON * pow(1 / tempDNorm, 2)
							* (tempDSigDivNormPowSix
									- 2 * pow(tempDSigDivNormPowSix, 2))
							* tempD;

			sumF[i] += tempF;
			sumF[j] += (-1) * tempF;
			//}
			++innerIterator;
			++j;
		}
		// GRAVITY (G_CONST = 0 when gravity is disabled)
		double gDirection[] = {0.0, 1.0, 0.0};
		utils::Vector<double, 3> gDirVec(gDirection);
		utils::Vector<double, 3> gravForce(G_CONST*((*iterator).getM())*gDirVec);

		//(*iterator).setF(sumF[i]);
		(*iterator).setF(gravForce + sumF[i]);
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
	LCcalculateFLJ();
	double current_time = start_time;

	double temperature = thermo.getT_init();
	bool target_temp_reached = false;

	int iteration = 0;
// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		//const clock_t beginTime = clock();

		// calculate new x
		LCcalculateX();
		// calculate new f
		LCcalculateFLJ();
		// calculate new v
		LCcalculateV();

		iteration++;
		cout << "\r" << "Iteration " << iteration << " completed." << flush;

		// Thermostat
		if (thermo.getEnabled()){
			if (!target_temp_reached){
				if (iteration % thermo.getn_delta() == 0){
					temperature += thermo.getDelta_T();
					if (temperature > thermo.getT_target()){
						temperature -= thermo.getDelta_T();
						target_temp_reached = true;
					}
				}
			}

			if (iteration % thermo.getn_thermo() == 0){
				thermo.setThermo(particleList, 2, temperature);
			}
		}

		if (iteration % freq == 0 || outflow_flag) {
			lcContainer.updateCells();
			outflow_flag = false;
		}
		if (iteration % freq == 0) {
			LCplotVTK(iteration);
		}

		LOG4CXX_TRACE(molsimlogger, "Iteration " << iteration << " finished.");

		current_time += delta_t;

		//cout << float( clock () - beginTime ) /  CLOCKS_PER_SEC;
		//cin.ignore();
	}

	cout << "\nOutput written. Terminating..." << endl;
}

void LCcalculateFLJ() {

	utils::Vector<double, 3> zero((double) 0);
	utils::Vector<double, 3> sumF((double) 0);
	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	int i = 0;
	while (iterator != lcContainer.endOuter()) {
		i = iterator.getCellNumber();
		if (i > (lcContainer.endOuter()).getCellNumber()) {
			break;
		}
		sumF = zero;
		utils::LCInnerParticleIterator innerIterator = lcContainer.beginInner(
				iterator);
		while (innerIterator != lcContainer.endInner(i)) {
			assert(innerIterator != lcContainer.endInner(i));
			if (innerIterator.getCellNumber()
					> lcContainer.endInner(i).getCellNumber()
					|| innerIterator.getCellNumber()
							> lcContainer.endOuter().getCellNumber()) {
				break;
			}
			Particle& p1 = *iterator;
			Particle& p2 = *innerIterator;
			/*			cout << "Element: " << innerIterator.getCellNumber() << " "
			 //					<< p2.toString() << endl;
			 //			cout << "EndInner: " << ((*(lcContainer.endInner(i))).toString())
			 //					<< endl;*/
			if (p1 == p2) {
				++innerIterator;
				continue;
			} else {
				assert(!(p1 == p2));

				computeForce(p1, p2);

				++innerIterator;
			}
		}

		/* check if the left boundary will affect the force threw reflection */
		if ((*iterator).getX()[0] <= h) {
			if (domainCondition[0] == 1) {
				if ((*iterator).getX()[0] <= 0) {
					outflow_flag = true;
				} else if (domainCondition[0] == 2) {
					double x_arg[3] = { 0, (*iterator).getX()[1],
							(*iterator).getX()[2] };
					utils::Vector<double, 3> x(x_arg);
					utils::Vector<double, 3> v(0.0);
					Particle p(x, v, 1);
					computeForce((*iterator), p);
				}
			}
		}
		/* check if the right boundary will affect the force threw reflection */
		else if ((*iterator).getX()[0] >= domainSize[0] - h) {
			if (domainCondition[1] == 1) {
				if ((*iterator).getX()[0] >= domainSize[0]) {
					outflow_flag = true;
				} else if (domainCondition[1] == 2) {
					double x_arg[3] = { domainSize[0], (*iterator).getX()[1],
							(*iterator).getX()[2] };
					utils::Vector<double, 3> x(x_arg);
					utils::Vector<double, 3> v(0.0);
					Particle p(x, v, 1);
					computeForce((*iterator), p);
				}
			}
		}
		/* check if the bottom boundary will affect the force threw reflection */
		if ((*iterator).getX()[1] <= h) {
			if (domainCondition[2] == 1) {
				if ((*iterator).getX()[1] <= 0) {
					outflow_flag = true;
				} else if (domainCondition[2] == 2) {
					double x_arg[3] = { (*iterator).getX()[0], 0,
							(*iterator).getX()[2] };
					utils::Vector<double, 3> x(x_arg);
					utils::Vector<double, 3> v(0.0);
					Particle p(x, v, 1);
					computeForce((*iterator), p);
				}
			}
		}
		/* check if the upper boundary will affect the force threw reflection */
		else if ((*iterator).getX()[1] >= domainSize[1] - h) {
			if (domainCondition[3] == 1) {
				if ((*iterator).getX()[1] >= domainSize[1]) {
					outflow_flag = true;
				} else if (domainCondition[3] == 2) {
					double x_arg[3] = { (*iterator).getX()[0], domainSize[1],
							(*iterator).getX()[2] };
					utils::Vector<double, 3> x(x_arg);
					utils::Vector<double, 3> v(0.0);
					Particle p(x, v, 1);
					computeForce((*iterator), p);
				}
			}
		}
		/* check if the front boundary will affect the force threw reflection */
		if ((*iterator).getX()[2] <= h && depth > 0) {
			if (domainCondition[4] == 1) {
				if ((*iterator).getX()[2] < 0) {
					outflow_flag = true;
				} else if (domainCondition[4] == 2) {
					double x_arg[3] = { (*iterator).getX()[0],
							(*iterator).getX()[1], 0 };
					utils::Vector<double, 3> x(x_arg);
					utils::Vector<double, 3> v(0.0);
					Particle p(x, v, 1);
					computeForce((*iterator), p);
				}
			}
		}
		/* check if the rear boundary will affect the force threw reflection */
		else if ((*iterator).getX()[2] >= domainSize[2] - h && depth > 0) {
			if (domainCondition[5] == 1) {
				if ((*iterator).getX()[2] >= domainSize[2]) {
					outflow_flag = true;
				} else if (domainCondition[5] == 2) {
					double x_arg[3] = { (*iterator).getX()[0],
							(*iterator).getX()[1], domainSize[2] };
					utils::Vector<double, 3> x(x_arg);
					utils::Vector<double, 3> v(0.0);
					Particle p(x, v, 1);
					computeForce((*iterator), p);
				}
			}
		}

		// GRAVITY (G_CONST = 0 when gravity is disabled)
		double gDirection[] = {0.0, 1.0, 0.0};
		utils::Vector<double, 3> gDirVec(gDirection);
		utils::Vector<double, 3> gravForce(G_CONST*((*iterator).getM())*gDirVec);

		//(*iterator).setF((*iterator).getTempF());
		(*iterator).setF(gravForce + (*iterator).getTempF());
		(*iterator).deleteTempF();
		++iterator;
	}
}

void LCcalculateX() {

	utils::LCOuterParticleIterator iterator = lcContainer.beginOuter();
	while (iterator != lcContainer.endOuter()) {
		int i = iterator.getCellNumber();
		if (i > (lcContainer.endOuter()).getCellNumber()) {
			break;
		}
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
		if (i > (lcContainer.endOuter()).getCellNumber()) {
			break;
		}
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
void computeForce(Particle& p1, Particle& p2) {
	utils::Vector<double, 3> tempD = p2.getX() - p1.getX();
	double tempDNorm = tempD.L2Norm();
	if (tempDNorm < R_CUTOFF) {
		double tempDSigDivNorm = pow(SIGMA / tempDNorm, 6);
		utils::Vector<double, 3> tempF = 24 * EPSILON * pow(1 / tempDNorm, 2)
				* (tempDSigDivNorm - 2 * pow(tempDSigDivNorm, 2)) * tempD;
		p2.updateTempF((-1) * tempF);
		p1.updateTempF(tempF);
	}
}

void LCplotVTK(int iteration) {

	outputWriter::VTKWriter writer;
	list<Particle>::iterator iterator = (lcContainer.getList()).begin();
	writer.initializeOutput((lcContainer.getList()).size());
	while (iterator != (lcContainer.getList()).end()) {
		Particle& p = *iterator;
		writer.plotParticle(p);
		++iterator;
	}
	string out_name(outputMask);
	writer.writeFile(out_name, iteration);
}

void writeOutputFile(){
	ofstream file;
	file.open ("ParListStatus.txt", ios::trunc);
	file	<< "# file format:\n"
			<< "# Lines of comment start with '#' and are only allowed at the beginning of the file\n"
			<< "# Empty lines are not allowed.\n"
			<< "# The first line not being a comment has to be one integer, indicating the number of\n"
			<< "# molecule data sets.\n"
			<< "#\n"
			<< "# Molecule data consists of\n"
			<< "# * xyz-coordinates (3 double values)\n"
			<< "# * velocities (3 double values)\n"
			<< "# * force (3 double values)\n"
			<< "# * old force (3 double values)\n"
			<< "# * mass (1 double value)\n"
			<< "# * type (1 int value)\n"
			<< "#\n"
			<< "# "
				<< setw(45) << "xyz-coord"
				<< setw(45) << "velocity"
				<< setw(45) << "force"
				<< setw(45) << "old force"
				<< setw(15) << "mass"
				<< setw(10) << "type\n"
			<< particleList.size() << endl;
	for (list<Particle>::iterator it=particleList.begin();
			it!=particleList.end(); it++){
		file 	<< setw(15) << (*it).getX()[0]
		     	<< setw(15) << (*it).getX()[1]
		     	<< setw(15) << (*it).getX()[2]

		     	<< setw(15) << (*it).getV()[0]
				<< setw(15) << (*it).getV()[1]
				<< setw(15) << (*it).getV()[2]

				<< setw(15) << (*it).getF()[0]
				<< setw(15) << (*it).getF()[1]
				<< setw(15) << (*it).getF()[2]

				<< setw(15) << (*it).getOldF()[0]
				<< setw(15) << (*it).getOldF()[1]
				<< setw(15) << (*it).getOldF()[2]

				<< setw(15) << (*it).getM()
				<< setw(10) << (*it).getType() << endl;
	}
	file.close();
}
