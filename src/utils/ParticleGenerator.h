/*
 * ParticleGenerator.h
 *
 *  Created on: 13.11.2013
 *      Author: Son
 */

#ifndef PARTICLEGENERATOR_H_
#define PARTICLEGENERATOR_H_

#include "Cuboid.h"
#include "Particle.h"
#include "Sphere.h"

#include <list>
#include <vector>
#include <string>

using namespace std;

namespace utils {

/** \class ParticleGenerator
 *  \brief This is a class capsulating (almost) all work related to cuboids.
 * 
 *  A particle generator contains a list of cuboids and is therefore able to initialize a set of particles into cuboids.
 *  Extracting needed information from an output file into cuboids and converting cuboids into one single list of particles are possible in this class.
 */
class ParticleGenerator {
private:
	/** A list of cuboids, each cuboid is an instance of class Cuboid.
	 */
	std::list<Cuboid> cuboidList;

	std::list<Sphere> sphereList;

	std::list<Particle> particleList;

public:
	/** Default constructor.
	 */
	ParticleGenerator();

	/** Main constructor, which creates a particle generator from a list of cuboids.
	 * @param[in] cubList A list of cuboids.
	 */
	ParticleGenerator(std::list<Cuboid>& cubList);

	ParticleGenerator(std::list<Particle>& parList);

	ParticleGenerator(std::list<Sphere>& sphList);

	/** The reading procedure, which can convert information from a given input file into particle generator's list of cuboids.
	 * @param[in] filename The full name of the input file in the project folder, e.g: "eingabe-brownian.txt".
	 */
	void readCuboids(char* filename);
	
	void extractSetting(double& start_time, double& end_time, double& delta_t, double& EPSILON, double& SIGMA, 
				std::list<string>& inputNames, std::list<string>& inputTypes, string& outputMask, int& outputFreq, 
				utils::Vector<double, 3>& domainSize, double& r_cutoff, 
				std::vector<string>& domainBoundCond);

	void extractParticles(const string filename);

	void extractCuboids(const string filename);

	void extractSpheres(const string filename);

	/** Converts particle generator's list of cuboids into one single list of particles
	 * @param[out] particleList The result will be stored here.
	 */
	void cuboidsToList();

	void spheresToList();

	// particleList stands behind
	void mergeWithParticleList(std::list<Particle>& before);

	/** \return Particle generator's list of cuboids.
	 */
	std::list<Cuboid>& getCuboidList();

	std::list<Sphere>& getSphereList();

	std::list<Particle>& getParticleList();

	virtual ~ParticleGenerator();
};

}
#endif /* PARTICLEGENERATOR_H_ */
