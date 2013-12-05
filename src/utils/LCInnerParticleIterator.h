/*
 * LCParticleIterator.h
 *
 *  Created on: Nov 27, 2013
 *      Author: andal
 */

#ifndef LCInnerPARTICLEITERATOR_H_
#define LCInnerPARTICLEITERATOR_H_

#include <list>
#include <Particle.h>
#include <vector>
#include "LCOuterParticleIterator.h"
#include <cassert>

namespace utils {

class LCInnerParticleIterator {
public:
	LCInnerParticleIterator(int index_arg,
			int original_index_arg, int cell_size_arg,
			int width_arg, int height_arg, int depth_arg,
			std::list<Particle>::iterator iterator_arg,
			std::vector<std::list<Particle> >& cells_arg);

	virtual ~LCInnerParticleIterator();

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
	bool operator!=(const LCInnerParticleIterator b);

	LCInnerParticleIterator& operator=(const LCInnerParticleIterator& cpy);

	int getCellNumber();

	bool checkLeft();
	bool checkRight();
	bool checkBottom();
	bool checkBack();
	bool checkTop();

private:
	/**
	 * the element of the iterator
	 */
	std::vector<std::list<Particle> >& cells;
	int cell_size;
	int width, height, depth;
	int index;
	int original_index;
	std::list<Particle>::iterator iterator;
};
} /* namespace utils */

#endif /* LCInnerPARTICLEITERATOR_H_ */