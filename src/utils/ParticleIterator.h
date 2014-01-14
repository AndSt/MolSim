/*
 * ParticleIterator.h
 *
 *  Created on: Oct 29, 2013
 *      Author: andal
 */

#ifndef PARTICLEITERATOR_H_
#define PARTICLEITERATOR_H_

#include <list>
#include <Particle.h>

namespace utils{

class ParticleIterator {

public:

	ParticleIterator();

	/**
	 * assigns the iterator to an iterator
	 */
	ParticleIterator(std::list<Particle*>::iterator iterator_arg);

	virtual ~ParticleIterator();


	/**
	 * @return returns the reference to the momentary particle
	 */
	Particle& operator*() const;

	/**
	 * iterates to the next element
	 */
	void operator++();

	/**
	 * checks on inequality
	 * @param b the Iterator to compare with
	 * @return returns true, if the two iterators don't match
	 */
	bool operator!=(const ParticleIterator b);

private:
	/**
	 * the element of the iterator
	 */
	std::list<Particle*>::iterator iterator;

};

}


#endif /* PARTICLEITERATOR_H_ */
