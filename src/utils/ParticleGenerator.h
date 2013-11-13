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

class ParticleGenerator {
private:
	std::list<Cuboid> cuboids;



public:
	ParticleGenerator();

	ParticleGenerator(std::list<Cuboid> cubList);
	
	// Initialize with an input file
	ParticleGenerator(char* filename);

	void readCuboids(char* filename);

	void cuboidsToList(std::list<Particle>& list);

	std::list<Cuboid>& getCuboids();

	virtual ~ParticleGenerator();
};

#endif /* PARTICLEGENERATOR_H_ */
