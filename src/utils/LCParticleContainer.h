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
	 * @param the list, TODO remaining params
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
	 * @return the last element of the neighboring partciles
	 * @param the index of the outer particle
	 */
	LCInnerParticleIterator endInner(int i);

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

	// TODO void initializeEndOfOuterIterators();

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
	 * @return the first particle of the domain
	 */
	LCOuterParticleIterator beginDomain;
	/**
	 * @return the last particle of the domain
	 */
	LCOuterParticleIterator endDomain;

	/**
	 * @return the first particle of the right boundary cells
	 */
	LCOuterParticleIterator beginOfLeftBoundary;

	/**
	 * @return the first particle of the right boundary cells
	 */
	LCOuterParticleIterator beginOfRightBoundary;

	/**
	 * @return the first particle of the bottom boundary cells
	 */
	LCOuterParticleIterator beginOfBottomBoundary;

	/**
	 * @return the first particle of the top boundary cells
	 */
	LCOuterParticleIterator beginOfTopBoundary;

	/**
	 * @return the first particle of the front boundary cells
	 */
	LCOuterParticleIterator beginOfFrontBoundary;
	/**
	 * @return the first particle of the rear boundary cells
	 */
	LCOuterParticleIterator beginOfBackBoundary;

	/**
	 * @return the first particle of the left halo cells
	 */
	LCOuterParticleIterator beginOfLeftHalo;

	/**
	 * @return the first particle of the right halo cells
	 */
	LCOuterParticleIterator beginOfRightHalo;

	/**
	 * @return the first particle of the bottom halo cells
	 */
	LCOuterParticleIterator beginOfBottomHalo;

	/**
	 * @return the first particle of the top halo cells
	 */
	LCOuterParticleIterator beginOfTopHalo;

	/**
	 * @return the first particle of the front halo cells
	 */
	LCOuterParticleIterator beginOfFrontHalo;

	/**
	 * @return the first particle of the rear halo cells
	 */
	LCOuterParticleIterator beginOfBackHalo;

	/**
	 * @return the last particle of the left boundary cells
	 */
	LCOuterParticleIterator endOfLeftBoundary;

	/**
	 * @return the lasi particle of the right boundary cells
	 */
	LCOuterParticleIterator endOfRightBoundary;

	/**
	 * @return the last particle of the bottom boundary cells
	 */
	LCOuterParticleIterator endOfBottomBoundary;

	/**
	 * @return the last particle of the top boundary cells
	 */
	LCOuterParticleIterator endOfTopBoundary;

	/**
	 * @return the last particle of the front boundary cells
	 */
	LCOuterParticleIterator endOfFrontBoundary;

	/**
	 * @return the last particle of the rear boundary cells
	 */
	LCOuterParticleIterator endOfBackBoundary;

	/**
	 * @return the last particle of the left halo cells
	 */
	LCOuterParticleIterator endOfLeftHalo;

	/**
	 * @return the last particle of the right halo cells
	 */
	LCOuterParticleIterator endOfRightHalo;

	/**
	 * @return the last particle of the bottom halo cells
	 */
	LCOuterParticleIterator endOfBottomHalo;

	/**
	 * @return the last particle of the top halo cells
	 */
	LCOuterParticleIterator endOfTopHalo;

	/**
	 * @return the last particle of the front halo cells
	 */
	LCOuterParticleIterator endOfFrontHalo;

	/**
	 * @return the last particle of the back halo cells
	 */
	LCOuterParticleIterator endOfBackHalo;

	/**
	 * @return the particles from the left halo cells
	 */
	std::vector<std::list<Particle *> *> leftHaloCells;

	/**
	 * @return the particles from the right halo cells
	 */
	std::vector<std::list<Particle *> *> rightHaloCells;

	/**
	 * @return the particles from the bottom halo cells
	 */
	std::vector<std::list<Particle *> *> bottomHaloCells;

	/**
	 * @return the particles from the top halo cells
	 */
	std::vector<std::list<Particle *> *> topHaloCells;

	/**
	 * @return the particles from the front halo cells
	 */
	std::vector<std::list<Particle *> *> frontHaloCells;

	/**
	 * @return the particles from the rear halo cells
	 */
	std::vector<std::list<Particle *> *> backHaloCells;

	/**
	 * @return the particles in the left boundary cells
	 */
	std::vector<std::list<Particle *> *> leftBoundaryCells;

	/**
	 * @return the particles in the right boundary cells
	 */
	std::vector<std::list<Particle *> *> rightBoundaryCells;

	/**
	 * @return the particles in the bottom boundary cells
	 */
	std::vector<std::list<Particle *> *> bottomBoundaryCells;

	/**
	 * @return the particles in the top boundary cells
	 */
	std::vector<std::list<Particle *> *> topBoundaryCells;

	/**
	 * @return the particles in the front boundary cells
	 */
	std::vector<std::list<Particle *> *> frontBoundaryCells;

	/**
	 * @return the particles in the rear boundary cells
	 */
	std::vector<std::list<Particle *> *> backBoundaryCells;

	std::vector<LCInnerParticleIterator> endOfInner;

	bool checkRight(int i);

	bool checkLeft(int i);

	bool checkTop(int i);

	bool checkBack(int i);

	bool checkFront(int i);
};

} /* namespace utils */

#endif /* LCPARTICLECONTAINER_H_ */
