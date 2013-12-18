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
	for (int i = 0; i < num_of_cells; i++) {
		delete cells[i];
	}

}

void LCParticleContainer::initialize(std::list<Particle>& particles_arg,
		Vector<double, 3> domain_size_arg, double cutoff_radius_arg) {
//	std::list<Particle>::iterator iterator = particles_arg.begin();
//	while(iterator != particles_arg.end()){
//		particles.push_back(&(*iterator));
//	}
	std::list<Particle>::iterator iterator = particles_arg.begin();
	while (iterator != particles_arg.end()) {
		particles.push_back(&(*iterator));
		++iterator;
	}
	domain_size = domain_size_arg;
	cutoff_radius = cutoff_radius_arg;

	width = domain_size[0] / cutoff_radius;
	height = domain_size[1] / cutoff_radius;
	depth = domain_size[2] / cutoff_radius;

	//initialize the number of cells needed in our array
	if (depth > 0) {
		num_of_cells = width * height * depth;
	} else {
		num_of_cells = width * height;
	}
	cells.resize(num_of_cells);
	endOfInners.resize(num_of_cells);
	for (int i = 0; i < num_of_cells; i++) {
		cells[i] = new std::list<Particle *>();
	}
	//initialize the cells with the corresponding particles
	initializeCells();

	initializeBoundaryCells();

	initializeHaloCells();

	initializeBeginOuter();

	initializeEndOuter();

	initializeEndInner();

}

void LCParticleContainer::updateCells() {
	//initialize the cells with the corresponding particles
	initializeCells();

	initializeBeginOuter();

	initializeEndOuter();

	initializeEndInner();

}

void LCParticleContainer::initializeCells() {
	for (int i = 0; i < num_of_cells; i++) {
		cells[i]->clear();
	}
	std::list<Particle *>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		//check if it's in the domain
		if (((*(*iterator)).getX())[0] <= domain_size[0]
				&& (*(*iterator)).getX()[1] <= domain_size[1]
				&& (*(*iterator)).getX()[2] <= domain_size[2]
				&& (*(*iterator)).getX()[0] >= 0
				&& ((*(*iterator)).getX())[1] >= 0
				&& (*(*iterator)).getX()[2] >= 0) {

			Particle& p = (*(*iterator));
			int i = (int) (p.getX()[0] / cutoff_radius)
					+ ((int) (p.getX()[1] / cutoff_radius)) * width
					+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
			cells[i]->push_back(*iterator);
		} else {
//			assert(true == false);
		}
		++iterator;
	}
	LOG4CXX_DEBUG(lcparticlecontainerlogger, "Initialized cells.");
}

void LCParticleContainer::initializeBoundaryCells() {

	//initialize vector of left bondary cells
	for (int i = 0; i <= num_of_cells - width; i = i + width) {
		leftBoundaryCells.push_back(cells[i]);
	}

	//initialize vector of right boundary cells
	for (int i = width - 1; i <= num_of_cells - 1; i = i + width) {
		rightBoundaryCells.push_back(cells[i]);
	}

	//initialize vector of bottom boundary cells
	for (int i = 0; i <= num_of_cells - width * height;
			i = i + width * height) {
		for (int j = 0; j < width; j++) {
			bottomBoundaryCells.push_back(cells[i + j]);
		}
	}

	//initialize vector of top boundary cells
	for (int i = width * height - width; i <= num_of_cells - width;
			i = i + width * height) {
		for (int j = 0; j < width; j++) {
			topBoundaryCells.push_back(cells[i + j]);
		}
	}

	//only needed if it's a 3D simulation
	if (depth > 0) {
		//initialize vector of front boundary cells
		for (int i = 0; i < width * height; i++) {
			frontBoundaryCells.push_back(cells[i]);
		}

		//initialize vector of back boundary cells
		for (int i = num_of_cells - width * height; i < num_of_cells; i++) {
			backBoundaryCells.push_back(cells[i]);
		}
	}
}

