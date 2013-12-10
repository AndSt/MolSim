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
 *  \brief This is a class capsulating (almost) all work related to cuboids and spheres.
 * 
 *  A particle generator contains a list of cuboids/spheres 
 *  and is therefore able to initialize a set of particles into cuboids/spheres.
 *  Extracting needed information from an output file into cuboids/spheres
 *  and converting cuboids/spheres into one single list of particles are possible in this class.
 */
class ParticleGenerator {
private:
	/** A list of cuboids, each cuboid is an instance of class Cuboid.*/
	std::list<Cuboid> cuboidList;

	/** A list of spheres, each sphere is an instance of class Sphere.*/
	std::list<Sphere> sphereList;

	/** The particles of either cuboids or spheres will be stored here.*/
	std::list<Particle> particleList;

public:
	/** Default constructor.
	 */
	ParticleGenerator();

	/** Main cuboid constructor, which creates a particle generator from a list of cuboids.
	 * @param[in] cubList A list of cuboids.
	 */
	ParticleGenerator(std::list<Cuboid>& cubList);

	/** Main particle constructor, which creates a particle generator from a list of untructered particles.
	 * @param[in] parList A list of particles.
	 */
	ParticleGenerator(std::list<Particle>& parList);

	/** Main sphere constructor, which creates a particle generator from a list of spheres.
	 * @param[in] sphList A list of spheres.
	 */
	ParticleGenerator(std::list<Sphere>& sphList);

	/** The reading procedure, which can convert information 
	 *  from a given TXT input file into particle generator's list of cuboids.
	 *
	 * @param[in] filename Name of the input file (e.g: "eingabe-brownian.txt").
	 * @param[out] cubList The cuboids will be stored here.
	 */
	void readCuboids(char* filename);
	
	/** The reading procedure, which can extract all information needed
	 *  for configuring the simulation from a given XML input file .
	 *
	 * @param[out] start_time Start time of simulation will be stored here.
	 * @param[out] end_time End time of simulation will be stored here.
	 * @param[out] delta_t Delta time (between 2 iterations) of simulation will be stored here.
	 * @param[out] EPSILON Needed for Lennard Jones Force.
	 * @param[out] SIGMA Needed for Lennard Jones Force.
	 * @param[out] inputNames A list of XML input names, which will be extracted.
	 * @param[out] inputTypes A list of types each XML input name has ("cuboids"/"spheres").
	 * @param[out] outputMask Output files will named after this mask.
	 * @param[out] outputFreq How many iterations it takes to write an output file.
	 * @param[out] domainSize A 3D vector indicating size of the domain (Linked Cell Algorithm).
	 * @param[out] r_cutoff Cutoff radius (Short Range Algorithm).
	 * @param[out] domainBoundCond Saves boundary conditions ("outflow"/"reflecting") for 6 sides of domain.
	 * @param[out] g_const The constant g of gravitational force
	 */
	void extractSetting(double& start_time, double& end_time, double& delta_t, 
				double& EPSILON, double& SIGMA, 
				std::list<string>& inputNames, std::list<string>& inputTypes, 
				string& outputMask, int& outputFreq, 
				utils::Vector<double, 3>& domainSize, double& r_cutoff, 
				std::vector<int>& domainBoundCond, double& g_const);

	/** The reading procedure, which can convert information 
	 *  from a given XML input file into particle generator's list of unstructered particles.
	 *
	 * @param[in] filename Name of the input file (e.g: "InputParticles.xml").
	 * @param[out] particleList The particles will be stored here.
	 */
	void extractParticles(const string filename);

	/** The reading procedure, which can convert information 
	 *  from a given XML input file into particle generator's list of cuboids.
	 *
	 * @param[in] filename Name of the input file (e.g: "InputCuboids.xml").
	 * @param[out] cubList The cuboids will be stored here.
	 */
	void extractCuboids(const string filename);

	/** The reading procedure, which can convert information 
	 *  from a given XML input file into particle generator's list of spheres.
	 *
	 * @param[in] filename Name of the input file (e.g: "InputSpheres.xml").
	 * @param[out] sphList The spheres will be stored here.
	 */
	void extractSpheres(const string filename);

	/** Converts particle generator's list of cuboids into one single list of particles.
	 * @param[out] particleList The result will be stored here.
	 */
	void cuboidsToList();

	/** Converts particle generator's list of spheres into one single list of particles.
	 * @param[out] particleList The result will be stored here.
	 */
	void spheresToList();

	// particleList stands behind
	/** Merge with a given list, which will stand BEFORE particleList.
	 * @param[in] before This list will be merged.
	 * @param[in] particleList All elements of this list will be added into the gear side of before.
	 * @param[out] before The new elements will be pushed into before's back.
	 */
	void mergeWithParticleList(std::list<Particle>& before);

	/** \return Particle generator's list of cuboids.*/
	std::list<Cuboid>& getCuboidList();

	/** \return Particle generator's list of spheres.*/
	std::list<Sphere>& getSphereList();

	/** \return Particle generator's list of particles.*/
	std::list<Particle>& getParticleList();

	virtual ~ParticleGenerator();
};

}
#endif /* PARTICLEGENERATOR_H_ */
