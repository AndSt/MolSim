/*
 * BoundaryHandler.h
 *
 *  Created on: Dec 8, 2013
 *      Author: andal
 */

#ifndef BOUNDARYHANDLER_H_
#define BOUNDARYHANDLER_H_

#include "Vector.h"
#include <list>
#include "LCOuterParticleIterator.h"
#include "LCParticleContainer.h"
#include <Particle.h>

namespace utils {

class BoundaryHandler {
public:
	BoundaryHandler(std::vector<int> boundary_type_arg,
			LCParticleContainer& container_arg, double h_arg,
			void (*calculate)(Particle*, Particle*));

	virtual ~BoundaryHandler();

	/**
	 * applies the outflow boundary condition on particles
	 */
	void applyOutflow();

	/**
	 * moves the particles that flew out of the domain
	 */
	void applyPeriodicMoving();

	/**
	 * applies the periodic boundary condition on particles
	 */
	void applyPeriodic();

	/**
	 * applies the reflecting boundary condition on particles
	 */
	void applyReflecting();

private:
	/**
	 * saves the boundary condition of each boundary
	 * 		1 - outflow
	 * 		2 - reflecting boundary
	 * 		3 - periodic boundary
	 */
	std::vector<int> boundary_type;

	/**
	 * the size of the domain
	 * [0] - length of the domain in x direction
	 * [1] - length of the domain in y direction
	 * [2] - length of the domain in z direction
	 */
	Vector<double, 3>& domain_size;

	/**
	 * the number of cells in x direction
	 */
	int& width;
	/**
	 * the number of cells in y direction
	 */
	int& height;
	/**
	 * the number of cells in z direction
	 */
	int& depth;

	/**
	 * the container with the particles
	 */
	LCParticleContainer& container;

	/**
	 * the distance to the boundary where the reflecting boundary condition engages
	 */
	double h;

	/**
	 * the computeForce borrowed from MolSim.cpp
	 */
	void (*calculate)(Particle*, Particle*);
};

} /* namespace utils */

#endif /* BOUNDARYHANDLER_H_ */
