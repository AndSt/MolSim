/*
 * ParticleGenerator.h
 *
 *  Created on: 13.11.2013
 *      Author: Son
 */

#ifndef PARTICLEGENERATOR_H_
#define PARTICLEGENERATOR_H_

#include "Cuboid.h"

#include <list>

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
	std::list<Cuboid> cuboids;

public:
	/** Default constructor.
	 */
	ParticleGenerator();

	/** Main constructor, which creates a particle generator from a list of cuboids.
	 * @param[in] cubList A list of cuboids.
	 */
	ParticleGenerator(std::list<Cuboid> cubList);

	/** The reading procedure, which can convert information from a given input file into particle generator's list of cuboids.
	 * @param[in] filename The full name of the input file in the project folder, e.g: "eingabe-brownian.txt".
	 */
	void readCuboids(char* filename);

	/** Converts particle generator's list of cuboids into one single list of particles
	 * @param[out] list The result will be stored here.
	 */
	void cuboidsToList(std::list<Particle>& list);

	/** \return Particle generator's list of cuboids.
	 */
	std::list<Cuboid>& getCuboids();

	virtual ~ParticleGenerator();
};

#endif /* PARTICLEGENERATOR_H_ */
