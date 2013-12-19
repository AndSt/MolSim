/*
 * LCParticleContainer.h
 *
 *  Created on: Nov 27, 2013
 *      Author: andal
 */

#ifndef LCPARTICLECONTAINER_H_
#define LCPARTICLECONTAINER_H_

#include <list>
#include <vector>
#include <Particle.h>
#include "Vector.h"
#include "ParticleIterator.h"
#include "LCInnerParticleIterator.h"
#include "LCOuterParticleIterator.h"

namespace utils {

class LCParticleContainer {
public:
	LCParticleContainer();
	virtual ~LCParticleContainer();

	/**
	 * fills the particles list
	 * @param the list
	 */
	void initialize(std::list<Particle>& particles_arg,
			Vector<double, 3> domain_size_arg, double cutoff_radius_arg);

	/**
	 * @return the first element of the container
	 */
	LCOuterParticleIterator beginOuter();

	/**
	 * @return the first element of the neighboring particles
	 * @param the outer particle iterator
	 */
	LCInnerParticleIterator beginInner(LCOuterParticleIterator it);

	/**
	 * @return the last element of the container
	 */
	LCOuterParticleIterator endOuter();

	/**
	 * updates the list of cells (also used to initialize)
	 */
	void updateCells();

	/**
	 * Initializes the cells
	 */
	void initializeCells();

	/**
	 * @return the particles list
	 */
	std::list<Particle *>& getList();

	/**
	 * initializes the halo cells around the domain
	 */
	void initializeHaloCells();

	/**
	 * @return the leftHaloCells
	 */
	std::vector<std::list<Particle *> *>& getLeftHaloCells();

	/**
	 * @return the rightHaloCells
	 */
	std::vector<std::list<Particle *> *>& getRightHaloCells();

	/**
	 * @return the bottomHaloCells
	 */
	std::vector<std::list<Particle *> *>& getBottomHaloCells();

	/**
	 * @return the topHaloCells
	 */
	std::vector<std::list<Particle *> *>& getTopHaloCells();

	/**
	 * @return the frontHaloCells
	 */
	std::vector<std::list<Particle *> *>& getFrontHaloCells();

	/**
	 * @return the backHaloCells
	 */
	std::vector<std::list<Particle *> *>& getBackHaloCells();

	/**
	 * initializes the cells in each boundary
	 */
	void initializeBoundaryCells();

	/**
	 * initializes the first particle for the domain and all boundaries
	 */
	void initializeBeginOuter();

	/**
	 *initializes the last particle for the domain and all boundaries
	 */
	void initializeEndOuter();

	/**
	 * @return the beginOfLeftBoundary
	 */
	LCOuterParticleIterator beginLeftBoundary();

	/**
	 * @return the beginOfRightBoundary
	 */
	LCOuterParticleIterator beginRightBoundary();

	/**
	 * @return the beginOfBottomBoundary
	 */
	LCOuterParticleIterator beginBottomBoundary();

	/**
	 * @return the beginOfTopBoundary
	 */
	LCOuterParticleIterator beginTopBoundary();

	/**
	 * @return the beginOfFrontBoundary
	 */
	LCOuterParticleIterator beginFrontBoundary();

	/**
	 * @return the beginOfBackBoundary
	 */
	LCOuterParticleIterator beginBackBoundary();

	/**
	 * @return endOfLeftBoundary
	 */
	LCOuterParticleIterator endLeftBoundary();

	/**
	 * @return the endOfRightBoundary
	 */
	LCOuterParticleIterator endRightBoundary();

	/**
	 * @return endOfBottomBoundary
	 */
	LCOuterParticleIterator endBottomBoundary();

	/**
	 * @return endOfTopBoundary
	 */
	LCOuterParticleIterator endTopBoundary();

	/**
	 * @return endOfFrontBoundary
	 */
	LCOuterParticleIterator endFrontBoundary();

	/**
	 * @return endOfBackBoundary
	 */
	LCOuterParticleIterator endBackBoundary();

	/**
	 * @return the beginOfLeftHalo
	 */
	LCOuterParticleIterator beginLeftHalo();

	/**
	 * @return the beginOfRightHalo
	 */
	LCOuterParticleIterator beginRightHalo();

	/**
	 * @return the beginOfBottomHalo
	 */
	LCOuterParticleIterator beginBottomHalo();

	/**
	 * @return the beginOfTopHalo
	 */
	LCOuterParticleIterator beginTopHalo();

