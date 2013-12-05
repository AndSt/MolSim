/*
 * LCParticleIterator.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: andal
 */

#include "LCInnerParticleIterator.h"
#include <log4cxx/logger.h>

log4cxx::LoggerPtr lcinnerparticleiteratorlogger(log4cxx::Logger::getLogger("utils.lcinnerparticleiterator"));

namespace utils {

LCInnerParticleIterator::LCInnerParticleIterator(int index_arg,
		int original_index_arg, int cell_size_arg, int width_arg,
		int height_arg, int depth_arg,
		std::list<Particle>::iterator iterator_arg,
		std::vector<std::list<Particle> >& cells_arg) :
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
	return *iterator;
}

void LCInnerParticleIterator::operator++() {

	++iterator;
	if (iterator != cells[index].end()) {
		assert(iterator != cells[index].end());
	} else {
		int old_index = index;
		bool done = false;
		while (cells[index].empty() || done == false) {
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
				if (checkTop()) {
					done = true;
				}
			} else if (index == original_index + width) {
				index = original_index + width + 1;
				if (checkTop() && checkRight()) {
					done = true;
				}
			} else if (index == original_index + width + 1) {
				if (depth > 1) {
					index = original_index + width * height - width - 1;
					if (checkBack() && checkBottom() && checkLeft()) {
						done = true;
					}
				} else {
					index = old_index;
					done = true;
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
				assert(cells[index].empty() == false);
				index = old_index;
				done = true;
			} else {
				assert(cells[index].empty() == false);
				LOG4CXX_ERROR(lcinnerparticleiteratorlogger, "Error, Iterator gone too far.")
			}
		}
		assert(index <= cell_size);
		assert(cells[index].empty() == false);
		assert(cells[index].begin() != cells[index].end());

		if (index > old_index) {
			iterator = cells[index].begin();
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
	assert(cells[index].empty() == false);
	return index;
}

bool LCInnerParticleIterator::checkLeft() {
	return ((original_index % width) != 0);
}
bool LCInnerParticleIterator::checkRight() {
	return ((index % width) != 0);
}
bool LCInnerParticleIterator::checkBottom() {
	return (width <= original_index % (width * height));
}
bool LCInnerParticleIterator::checkBack() {
	return (index < cell_size);
}
bool LCInnerParticleIterator::checkTop() {
	return (width * height - width > (original_index % (width * height)));
}

}
/* namespace utils */
