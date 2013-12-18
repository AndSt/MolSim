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
			void (*calculate)(Particle&, Particle&));

	virtual ~BoundaryHandler();

	void applyBoundaries();

	void applyOutflow();

	void applyPeriodicMoving();

	void applyPeriodic();

	void applyReflecting();


private:
	/**
	 * saves the boundary condition of each boundary
	 * 		1 - outflow
	 * 		2 - reflecting boundary
	 * 		3 - periodic boundary
	 */
	std::vector<int> boundary_type;
	Vector<double, 3>& domain_size;
	int& width;
	int& height;
	int& depth;
	LCParticleContainer& container;

	double h;

	void (*calculate)(Particle&, Particle&);
};

} /* namespace utils */

#endif /* BOUNDARYHANDLER_H_ */
