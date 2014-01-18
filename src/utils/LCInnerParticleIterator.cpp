/*
 * LCParticleIterator.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: andal
 */

#include "LCInnerParticleIterator.h"

namespace utils {

LCInnerParticleIterator::LCInnerParticleIterator() {
	//Constructor only for resize
}

LCInnerParticleIterator::LCInnerParticleIterator(int index_arg,
		int original_index_arg, int cell_size_arg, int width_arg,
		int height_arg, int depth_arg,
		std::list<Particle *>::iterator iterator_arg,
		std::vector<std::list<Particle *> *>* cells_arg) :
		cells(cells_arg) {
	original_index = original_index_arg;
	index = index_arg;
	cell_size = cell_size_arg;
	width = width_arg;
	height = height_arg;
	depth = depth_arg;
	iterator = iterator_arg;
}

LCInnerParticleIterator::~LCInnerParticleIterator() {
	// TODO Auto-generated destructor stub
}

Particle& LCInnerParticleIterator::operator*() const {
	return *(*iterator);
}

void LCInnerParticleIterator::operator++() {

	++iterator;
	/** 
	 * Checks whether the outer particle was already the last Particle in its cell
	 * which would mean iterator were now on the dummy end of the list.
	 */
	if (iterator != (*cells)[index]->end()) {
		assert(iterator != (*cells)[index]->end());
	} else {
		int old_index = index;
		bool done = false;
		/**
		 * Checks the neighoring cells of the outer particle in a predetermined order:
		 * right, top left, top, top right [for both dimensional cases],
		 * Back bottom left, back bottom, back bottom right, back left, back, back right,
		 * back top left, back top and back top right [for the 3-dimensional case]
		 */
//		std::cout << index << std::endl;
		while (index < cell_size && (done == false || (*cells)[index]->empty() )) {
			done = false;
			if (index == original_index) {
				index++;
				if (checkRight()) {
					done = true;
				}
			} else if (index == original_index + 1) {
				index = original_index + width - 1;
				if (checkLeft() && checkTop()) {
					done = true;
				}
			} else if (index == original_index + width - 1) {
				index = original_index + width;
				if (checkTop() == true) {
					done = true;
				}
			} else if (index == original_index + width) {
				index = original_index + width + 1;
				if (checkTop() && checkRight()) {
					done = true;

				}
			} else if (index == original_index + width + 1) {
				index = original_index + width * height - width - 1;
				if (depth > 1) {
					if (checkBack() && checkBottom() && checkLeft()) {
						done = true;
					}
				} else {
					index = original_index + width + 2;
					done = true;
					//assert(true == false);
				}
			} else if (depth > 0
					&& index == original_index + width * height - width - 1) {
				index = original_index + width * height - width;
				if (checkBack() && checkBottom()) {
					done = true;
				}
			} else if (depth > 0
					&& index == original_index + width * height - width) {
				index = original_index + width * height - width + 1;
				if (checkBack() && checkBottom() && checkRight()) {
					done = true;
				}
			} else if (depth > 0
					&& index == original_index + width * height - width + 1) {
				index = original_index + width * height - 1;
				if (checkBack() && checkLeft()) {
					done = true;
				}
			} else if (depth > 0
					&& index == original_index + width * height - 1) {
				index = original_index + width * height;
				if (checkBack()) {
					done = true;
				}
			} else if (depth > 0 && index == original_index + width * height) {
				index = original_index + width * height + 1;
				if (checkBack() && checkRight()) {
					done = true;
				}
			} else if (depth > 0
					&& index == original_index + width * height + 1) {
				index = original_index + width * height + width - 1;
				if (checkBack() && checkTop() && checkLeft()) {
					done = true;
				}
			} else if (depth > 0
					&& index == original_index + width * height + width - 1) {
				index = original_index + width * height + width;
				if (checkBack() && checkTop()) {
					done = true;
				}
			} else if (depth > 0
					&& index == original_index + width * height + width) {
				index = original_index + width * height + width + 1;
				if (checkBack() && checkTop() && checkRight()) {
					done = true;
				}
			} else if (depth > 0
					&& index == original_index + width * height + width + 1) {
				assert((*cells)[index]->empty() == false);
				index = original_index + width * height + width + 2;
				done = true;
			} else {
				index = original_index + width * height + width + 2;
				//std::cout << index << std::endl;
				done = true;
			}

//			std::cout << index << std::endl;
		}
		if((depth < 2 && index >= original_index + width + 2)){
		}
		else if(index >= original_index + width * height + width + 2){

		}
		else if(index >= cell_size){

		}
		else if (index > old_index) {
			assert(index <= cell_size);
			assert((*cells)[index]->begin() != (*cells)[index]->end());
			assert((*cells)[index]->empty() == false);
			iterator = (*cells)[index]->begin();
			assert(index > old_index);
		} else {
			assert(index == old_index);
		}
	}
}

bool LCInnerParticleIterator::operator!=(const LCInnerParticleIterator b) {
	return iterator != b.iterator;
}

LCInnerParticleIterator& LCInnerParticleIterator::operator=(
		const LCInnerParticleIterator& cpy) {
	if (this == &cpy)
		return *this;
	cells = cpy.cells;
	cell_size = cpy.cell_size;
	iterator = cpy.iterator;
	original_index = cpy.original_index;
	index = cpy.index;
	width = cpy.width;
	height = cpy.height;
	depth = cpy.depth;
	return *this;
}

int LCInnerParticleIterator::getCellNumber() {
	return index;
}


bool LCInnerParticleIterator::checkLeft() {
        return ((original_index % width) > 0);
}
bool LCInnerParticleIterator::checkRight() {
	return ((original_index % width) != (width - 1));
}
bool LCInnerParticleIterator::checkBottom() {
        return (width <= (original_index % (width * height)));
}
bool LCInnerParticleIterator::checkBack() {
	if(depth == 0){
		return false;
	}
	else {
		return (original_index / (width * height) < (depth - 1));
	}
}
bool LCInnerParticleIterator::checkTop() {
        return ((width - 1) * height  > (original_index % (width * height)));
}

}
/* namespace utils */
