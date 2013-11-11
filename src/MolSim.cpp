#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "utils/Vector.h"
#include "Particle.h"
#include "utils/ParticleContainer.h"
#include "utils/ParticleIterator.h"
#include "Cuboid.h"

#include <list>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iostream>


using namespace std;

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
//void calculateF();

// New calculation for force according to Lennard-Jones
void calculateFLJ();

// Convert a list of cuboids to a list of particles
void cuboidsToList(list<Cuboid>& cubList, list<Particle>& list);

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

// For Lennard-Jones
const double SIGMA = 1;
const double EPSILON = 5;

list<Particle> particles;
ParticleContainer container;

// List of cuboids
list<Cuboid> cuboids;

/**
 * @param argsv the first parameter is the file. ( here "eingabe-sonne.txt")
 * The second parameter is the end_time.
 * The third parameter is  delta_t.
 */
int main(int argc, char* argsv[]) {

	/* Format input command line:
	 * ./MolSim <input file> <end time> <delta time>
	 * Example for input command line:
	 * ./MolSim "eingabe-sonne.txt" 1000 0.014
	 * ./MolSim "eingabe-brownian.txt" 1000 0.014
	 *
	 */
	cout << "Hello from MolSim for PSE!" << endl;
	cout << "./MolSim <input file> <end time> <delta time>" << endl;
	if (argc != 4) {
		cout << "Errounous programme call! " << endl;
		exit(-1);
	}

	cout << "Reading input file..." << endl;
	FileReader fileReaderCub;
	fileReaderCub.readFileCub(cuboids, argsv[1]);

	// Via input file
	//FileReader fileReader;
	//fileReader.readFile(particles, argsv[2]);

	container.initialize(particles);
	cuboidsToList(cuboids, particles);

	// the forces are needed to calculate x, but are not given in the input file.
	//calculateF();
	calculateFLJ();

	double current_time = start_time;

	int iteration = 0;

	// Via command line (but also for via input file)
	end_time = (double) atof(argsv[2]);
	delta_t = (double) atof(argsv[3]);

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
/*
void calculateF() {

	ParticleIterator iterator;
	iterator = container.begin();
	while (iterator != container.end()) {

		ParticleIterator innerIterator;
		innerIterator = container.begin();

		utils::Vector<double, 3> sumFi((double) 0);
		while (innerIterator != container.end()) {
			if (innerIterator != iterator) {

				Particle& p1 = *iterator; //i
				Particle& p2 = *innerIterator; //j

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
*/

// Convert a list of cuboids to one single list of particles
void cuboidsToList(list<Cuboid>& cubList, list<Particle>& list){
	list.clear();
	if (cubList.size() == 0){
		cout << "Cuboid list is empty!" << endl;
		exit(-1);
	}

	// Size >= 1
	/*
	std::list<Cuboid>::iterator iterator = cubList.begin();
	Cuboid& temp1 = *iterator;
	list = temp1.getCuboid();
	iterator++;
	for (; iterator != cubList.end(); iterator++) {
		Cuboid& temp2 = *iterator;
		list.merge(temp2.getCuboid());
	}*/
	
	std::list<Cuboid>::iterator iterator;
	for (iterator = cubList.begin(); iterator != cubList.end(); iterator++){
		Cuboid& temp = *iterator;
		std::list<Particle>::iterator iterator1;
		for (iterator1 = temp.getCuboid().begin(); iterator1 != temp.getCuboid().end(); iterator1++){
			Particle& tempP = *iterator1;
			list.push_back(tempP);
		}
	}
}
// New calculateF() with Lennard-Jones
/*
void calculateFLJ(){
	// Symmetric matrix nxn for calculating Fij (only once per pair)
	vector<vector<utils::Vector<double, 3> > > matrix;
	matrix.resize(particles.size());
	for (int i = 0; i < particles.size(); i++) {
		matrix[i].resize(particles.size());
	}

	// Index runs vertically
	int i = 0;

	// Index runs horizontally
	int j = 0;

	// Sum Fij for all j, i fixed
	double ss[] = {0,0,0};
	utils::Vector<double, 3> sumFi(ss);

	std::list<Particle>::iterator iterator;
	for (iterator = particles.begin(); iterator != particles.end(); iterator++) {
		Particle& temp = *iterator;
		std::list<Particle>::iterator iterator1;
		j = 0;
		sumFi = utils::Vector<double, 3> (ss);
		for (iterator1 = particles.begin(); iterator1 != particles.end(); iterator1++) {
			Particle& temp1 = *iterator1;
			if (i==j)
				matrix[i][j] = utils::Vector<double,3>(ss);
			else if (i<j){
				// Calculate Fij
				utils::Vector<double, 3> tempD = temp1.getX() - temp.getX();
				matrix[i][j] = 24*EPSILON*pow(1/(tempD.L2Norm()),2)*(pow(SIGMA/tempD.L2Norm(),6)-2*pow(SIGMA/tempD.L2Norm(),12))*tempD;
			}
			else
				// The third Newton's law
				matrix[i][j] = (-1)*matrix[j][i];

			// Sum up the Fij for all j, i fixed
			sumFi += matrix[i][j];
			j++;
		}
		temp.setF(sumFi);
		i++;
	}
}*/

// New calculateF() with Lennard-Jones
void calculateFLJ() {
	
	//initialize outer Iterator and index
	utils::Vector<double, 3> zero((double) 0);
	ParticleIterator iterator;
	utils::Vector<double, 3> sumF[container.size()];
	for(int i = 0; i < container.size(); i++)
	{
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
			double tempDSigDivNorm = SIGMA/tempDNorm;
			utils::Vector<double, 3> tempF = 24*EPSILON*pow(1/tempDNorm,2)*(pow(tempDSigDivNorm,6)-2*pow(tempDSigDivNorm,12))*tempD*(-1);
			
			
			sumF[i] += tempF;
			sumF[j] += (-1)*tempF;
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
	std::list<Particle>::iterator iterator;
	for (iterator = particles.begin(); iterator != particles.end(); iterator++) {
		Particle& p = *iterator;
		utils::Vector<double, 3> tempX = p.getX() + delta_t * p.getV() + ((delta_t) * (delta_t) / (2 * p.getM())) * p.getOldF();
		p.getX() = tempX;
	}
}

/**
 *  This method calculates the position of the particles.
 *  It obeys the Velocity-Stoermer-Verlet-Algorithm.
 */
void calculateV() {
	std::list<Particle>::iterator iterator;
	for (iterator = particles.begin(); iterator != particles.end(); iterator++) {
		Particle& p = *iterator;
		utils::Vector<double, 3> tempV = p.getV() + (delta_t / (2 * p.getM())) * (p.getF() + p.getOldF());
		p.getV() = tempV;
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
	writer.initializeOutput(particles.size());
	std::list<Particle>::iterator iterator;
	for (iterator = particles.begin(); iterator != particles.end(); iterator++) {
		Particle& p = *iterator;
		writer.plotParticle(p);
	}

	string out_name("MD1_vtk");
	writer.writeFile(out_name, iteration);
}