void LCParticleContainer::initializeHaloCells() {
	//initialize left halo cells
//	for (int i = 0; i < rightBoundaryCells.size(); i++) {
//		leftHaloCells.push_back(rightBoundaryCells[i]);
//	}
//
//	//initialize right halo cells
//	for (int i = 0; i < leftBoundaryCells.size(); i++) {
//		rightHaloCells.push_back(leftBoundaryCells[i]);
//	}
//
//	//initialize bottom halo cells
//	for (int i = 0; i < topBoundaryCells.size(); i++) {
//		bottomHaloCells.push_back(topBoundaryCells[i]);
//	}
//
//	//initialize top halo cells
//	for (int i = 0; i < bottomBoundaryCells.size(); i++) {
//		topHaloCells.push_back(bottomBoundaryCells[i]);
//	}
	leftHaloCells = rightBoundaryCells;
	rightHaloCells = leftBoundaryCells;
	bottomHaloCells = topBoundaryCells;
	topHaloCells = bottomBoundaryCells;

	//only with depth > 2 the periodic force calculation is needed
	if (depth > 0) {
		//initialize front halo cells
		for (int i = 0; i < backBoundaryCells.size(); i++) {
			frontHaloCells.push_back(backBoundaryCells[i]);
		}

		//initialize back halo cells
		for (int i = 0; i < frontBoundaryCells.size(); i++) {
			backHaloCells.push_back(frontBoundaryCells[i]);
		}
	}
}

void LCParticleContainer::initializeBeginOuter() {
	//initialize the beginning of the domain
	int i = 0;
	while (cells[i]->empty() == true) {
		++i;
	}
	assert(cells[i]->empty() == false);
	beginDomain = LCOuterParticleIterator(num_of_cells, &cells,
			cells[i]->begin(), i);

	//initialize the beginning of the left boundary
	i = 0;
	while (i < leftBoundaryCells.size() && leftBoundaryCells[i]->empty() == true) {
		++i;
	}
	if (i >= leftBoundaryCells.size()) {
		i = 0;
	}
	beginOfLeftBoundary = LCOuterParticleIterator(leftBoundaryCells.size(),
			&leftBoundaryCells, leftBoundaryCells[i]->begin(), i);

	//initialize the beginning of the right boundary
	i = 0;
	while (i < rightBoundaryCells.size()
			&& rightBoundaryCells[i]->empty() == true) {
		++i;
	}
	if (i >= rightBoundaryCells.size()) {
		i = 0;
	}
	beginOfRightBoundary = LCOuterParticleIterator(rightBoundaryCells.size(),
			&rightBoundaryCells, rightBoundaryCells[i]->begin(), i);

	//initialize the beginning of the bottom boundary
	i = 0;
	while (i < bottomBoundaryCells.size()
			&& bottomBoundaryCells[i]->empty() == true) {
		++i;
	}
	if (i >= bottomBoundaryCells.size()) {
		i = 0;
	}
	beginOfBottomBoundary = LCOuterParticleIterator(bottomBoundaryCells.size(),
			&bottomBoundaryCells, bottomBoundaryCells[i]->begin(), i);

	//initialize the beginning of the top boundary
	i = 0;
	while (i < topBoundaryCells.size() && topBoundaryCells[i]->empty() == true) {
		++i;
	}
	if (i >= topBoundaryCells.size()) {
		i = 0;
	}
	beginOfTopBoundary = LCOuterParticleIterator(topBoundaryCells.size(),
			&topBoundaryCells, topBoundaryCells[i]->begin(), i);

	if (depth > 2) {
		//initialize the beginning of the front boundary
		i = 0;
		while (i < frontBoundaryCells.size()
				&& frontBoundaryCells[i]->empty() == true) {
			++i;
		}
		if (i >= frontBoundaryCells.size()) {
			i = 0;
		}
		beginOfFrontBoundary = LCOuterParticleIterator(
				frontBoundaryCells.size(), &frontBoundaryCells,
				frontBoundaryCells[i]->begin(), i);

		//initialize the beginning of the back boundary
		i = 0;
		while (i < backBoundaryCells.size()
				&& backBoundaryCells[i]->empty() == true) {
			++i;
		}
		if (i >= backBoundaryCells.size()) {
			i = 0;
		}
		beginOfBackBoundary = LCOuterParticleIterator(backBoundaryCells.size(),
				&backBoundaryCells, backBoundaryCells[i]->begin(), i);
	}

	beginOfLeftHalo = beginOfRightBoundary;
	beginOfRightHalo = beginOfLeftBoundary;
	beginOfBottomHalo = beginOfTopBoundary;
	beginOfTopHalo = beginOfBottomHalo;
	if (depth > 2) {
		beginOfFrontHalo = beginOfBackBoundary;
		beginOfBackHalo = beginOfTopBoundary;
	}
}

