/*
 * LCParticleContainer.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: andal
 */

#include "LCParticleContainer.h"
#include <log4cxx/logger.h>

log4cxx::LoggerPtr lcparticlecontainerlogger(
		log4cxx::Logger::getLogger("utils.lcparticlecontainer"));

namespace utils {

LCParticleContainer::LCParticleContainer() {
	// TODO Auto-generated constructor stub

}

LCParticleContainer::~LCParticleContainer() {
	// TODO Auto-generated destructor stub
}

void LCParticleContainer::initialize(std::list<Particle>& particles_arg,
		Vector<double, 3> domain_size_arg, double cutoff_radius_arg) {
	particles = particles_arg;
	domain_size = domain_size_arg;
	cutoff_radius = cutoff_radius_arg;

	width = domain_size[0] / cutoff_radius;
	height = domain_size[1] / cutoff_radius;
	depth = domain_size[2] / cutoff_radius;
	if (depth > 0) {
		num_of_cells = width * height * depth;
	} else {
		num_of_cells = width * height;
	}
	cells.resize(num_of_cells);

	for (int i = 0; i < num_of_cells; i++) {
		cells[i] = std::list<Particle>();
	}
	initializeCells();
}

void LCParticleContainer::updateCells() {
	deleteHalo();
	toList();
	initializeCells();
	LOG4CXX_DEBUG(lcparticlecontainerlogger, "Updated cells.");
}

void LCParticleContainer::initializeCells() {
	for (int i = 0; i < num_of_cells; i++) {
		cells[i].clear();
	}
	std::list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		//check if it's in the domain

		if (((*iterator).getX())[0] <= domain_size[0]
				&& (*iterator).getX()[1] <= domain_size[1]
				&& (*iterator).getX()[2] <= domain_size[2]
				&& (*iterator).getX()[0] >= 0 && ((*iterator).getX())[1] >= 0
				&& (*iterator).getX()[2] >= 0) {

			Particle& p = *iterator;
			int i = (int) (p.getX()[0] / cutoff_radius)
					+ ((int) (p.getX()[1] / cutoff_radius)) * width
					+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
			cells[i].push_back(*iterator);
		} else {
			halo.push_back(*iterator);
		}
		++iterator;
	}
	LOG4CXX_DEBUG(lcparticlecontainerlogger, "Initialized cells.");
}

void LCParticleContainer::toList() {
	particles.clear();
	LCOuterParticleIterator iterator = beginOuter();
	while (iterator != endOuter()) {
		if (iterator.getCellNumber() > endOuter().getCellNumber()) {
			break;
		}
		assert(iterator.getCellNumber() <= endOuter().getCellNumber());
		particles.push_back(*iterator);
		++iterator;
	}
	std::list<Particle>::iterator iiterator = halo.begin();
	while (iiterator != halo.end()) {
		particles.push_back(*iiterator);
		++iiterator;
	}
}
void LCParticleContainer::deleteHalo() {
	halo.clear();
}

LCOuterParticleIterator LCParticleContainer::beginOuter() {
	int i = 0;
	while (cells[i].empty() == true) {
		++i;
	}
	assert(cells[i].empty() == false);
	return LCOuterParticleIterator(num_of_cells, cells, cells[i].begin(), i);
}

LCInnerParticleIterator LCParticleContainer::beginInner(
		LCOuterParticleIterator it) {
	int i = it.getCellNumber();
	assert(cells[i].empty() == false);
	LCInnerParticleIterator inner(i, i, num_of_cells, width, height, depth,
			it.getIterator(), cells);
	return inner;
}

LCOuterParticleIterator LCParticleContainer::endOuter() {
	int i = 1;
	while (cells[num_of_cells - i].empty() == true) {
		assert(cells[num_of_cells - i].size() == 0);
		++i;
	}
	return LCOuterParticleIterator(num_of_cells, cells,
			cells[num_of_cells - i].end(), (num_of_cells - i));
}

LCInnerParticleIterator LCParticleContainer::endInner(int i) {
	int x;
	if ((!cells[i + width * height + width + 1].empty()) && depth > 0) {
		x = i + width * height + width + 1;
	} else if ((!cells[i + width * height + width].empty()) && depth > 0) {
		x = i + width * height + width;
	} else if ((!cells[i + width * height + width - 1].empty()) && depth > 0) {
		x = i + width * height + width - 1;
	} else if ((!cells[i + width * height + 1].empty()) && depth > 0) {
		x = i + width * height + 1;
	} else if ((!cells[i + width * height].empty()) && depth > 0) {
		x = i + width * height;
	} else if ((!cells[i + width * height - 1].empty()) && depth > 0) {
		x = i + width * height - 1;
	} else if ((!cells[i + width * height - width + 1].empty()) && depth > 0) {
		x = i + width * height - width + 1;
	} else if ((!cells[i + width * height - width].empty()) && depth > 0) {
		x = i + width * height - width;
	} else if ((!cells[i + width * height - width - 1].empty()) && depth > 0) {
		x = i + width * height - width - 1;
	} else if (!cells[i + width + 1].empty()) {
		x = i + width + 1;
	} else if (!cells[i + width].empty()) {
		x = i + width;
	} else if (!cells[i + width - 1].empty()) {
		x = i + width - 1;
	} else if (!cells[i + 1].empty()) {
		x = i + 1;
	} else {
		x = i;
	}
	assert(cells[i].size() != 0);
	assert(cells[x].empty() == false);
	assert(cells[x].size() > 0);
	//assert(x <= i + 61);
	return LCInnerParticleIterator(x, x, num_of_cells, width, height, depth,
			cells[x].end(), cells);
}

std::list<Particle>& LCParticleContainer::getList() {
	return particles;
}

std::list<Particle>& LCParticleContainer::getHaloList() {
	return halo;
}

int LCParticleContainer::size() {
	int size = 0;
	for (int i = 0; i < num_of_cells; i++) {
		size += cells[i].size();
	}
	return size;
}

} /* namespace utils */
