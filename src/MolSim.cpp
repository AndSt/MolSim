#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "utils/Vector.h"
#include "utils/ParticleContainer.h"
#include "utils/ParticleIterator.h"

#include <list>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

// plot the particles to VTKWriter-File
void plotVTK(int iteration);

double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;

std::list<Particle> particles;
ParticleContainer container;


/**
 * @param argsv the first parameter is the file. ( here "eingabe-sonne.txt")
 * The second parameter is the end_time.
 * The third parameter is  delta_t.
 */
int main(int argc, char* argsv[]) {

	cout << "Hello from MolSim for PSE!" << endl;
	cout << "[1]. Koordinaten; [2]. end_time; [3]. delta_t." << endl;
	if (argc != 4) {
		cout << "Errounous programme call! " << endl;
		cout << "./molsym filename" << endl;
	}

	FileReader fileReader;
	fileReader.readFile(particles, argsv[1]);

	container.initialize(particles);

	// the forces are needed to calculate x, but are not given in the input file.
	calculateF();

	double current_time = start_time;

	int iteration = 0;

	// end_time und delta_t eingegeben via command line
	end_time = (double) atof(argsv[2]);
	delta_t = (double) atof(argsv[3]);

	// for this loop, we assume: current x, current f and current v are known
	while (current_time < end_time) {
		// calculate new x
		calculateX();

		// calculate new f
		calculateF();
		// calculate new v
		calculateV();

		iteration++;
		if (iteration % 10 == 0) {
			//plotParticles(iteration);
			plotVTK(iteration);
		}
		cout << "Iteration " << iteration << " finished." << endl;

		current_time += delta_t;
	}

	cout << "output written. Terminating..." << endl;
	return 0;
}

/**
 * This method calculates the forces between the particles.
 * The calculation obeys the simple force calculation.
 */
void calculateF() {

	ParticleIterator iterator;
	iterator = container.begin();
	while (iterator != container.end()) {

		ParticleIterator innerIterator;
		innerIterator = container.begin();
		//sum von Fij fuer alle j (i fest)
		utils::Vector<double, 3> sumFi((double) 0);
		while (innerIterator != container.end()) {
			if (innerIterator != iterator) {

				Particle& p1 = *iterator; //i
				Particle& p2 = *innerIterator; //j

				// insert calculation of force here!
				utils::Vector<double, 3> tempD = p1.getX() - p2.getX();
				utils::Vector<double, 3> tempF = (p1.getM() * p2.getM()
						/ (pow((tempD.L2Norm()), 3))) * (-1) * tempD;
				sumFi += tempF;
			}
			++innerIterator;
		}
		(*iterator).setF(sumFi);
		++iterator;
	}
}

/**
 *  This method calculates the position of the particles.
 *  It obeys the Velocity-St�rmer-Verlet-Algorithm.
 */
void calculateX() {

	ParticleIterator iterator;
	iterator = container.begin();
	while (iterator != container.end()) {

		Particle& p = *iterator;

		// insert calculation of X here!
		utils::Vector<double, 3> tempX = p.getX() + delta_t * p.getV()
				+ ((delta_t) * (delta_t) / (2 * p.getM())) * p.getOldF();
		p.setX(tempX);

		++iterator;
	}
}

/**
 *  This method calculates the position of the particles.
 *  It obeys the Velocity-St�rmer-Verlet-Algorithm.
 */
void calculateV() {

	ParticleIterator iterator;
	iterator = container.begin();
	while (iterator != container.end()) {

		Particle& p = *iterator;

		// insert calculation of velocity here!
		utils::Vector<double, 3> tempV = p.getV()
				+ (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());
		p.setV(tempV);
		++iterator;
	}
}

void plotParticles(int iteration) {

	string out_name("MD_vtk");

	outputWriter::XYZWriter writer;
	writer.plotParticles(particles, out_name, iteration);

}

/**
 * This method writes the output VTK files.
 */
void plotVTK(int iteration) {
	outputWriter::VTKWriter writer;
	ParticleIterator iterator;
	iterator = container.begin();
	writer.initializeOutput(container.particles.size());
	while (iterator != container.end()) {
		Particle& p = *iterator;

		writer.plotParticle(p);
		++iterator;
	}
	string out_name("MD1_vtk");
	writer.writeFile(out_name, iteration);
}
