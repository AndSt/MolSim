/*
 * LCOuterParticleIterator.h
 *
 *  Created on: Nov 28, 2013
 *      Author: andal
 */


#ifndef LCOuterPARTICLEITERATOR_H_
#define LCOuterPARTICLEITERATOR_H_

#include <list>
#include <Particle.h>
#include <vector>
#include "LCInnerParticleIterator.h"

namespace utils {

class LCOuterParticleIterator {
public:

	LCOuterParticleIterator();

	LCOuterParticleIterator(int cell_size_arg,
			std::vector<std::list<Particle *> *>* cells_arg, std::list<Particle *>::iterator iterator_arg,
			int index_arg);

	virtual ~LCOuterParticleIterator();

	/**
	 * @return returns the reference to the momentary particle
	 */
	Particle& operator*() const;

	/**
	 * iterates to the next element
	 */
	void operator++();

	int getCellNumber();

	std::list<Particle *>::iterator getIterator();

	/**
	 * checks on inequality
	 * @param b the Iterator to compare with
	 * @return returns true, if the two iterators don't match
	 */
	bool operator!=(const LCOuterParticleIterator b);

	LCOuterParticleIterator& operator=(const LCOuterParticleIterator& cpy);

private:
	/**
	 * the element of the iterator
	 */
	std::vector<std::list<Particle *> *>* cells;
	int cell_size;
	int index;
	std::list<Particle *>::iterator iterator;
};
} /* namespace utils */

#endif /* LCOuterPARTICLEITERATOR_H_ */