void LCParticleContainer::initializeEndInner() {
	for (int i = beginOuter().getCellNumber(); i < endOuter().getCellNumber();
			i++) {
		int x;
		if (depth > 1) {
			if ((num_of_cells > i + width * height + width + 1
					&& !cells[i + width * height + width + 1]->empty())
					&& checkRight(i) && checkBack(i) && checkTop(i)) {
				x = i + width * height + width + 1;
			} else if ((num_of_cells > i + width * height + width
					&& !cells[i + width * height + width]->empty())
					&& checkBack(i) && checkTop(i)) {
				x = i + width * height + width;
			} else if ((num_of_cells > i + width * height + width - 1
					&& !cells[i + width * height + width - 1]->empty()
					&& checkLeft(i) && checkBack(i) && checkTop(i))) {
				x = i + width * height + width - 1;
			} else if ((num_of_cells > i + width * height + 1
					&& !cells[i + width * height + 1]->empty()) && checkRight(i)
					&& checkTop(i)) {
				x = i + width * height + 1;
			} else if ((num_of_cells > i + width * height
					&& !cells[i + width * height]->empty()) && checkTop(i)) {
				x = i + width * height;
			} else if ((num_of_cells > i + width * height - 1
					&& !cells[i + width * height - 1]->empty()) && checkLeft(i)
					&& checkTop(i)) {
				x = i + width * height - 1;
			} else if ((num_of_cells > i + width * height - width + 1
					&& !cells[i + width * height - width + 1]->empty()
					&& checkRight(i) && checkFront(i) && checkTop(i))) {
				x = i + width * height - width + 1;
			} else if ((num_of_cells > i + width * height - width
					&& !cells[i + width * height - width]->empty())
					&& checkFront(i) && checkTop(i)) {
				x = i + width * height - width;
			} else if ((num_of_cells > i + width * height - width - 1
					&& !cells[i + width * height - width - 1]->empty()
					&& checkLeft(i) && checkFront(i) && checkTop(i))) {
				x = i + width * height - width - 1;
			} else if (num_of_cells > i + width + 1
					&& !cells[i + width + 1]->empty() && checkRight(i)
					&& checkTop(i)) {
				x = i + width + 1;
			} else if (num_of_cells > i + width && !cells[i + width]->empty()
					&& checkTop(i)) {
				x = i + width;
			} else if (num_of_cells > i + width - 1
					&& !cells[i + width - 1]->empty() && checkLeft(i)
					&& checkTop(i)) {
				x = i + width - 1;
			} else if (num_of_cells > i + 1 && !cells[i + 1]->empty()
					&& checkRight(i)) {
				x = i + 1;
			} else {
				x = i;
			}
		} else {
			if (num_of_cells > i + width + 1
					&& !cells[i + width + 1]->empty()) {
				x = i + width + 1;
			} else if (num_of_cells > i + width && !cells[i + width]->empty()) {
				x = i + width;
			} else if (num_of_cells > i + width
					&& !cells[i + width - 1]->empty()) {
				x = i + width - 1;
			} else if (num_of_cells > i + 1 && !cells[i + 1]->empty()) {
				x = i + 1;
			} else {
				x = i;
			}
		}
		assert(cells[i]->size() != 0);
		assert(cells[x]->empty() == false);
		assert(cells[x]->size() > 0);

		LCInnerParticleIterator ip(x, x, num_of_cells, width, height, depth,
				cells[x]->end(), &cells);

		endOfInners[i] = ip;
	}
}

