#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "Particle.h"
#include "Cuboid.h"
#include "utils/Vector.h"
#include "utils/ParticleContainer.h"
#include "utils/ParticleIterator.h"
#include "utils/ParticleGenerator.h"

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

#include <list>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;

/**** forward declaration of the calculation functions ****/

void simulate();

/**
 * calculate the force for all particles, according to Lennard-Jones
 */
void calculateFLJ();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the velocity for all particles
 */
void calculateV();

void getIntegerInput(string &str, int &input);

void getDoubleInput(string &str, double &input);

// plot the particles to VTKWriter-File
void plotVTK(int iteration);

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

// For Linked Cell Algorithm
double R_CUTOFF = 3.0;
utils::Vector<double, 3> domainSize;

list<Particle> particleList;
utils::ParticleContainer container;
utils::ParticleGenerator pgen;

string fileName;

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
		if(arg1 == "-test") test = true;
	}

	/*
	 * "Testing suite": Read in the Options and run the TestRunner
	 */
	if (test == true) {

		LOG4CXX_INFO(molsimlogger, "Arrived @ testsuite.");

		string str;
		int option = 0;

		cout << "Here are the testing options: " << endl;
		cout << "Tipp: If you Enter Option '1' or '2' you will get back to this menu";
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
		cout << "Hello from MolSim for PSE!" << endl;
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
		cout << "Enter '3', if you want to run program with xml input files." << endl;

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
			cout << "\tInputSetting: contains start_time, end_time, delta_t,\
					\n\t\t inputfile name, inputfile type, output mask\
				 	\n\t\t and output frequency." << endl;
			cout << "\tInputParticles: contains all information needed for particles." << endl;
			cout << "\tInputCuboids: contains all information needed for cuboids." << endl;
			cout << "Press 1 to continue." << endl;
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
		else if (option1 == 3){
			//doesn't care about option2
			//getting information from InputSetting first
			pgen.extractSetting(start_time, end_time, delta_t, EPSILON, SIGMA, inputNames, inputTypes, outputMask, freq,
 								domainSize, R_CUTOFF);
			particleList.clear();
			list<string>::iterator itT = inputTypes.begin();
			int i = 1;
			cout << i << ". input file: " << "[spheres]" << endl;
			pgen.extractSpheres("InputSpheres.xml");
			pgen.spheresToList();
			particleList = pgen.getParticleList();
			/*for (list<string>::iterator itN = inputNames.begin(); itN != inputNames.end(); itN++){
				if (*itT=="particles"){
					cout << i << ". input file: " << "[particles]." << endl;
					pgen.extractParticles(*itN);
					particleList.insert(particleList.end(), 
							pgen.getParticleList().begin(), pgen.getParticleList().end());
				}else if (*itT=="cuboids"){
					cout << i << ". input file: " << "[cuboids]" << endl;
					pgen.extractCuboids(*itN);
					pgen.cuboidsToList();					
					particleList.insert(particleList.end(), 
							pgen.getParticleList().begin(), pgen.getParticleList().end());
				}else{
					cout << i << ". input file: " << "[spheres]" << endl;
					pgen.extractSpheres(*itN);
					pgen.spheresToList();				
					particleList.insert(particleList.end(), 
							pgen.getParticleList().begin(), pgen.getParticleList().end());
				}
				itT++;
				i++;
			}*/
			cout << "Press enter to continue..." << endl;
			cin.ignore();
		}

		cout << "Reading input file..." << endl;

		//inintialize container with particle list
		LOG4CXX_INFO(molsimlogger, "Arrived @ initialization call.");
		container.initialize(particleList);

		//start simulation
		LOG4CXX_INFO(molsimlogger, "Arrived @ simulation call.");

		cout << "Running simulation..." << endl;

		simulate();
		LOG4CXX_INFO(molsimlogger, "Arrived @ ending simulation.");
	}
	return 0;
}


void simulate() {
// the forces are needed to calculate x, but are not given in the input file.
//calculateF();
	calculateFLJ();

	double current_time = start_time;

	int iteration = 0;

// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x
		calculateX();

		// calculate new f
		calculateFLJ();

		// calculate new v
		calculateV();

		iteration++;
		if (iteration % freq == 0) {
			plotVTK(iteration);
		}
		//cout << "Iteration " << iteration << " finished." << endl;
		LOG4CXX_TRACE(molsimlogger, "Iteration " << iteration << " finished.");

		current_time += delta_t;
	}

	cout << "Output written. Terminating..." << endl;
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
				utils::Vector<double, 3> tempF = 24 * EPSILON
					* pow(1 / tempDNorm, 2)
					* (tempDSigDivNormPowSix - 2 * pow(tempDSigDivNormPowSix, 2))
					* tempD;

				sumF[i] += tempF;
				sumF[j] += (-1) * tempF;
			//}
			++innerIterator;
			++j;
		}

		(*iterator).setF(sumF[i]);
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

		writer.plotParticle(p);
		++iterator;
	}
	string out_name(outputMask);
	writer.writeFile(out_name, iteration);
}