	/**
	 * @return the beginOfFrontHalo
	 */
	LCOuterParticleIterator beginFrontHalo();

	/**
	 * @return the beginOfBackHalo
	 */
	LCOuterParticleIterator beginBackHalo();

	/**
	 * @return the endOfLeftHalo
	 */
	LCOuterParticleIterator endLeftHalo();

	/**
	 * @return the endOfRightHalo
	 */
	LCOuterParticleIterator endRightHalo();

	/**
	 * @return the endOfBottomHalo
	 */
	LCOuterParticleIterator endBottomHalo();

	/**
	 * @return the endOfTopHalo
	 */
	LCOuterParticleIterator endTopHalo();

	/**
	 * @return the endOfFrontHalo
	 */
	LCOuterParticleIterator endFrontHalo();

	/**
	 * @return the endOfBackHalo
	 */
	LCOuterParticleIterator endBackHalo();

	/**
	 * @return the endOfInners[i]
	 * @param the index of the outer iterator
	 */
	LCInnerParticleIterator& endInner(int i);

	/**
	 * @return the leftBoundaryCells
	 */
	std::vector<std::list<Particle *> *>& getLeftBoundaryCells();

	/**
	 * @return the rightBoundaryCells
	 */
	std::vector<std::list<Particle *> *>& getRightBoundaryCells();

	/**
	 * @return the bottomBoundaryCells
	 */
	std::vector<std::list<Particle *> *>& getBottomBoundaryCells();

	/**
	 * @return the topBoundaryCells
	 */
	std::vector<std::list<Particle *> *>& getTopBoundaryCells();

	/**
	 * @return the frontBoundaryCells
	 */
	std::vector<std::list<Particle *> *>& getFrontBoundaryCells();

	/**
	 * @return the backBoundaryCells
	 */
	std::vector<std::list<Particle *> *>& getBackBoundaryCells();

	/**
	 * @return the domain sizes
	 */
	utils::Vector<double, 3>& getDomainSize();

	/**
	 * @return the width
	 */
	int& getWidth();

	/**
	 * @return the height
	 */
	int& getHeight();

	/**
	 * @return the depth
	 */
	int& getDepth();

	/**
	 * @return number of particles within the domain
	 */
	int size();

	/**
	 * initalizes the ends for the inner iterators
	 */
	void initializeEndInner();

private:
	/**
	 * contains the list of the given particles
	 */
	std::list<Particle *> particles;

	/**
	 * contains the vector of cells of the given particles
	 */
	std::vector<std::list<Particle *> *> cells;

	/**
	 * contains the size of the domain.
	 * domain_size[0] - valid region of the "x-axis"
	 * domain_size[1] - valid region of the "y-axis"
	 * domain_size[2] - valid region of the "z-axis"
	 */
	utils::Vector<double, 3> domain_size;

	/**
	 * length of the edges (3D or 2D) of the cells
	 */
	double cutoff_radius;

	/**
	 * number of cells in the "x-axis" = domain_size[0] / cutoff_radius (rounded down)
	 */
	int width;

	/**
	 * number of cells in the "y-axis" = domain_size[1] / cutoff_radius (rounded down)
	 */
	int height;

	/**
	 * number of cells in the "z-axis" = domain_size[2] / cutoff_radius (rounded down)
	 */
	int depth;

	/**
	 * number of cells = width * height * depth (in 3D) or width * height (in 2D)
	 */
	int num_of_cells;

	/**
	 * the first particle of the domain
	 */
	LCOuterParticleIterator beginDomain;
	/**
	 * the last particle of the domain
	 */
	LCOuterParticleIterator endDomain;

	/**
	 * the first particle of the right boundary cells
	 */
	LCOuterParticleIterator beginOfLeftBoundary;

	/**
	 * the first particle of the right boundary cells
	 */
	LCOuterParticleIterator beginOfRightBoundary;

	/**
	 * the first particle of the bottom boundary cells
	 */
	LCOuterParticleIterator beginOfBottomBoundary;

	/**
	 * the first particle of the top boundary cells
	 */
	LCOuterParticleIterator beginOfTopBoundary;

	/**
	 * the first particle of the front boundary cells
	 */
	LCOuterParticleIterator beginOfFrontBoundary;
	/**
	 * the first particle of the rear boundary cells
	 */
	LCOuterParticleIterator beginOfBackBoundary;