void LCParticleContainer::initializeEndOuter() {
	//
	// initialize the end of the domain
	//
	int i = num_of_cells - 1;
	while (i >= 0 && cells[i]->empty() == true) {
		assert(cells[i]->size() == 0);
		--i;
	}
	if (i < 0) {
		endDomain = LCOuterParticleIterator(num_of_cells, &cells,
				cells[0]->begin(), 0);
	} else {
		endDomain = LCOuterParticleIterator(num_of_cells, &cells,
				cells[i]->end(), i);
	}

	//
	// initialize the end of the left boundary
	//
	i = leftBoundaryCells.size() - 1;
	while (i >= 0 && leftBoundaryCells[i]->empty() == true) {
		assert(leftBoundaryCells[i]->size() == 0);
		--i;
	}
	if (i < 0) {
		endOfLeftBoundary = LCOuterParticleIterator(leftBoundaryCells.size(),
				&leftBoundaryCells, leftBoundaryCells[0]->begin(), 0);
	} else {
		endOfLeftBoundary = LCOuterParticleIterator(leftBoundaryCells.size(),
				&leftBoundaryCells, leftBoundaryCells[i]->end(), i);
	}

	//
	// initialize the end of the right boundary
	//
	i = rightBoundaryCells.size() - 1;
	while (i >= 0 && rightBoundaryCells[i]->empty()) {
		assert(rightBoundaryCells[i]->size() == 0);
		--i;
	}
	if (i < 0) {
		endOfRightBoundary = LCOuterParticleIterator(rightBoundaryCells.size(),
				&rightBoundaryCells, rightBoundaryCells[0]->begin(), 0);
	} else {
		endOfRightBoundary = LCOuterParticleIterator(rightBoundaryCells.size(),
				&rightBoundaryCells, rightBoundaryCells[i]->end(), i);
	}

	//
	// initialize the end of the bottom boundary
	//
	i = bottomBoundaryCells.size() - 1;
	while (i >= 0 && bottomBoundaryCells[i]->empty()) {
		assert(bottomBoundaryCells[i]->size() == 0);
		--i;
	}
	if (i < 0) {
		endOfBottomBoundary = LCOuterParticleIterator(
				bottomBoundaryCells.size(), &bottomBoundaryCells,
				bottomBoundaryCells[0]->begin(), 0);
	} else {
		endOfBottomBoundary = LCOuterParticleIterator(
				bottomBoundaryCells.size(), &bottomBoundaryCells,
				bottomBoundaryCells[i]->end(), i);
	}

	//
	// initialize the end of the top boundary
	//
	i = topBoundaryCells.size() - 1;
	while (i >= 0 && topBoundaryCells[i]->empty()) {
		assert(topBoundaryCells[i]->size() == 0);
		--i;
	}
	if (i < 0) {
		endOfTopBoundary = LCOuterParticleIterator(topBoundaryCells.size(),
				&topBoundaryCells, topBoundaryCells[0]->begin(), 0);
	} else {
		endOfTopBoundary = LCOuterParticleIterator(topBoundaryCells.size(),
				&topBoundaryCells, topBoundaryCells[i]->end(), i);
	}

	if (depth > 2) {
		//
		// initialize the end of the front boundary
		//
		i = frontBoundaryCells.size() - 1;
		while (i >= 0 && frontBoundaryCells[i]->empty()) {
			assert(frontBoundaryCells[i]->size() == 0);
			--i;
		}
		if (i >= 0) {
			endOfFrontBoundary = LCOuterParticleIterator(
					frontBoundaryCells.size(), &frontBoundaryCells,
					frontBoundaryCells[0]->begin(), 0);
		} else {
			endOfFrontBoundary = LCOuterParticleIterator(
					frontBoundaryCells.size(), &frontBoundaryCells,
					frontBoundaryCells[i]->end(), i);
		}

		//
		// initialize the end of the back boundary
		//
		i = backBoundaryCells.size() - 1;
		while (i >= 0 && backBoundaryCells[i]->empty()) {
			assert(backBoundaryCells[i]->size() == 0);
			--i;
		}
		if (i >= 0) {
			endOfBackBoundary = LCOuterParticleIterator(
					backBoundaryCells.size(), &backBoundaryCells,
					backBoundaryCells[0]->begin(), 0);
		} else {
			endOfBackBoundary = LCOuterParticleIterator(
					backBoundaryCells.size(), &backBoundaryCells,
					backBoundaryCells[i]->end(), i);
		}
	}

	endOfLeftHalo = endOfRightBoundary;
	endOfRightHalo = endOfLeftBoundary;
	endOfBottomHalo = endOfTopBoundary;
	endOfTopHalo = endOfBottomHalo;
	if (depth > 2) {
		endOfFrontHalo = endOfBackBoundary;
		endOfBackHalo = endOfTopBoundary;
	}
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getLeftBoundaryCells() {
	return leftBoundaryCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getRightBoundaryCells() {
	return rightBoundaryCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getBottomBoundaryCells() {
	return bottomBoundaryCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getTopBoundaryCells() {
	return topBoundaryCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getFrontBoundaryCells() {
	return frontBoundaryCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getBackBoundaryCells() {
	return backBoundaryCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getLeftHaloCells() {
	return leftHaloCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getRightHaloCells() {
	return rightHaloCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getBottomHaloCells() {
	return bottomHaloCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getTopHaloCells() {
	return topHaloCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getFrontHaloCells() {
	return frontHaloCells;
}

std::vector<std::list<Particle *> *>& LCParticleContainer::getBackHaloCells() {
	return backHaloCells;
}

LCOuterParticleIterator LCParticleContainer::beginOuter() {
	return beginDomain;
}

LCOuterParticleIterator LCParticleContainer::endOuter() {
	return endDomain;
}

LCInnerParticleIterator& LCParticleContainer::endInner(int i) {
	return endOfInners[i];
}

LCInnerParticleIterator LCParticleContainer::beginInner(
		LCOuterParticleIterator it) {
	int i = it.getCellNumber();
	assert(cells[i]->empty() == false);
	LCInnerParticleIterator inner(i, i, num_of_cells, width, height, depth,
			it.getIterator(), &cells);
	return inner;
}



LCOuterParticleIterator LCParticleContainer::beginLeftBoundary() {
	return beginOfLeftBoundary;
}

LCOuterParticleIterator LCParticleContainer::beginRightBoundary() {
	return beginOfRightBoundary;
}

LCOuterParticleIterator LCParticleContainer::beginBottomBoundary() {
	return beginOfBottomBoundary;
}

LCOuterParticleIterator LCParticleContainer::beginTopBoundary() {
	return beginOfTopBoundary;
}

LCOuterParticleIterator LCParticleContainer::beginFrontBoundary() {
	return beginOfFrontBoundary;
}

LCOuterParticleIterator LCParticleContainer::beginBackBoundary() {
	return beginOfBackBoundary;
}

LCOuterParticleIterator LCParticleContainer::endLeftBoundary() {
	return endOfLeftBoundary;
}

LCOuterParticleIterator LCParticleContainer::endRightBoundary() {
	return endOfRightBoundary;
}

LCOuterParticleIterator LCParticleContainer::endBottomBoundary() {
	return endOfBottomBoundary;
}

LCOuterParticleIterator LCParticleContainer::endTopBoundary() {
	return endOfTopBoundary;
}

LCOuterParticleIterator LCParticleContainer::endFrontBoundary() {
	return endOfFrontBoundary;
}

LCOuterParticleIterator LCParticleContainer::endBackBoundary() {
	return endOfBackBoundary;
}

LCOuterParticleIterator LCParticleContainer::beginLeftHalo() {
	return beginOfLeftHalo;
}

LCOuterParticleIterator LCParticleContainer::beginRightHalo() {
	return beginOfRightHalo;
}

LCOuterParticleIterator LCParticleContainer::beginBottomHalo() {
	return beginOfBottomHalo;
}

LCOuterParticleIterator LCParticleContainer::beginTopHalo() {
	return beginOfTopHalo;
}

LCOuterParticleIterator LCParticleContainer::beginFrontHalo() {
	return beginOfFrontHalo;
}

LCOuterParticleIterator LCParticleContainer::beginBackHalo() {
	return beginOfBackHalo;
}

LCOuterParticleIterator LCParticleContainer::endLeftHalo() {
	return endOfLeftHalo;
}

LCOuterParticleIterator LCParticleContainer::endRightHalo() {
	return endOfRightHalo;
}

LCOuterParticleIterator LCParticleContainer::endBottomHalo() {
	return endOfBottomHalo;
}

LCOuterParticleIterator LCParticleContainer::endTopHalo() {
	return endOfTopHalo;
}

LCOuterParticleIterator LCParticleContainer::endFrontHalo() {
	return endOfFrontHalo;
}

LCOuterParticleIterator LCParticleContainer::endBackHalo() {
	return endOfBackHalo;
}

std::list<Particle *>& LCParticleContainer::getList() {
	return particles;
}

utils::Vector<double, 3>& LCParticleContainer::getDomainSize() {
	return domain_size;
}

int& LCParticleContainer::getWidth() {
	return width;
}

int& LCParticleContainer::getHeight() {
	return height;
}

int& LCParticleContainer::getDepth() {
	return depth;
}

int LCParticleContainer::size() {
	int size = 0;
	for (int i = 0; i < num_of_cells; i++) {
		size += cells[i]->size();
	}
	return size;
}

bool LCParticleContainer::checkRight(int i) {
	return (i + 1) % width != 0;
}

bool LCParticleContainer::checkLeft(int i) {
	return i % width != 0;
}

bool LCParticleContainer::checkBack(int i) {
	return num_of_cells - width * height > i;
}

bool LCParticleContainer::checkTop(int i) {
	return i % (width * height) < width * height - width;
}

bool LCParticleContainer::checkFront(int i) {
	return i >= width * height;
}

} /* namespace utils */
