/*
 * ParticleContainer.h
 *
 *  Created on: Oct 23, 2013
 *      Author: andal
 */

#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include "Vector.h"
#include "ParticleIterator.h"
#include "Particle.h"

#include <cstring>
#include <list>

class ParticleContainer {

public:

	ParticleContainer();

	/**
	 * @return the first element of the container
	 */
	virtual ParticleIterator begin() = 0;

	/**
	 * @return the last element of the container
	 */
	virtual ParticleIterator end() = 0;

	/**
	 * @ return the particles list
	 */
	virtual std::list<Particle>& getList() = 0;

	/**
	 * @ return the size of the size
	 */
	virtual int size() = 0;

	virtual ~ParticleContainer();
};


#endif /* PARTICLECONTAINER_H_ */
