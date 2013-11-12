/*
 * List.h
 *
 *  Created on: 12.11.2013
 *      Author: Son
 */

#ifndef LIST_H_
#define LIST_H_

#include "ParticleIterator.h"

#include<list>

class List : public ParticleContainer{
public:
	List();

	List(const std::list<Particle>& particles_arg);

	ParticleIterator begin();

	ParticleIterator end();

	std::list<Particle>& getList();

	int size();

	~List();

private:
	std::list<Particle> particles;
};

#endif /* LIST_H_ */
