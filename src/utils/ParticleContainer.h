/*
 * ParticleContainer.h
 *
 *  Created on: Oct 23, 2013
 *      Author: andal
 */

#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <list>
#include <Particle.h>
#include "Vector.h"
#include "ParticleIterator.h"


class ParticleContainer {

public:


	ParticleContainer();
	~ParticleContainer();

	/**
	 * contains the list of the given particles
	 */
	std::list<Particle> particles;

	/**
	 * fills the particles list
	 * @param the list
	 */
	void initialize(std::list<Particle> particles_arg);

	/**
	 * @return returns the first element of the container
	 */
	ParticleIterator begin();

	/**
	 * @return returns the last element of the container
	 */
	ParticleIterator end();

private:

};


#endif /* PARTICLECONTAINER_H_ */
