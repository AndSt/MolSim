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
	 * fills the particles list
	 * @param the list
	 */
	void initialize(std::list<Particle>& particles_arg);

	/**
	 * @return the first element of the container
	 */
	ParticleIterator begin();

	/**
	 * @return the last element of the container
	 */
	ParticleIterator end();

	/**
	 * @ return the particles list
	 */
	std::list<Particle> getList();

	/**
	 * @ return the size of the size
	 */
	int size();

private:
	/**
	  * contains the list of the given particles
	  */
	std::list<Particle> particles;
};


#endif /* PARTICLECONTAINER_H_ */
