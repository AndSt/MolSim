#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "Particle.h"
#include "Cuboid.h"
#include "utils/Vector.h"
#include "utils/ParticleContainer.h"
#include "utils/ParticleIterator.h"
#include "utils/ParticleGenerator.h"

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
#include <cstdlib>
#include <iostream>

using namespace std;

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
 * calculate the position for all particles
 */
void calculateV();

// plot the particles to VTKWriter-File
void plotVTK(int iteration);

double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;

// For Lennard-Jones
const double SIGMA = 1;
const double EPSILON = 5;

list<Particle> particles;
ParticleContainer container;
ParticleGenerator pgen;

/**
 * @param argsv the first parameter is the file. ( here "eingabe-sonne.txt")
 * The second parameter is the end_time.
 * The third parameter is delta_t.
 */
int main(int argc, char* argsv[]) {

	/* Format input command line:
	 * ./MolSim <input file> <end time> <delta time>
	 * Example for input command line:
	 * ./MolSim "eingabe-sonne.txt" 1000 0.014
	 * ./MolSim "eingabe-brownian.txt" 5 0.0002
	 *
	 */
	bool test = false;
	if(argc >= 2){
	string arg1 = argsv[1];
	test = true;
	}
	if (test == true) {

		string str;
		int option = 0;
		while (option != 3) {
			cout << "Enter '1', if you want to test all unit tests." << endl;
			cout << "Enter '2', if you want to test a specific unit test."
					<< endl;
			cout << "Enter '3', if you want to exit the 'test suite'." << endl;
			cout << endl;
			while (true) {
				getline(cin, str);
				stringstream myStream(str);
				if (myStream >> option)
					break;
				cout << "Invalid number, please try again" << endl;
			}

			if (option == 1) {

				CppUnit::TextUi::TestRunner runner;
				runner.addTest(ParticleIteratorTest::suite());
				runner.addTest(ParticleContainerTest::suite());
				runner.run();

			} else if (option == 2) {
				cout << "Enter '1', if you want to test the ParticleContainer."
						<< endl;
				cout << "Enter '2', if you want to test the ParticleIterator."
						<< endl;
				cout << "Enter '3', if you want to test the ParticleGenerator."
						<< endl;

				while (true) {
					getline(cin, str);
					stringstream myStream(str);
					if (myStream >> option)
						break;
					cout << "Invalid number, please try again" << endl;
				}
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
	} else {
		string str;
		FileReader fileReader;
		cout << "Hello from MolSim for PSE!" << endl;
		cout << endl;
		cout
				<< "Enter '1', if you want to run the program with a particle file."
				<< endl;
		cout << "Enter '2', if you want to run program with a cuboid file."
				<< endl;
		int option1, option2;

		while (true) {
			getline(cin, str);
			stringstream myStream(str);
			if (myStream >> option1)
				break;
			cout << "Invalid number, please try again" << endl;
		}

		switch (option1) {
		case 1:
			cout << "Enter '1', if you want the default configuration: "
					<< endl;
			cout << "         file -'eingabe-sonne.txt'" << endl;
			cout << "         end time - 1000" << endl;
			cout << "         delta t - 0.014" << endl;
			cout << "Enter '2', if you want a different configuration" << endl;
			break;
		case 2:
			cout << "Enter '1', if you want the default configuration: "
					<< endl;
			cout << "         file -'eingabe-brownian.txt'" << endl;
			cout << "         end time - 5" << endl;
			cout << "         delta t - 0.0002" << endl;
			cout << "Enter '2', if you want a different configuration" << endl;
			break;
		}

		while (true) {
			getline(cin, str);
			stringstream myStream(str);
			if (myStream >> option2)
				break;
			cout << "Invalid number, please try again" << endl;
		}

		if (option1 == 1) {
			switch (option2) {
			case 1:
				fileReader.readFile(particles, "eingabe-sonne.txt");
				delta_t = 0.014;
				end_time = 1000;
				break;
			}
		} else if (option1 == 2) {
			switch (option2) {
			case 1:
				pgen.readCuboids("eingabe-brownian.txt");
				delta_t = 0.0002;
				end_time = 5;
				break;
			}

			pgen.cuboidsToList(particles);
		}

		cout << "Reading input file..." << endl;

		container.initialize(particles);

		simulate();
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
		//calculateF();
		calculateFLJ();

		// calculate new v
		calculateV();

		iteration++;
		if (iteration % 10 == 0) {
			plotVTK(iteration);
		}
		cout << "Iteration " << iteration << " finished." << endl;

		current_time += delta_t;
	}

	cout << "output written. Terminating..." << endl;
}

/**
 * This method calculates the forces between the particles.
 * The calculation obeys the Lennard-Jones force between two molecules.
 */
void calculateFLJ() {

//initialize outer Iterator and index
	utils::Vector<double, 3> zero((double) 0);
	ParticleIterator iterator;
	utils::Vector<double, 3> sumF[container.size()];
	for (int i = 0; i < container.size(); i++) {
		sumF[i] = zero;
	}
	iterator = container.begin();
	int i = 0;
	while (iterator != container.end()) {

		//initialize inner Iterator and Index
		ParticleIterator innerIterator;
		innerIterator = iterator;
		++innerIterator;
		int j = i + 1;

		while (innerIterator != container.end()) {

			Particle& p1 = *iterator;
			Particle& p2 = *innerIterator;

			//calculations
			utils::Vector<double, 3> tempD = p1.getX() - p2.getX();
			double tempDNorm = tempD.L2Norm();
			double tempDSigDivNorm = SIGMA / tempDNorm;
			utils::Vector<double, 3> tempF = 24 * EPSILON
					* pow(1 / tempDNorm, 2)
					* (pow(tempDSigDivNorm, 6) - 2 * pow(tempDSigDivNorm, 12))
					* (-1) * tempD;

			sumF[i] += tempF;
			sumF[j] += (-1) * tempF;
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

	ParticleIterator iterator;
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

	ParticleIterator iterator;
	iterator = container.begin();
	while (iterator != container.end()) {

		Particle& p = *iterator;

		utils::Vector<double, 3> tempV = p.getV()
				+ (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());

		p.getV() = tempV;
		++iterator;
	}
}

/**
 * This method writes the output VTK files.
 */
void plotVTK(int iteration) {
	outputWriter::VTKWriter writer;
	ParticleIterator iterator;
	iterator = container.begin();
	writer.initializeOutput(container.size());
	while (iterator != container.end()) {
		Particle& p = *iterator;

		writer.plotParticle(p);
		++iterator;
	}
	string out_name("MD1_vtk");
	writer.writeFile(out_name, iteration);
}