	/**
	 * the first particle of the left halo cells
	 */
	LCOuterParticleIterator beginOfLeftHalo;

	/**
	 * the first particle of the right halo cells
	 */
	LCOuterParticleIterator beginOfRightHalo;

	/**
	 * the first particle of the bottom halo cells
	 */
	LCOuterParticleIterator beginOfBottomHalo;

	/**
	 * the first particle of the top halo cells
	 */
	LCOuterParticleIterator beginOfTopHalo;

	/**
	 *  the first particle of the front halo cells
	 */
	LCOuterParticleIterator beginOfFrontHalo;

	/**
	 *  the first particle of the rear halo cells
	 */
	LCOuterParticleIterator beginOfBackHalo;

	/**
	 * the last particle of the left boundary cells
	 */
	LCOuterParticleIterator endOfLeftBoundary;

	/**
	 * the last particle of the right boundary cells
	 */
	LCOuterParticleIterator endOfRightBoundary;

	/**
	 * the last particle of the bottom boundary cells
	 */
	LCOuterParticleIterator endOfBottomBoundary;

	/**
	 * the last particle of the top boundary cells
	 */
	LCOuterParticleIterator endOfTopBoundary;

	/**
	 * the last particle of the front boundary cells
	 */
	LCOuterParticleIterator endOfFrontBoundary;

	/**
	 * the last particle of the rear boundary cells
	 */
	LCOuterParticleIterator endOfBackBoundary;

	/**
	 * the last particle of the left halo cells
	 */
	LCOuterParticleIterator endOfLeftHalo;

	/**
	 * the last particle of the right halo cells
	 */
	LCOuterParticleIterator endOfRightHalo;

	/**
	 * the last particle of the bottom halo cells
	 */
	LCOuterParticleIterator endOfBottomHalo;

	/**
	 * the last particle of the top halo cells
	 */
	LCOuterParticleIterator endOfTopHalo;

	/**
	 * the last particle of the front halo cells
	 */
	LCOuterParticleIterator endOfFrontHalo;

	/**
	 * the last particle of the back halo cells
	 */
	LCOuterParticleIterator endOfBackHalo;

	/**
	 * the particles from the left halo cells
	 */
	std::vector<std::list<Particle *> *> leftHaloCells;

	/**
	 * the particles from the right halo cells
	 */
	std::vector<std::list<Particle *> *> rightHaloCells;

	/**
	 * the particles from the bottom halo cells
	 */
	std::vector<std::list<Particle *> *> bottomHaloCells;

	/**
	 * the particles from the top halo cells
	 */
	std::vector<std::list<Particle *> *> topHaloCells;

	/**
	 * the particles from the front halo cells
	 */
	std::vector<std::list<Particle *> *> frontHaloCells;

	/**
	 * the particles from the rear halo cells
	 */
	std::vector<std::list<Particle *> *> backHaloCells;

	/**
	 * the particles in the left boundary cells
	 */
	std::vector<std::list<Particle *> *> leftBoundaryCells;

	/**
	 * the particles in the right boundary cells
	 */
	std::vector<std::list<Particle *> *> rightBoundaryCells;

	/**
	 * the particles in the bottom boundary cells
	 */
	std::vector<std::list<Particle *> *> bottomBoundaryCells;

	/**
	 * the particles in the top boundary cells
	 */
	std::vector<std::list<Particle *> *> topBoundaryCells;

	/**
	 * the particles in the front boundary cells
	 */
	std::vector<std::list<Particle *> *> frontBoundaryCells;

	/**
	 * the particles in the rear boundary cells
	 */
	std::vector<std::list<Particle *> *> backBoundaryCells;

	/**
	 * the ends of the inner iterators
	 */
	std::vector<LCInnerParticleIterator> endOfInners;

	/**
	 * checks whether the iterator is in the right boundary
	 * @param the index
	 */
	bool checkRight(int i);

	/**
	 * checks whether the iterator is in the left boundary
	 * @param the index
	 */
	bool checkLeft(int i);

	/**
	 * checks whether the iterator is in the top boundary
	 * @param the index
	 */
	bool checkTop(int i);

	/**
	 * checks whether the iterator is in the rear boundary
	 * @param the index
	 */
	bool checkBack(int i);

	/**
	 * checks whether the iterator is in the front boundary
	 * @param the index
	 */
	bool checkFront(int i);
};

} /* namespace utils */

#endif /* LCPARTICLECONTAINER_H_ */
