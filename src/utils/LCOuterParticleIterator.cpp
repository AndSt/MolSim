/*
 * LCOuterParticleIterator.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: andal
 */

#include "LCOuterParticleIterator.h"

namespace utils {


LCOuterParticleIterator::LCOuterParticleIterator(int cell_size_arg,
		std::vector<std::list<Particle> >& cells_arg,
	std::list<Particle>::iterator iterator_arg, int index_arg) :
	cells(cells_arg) {
	cell_size = cell_size_arg;
	index = index_arg;
	iterator = iterator_arg;
	}

LCOuterParticleIterator::~LCOuterParticleIterator() {
	// TODO Auto-generated destructor stub
}

Particle& LCOuterParticleIterator::operator*() const {
	return *iterator;
}

bool LCOuterParticleIterator::operator!=(const LCOuterParticleIterator b) {
	bool return_value = false;
	if(iterator != b.iterator){
		return_value = true;
	}
	if(index > b.index){
		return_value = true;
	}
	return return_value;
}

void  LCOuterParticleIterator::operator++() {
	assert(cells[index].empty() == false);
	//std::cout << it_index << " "<< cells[index].size() << " " << index << " " << (*iterator).toString() << std::endl;

	++iterator;
	if (iterator != cells[index].end()) {
		assert(iterator != cells[index].end());
	} else {
		int old_index = index;
		assert(cells[index].empty() == false);
		index++;
		while (cells[index].empty() == true && index < cell_size) {
			index++;
		}
		assert(index > old_index);
		assert(cells[index].empty() == false);
		assert(cells[index].begin() != cells[index].end());
		iterator = cells[index].begin();
	}
}

int LCOuterParticleIterator::getCellNumber(){
	return index;
}

std::list<Particle>::iterator LCOuterParticleIterator::getIterator(){
	std::list<Particle>::iterator newIterator = iterator;
	return newIterator;
}

LCOuterParticleIterator& LCOuterParticleIterator::operator=(const LCOuterParticleIterator& cpy){
	if (this == &cpy)  return *this;
	cells = cpy.cells;
	cell_size = cpy.cell_size;
	index = 0;
	iterator = cpy.iterator;
	return *this;
}

} /* namespace utils */
