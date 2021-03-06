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
	LCInnerParticleIterator();

	LCInnerParticleIterator(int index_arg,
			int original_index_arg, int cell_size_arg,
			int width_arg, int height_arg, int depth_arg,
			std::list<Particle *>::iterator iterator_arg,
			std::vector<std::list<Particle *> *>* cells_arg);

	virtual ~LCInnerParticleIterator();

	/**
	 * @return returns the reference to the momentary particle
	 */
	Particle& operator*() const;

	/**
	 * iterates to the next element
	 * @return the next particle in the neighborhood of the outer particle
	 */
	void operator++();


	/**
	 * checks on inequality
	 * @param b the Iterator to compare with
	 * @return returns true, if the two iterators do not match
	 */
	bool operator!=(const LCInnerParticleIterator b);

	/**
	 * @return assignes an inner iterator with the attributes of cpy
	 */
	LCInnerParticleIterator& operator=(const LCInnerParticleIterator& cpy);

	/**
	 * @return the index
	 */
	int getCellNumber();

	/**
	 * checks whether the inner iterator may go left
	 */
	bool checkLeft();
	/**
	 * checks whether the inner iterator may go right
	 */
	bool checkRight();
	/**
	 * checks whether the inner iterator may go to a lower layer
	 */
	bool checkBottom();
	/**
	 * checks whether the inner iterator may go to a deeper layer
	 */
	bool checkBack();
	/**
	 * checks whether the inner iterator may go to a higher layer
	 */
	bool checkTop();

private:
	/**
	 * the pointers to the cells with the particles inside
	 */
	std::vector<std::list<Particle *> *>* cells;

	/**
	 * the total number of cells
	 */
	int cell_size;
	/**
	 * the number of cells in x, y and z direction
	 */
	int width, height, depth;
	/**
	 * the cell number of the inner iterator
	 */
	int index;
	/**
	 * the cell number of the outer iterator where the inneriterator was called from
	 */
	int original_index;
	/**
	 * the iterator
	 */
	std::list<Particle *>::iterator iterator;
};
} /* namespace utils */

#endif /* LCInnerPARTICLEITERATOR_H_ */
