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
	 * @return the first element of the container
	 */
	LCInnerParticleIterator beginInner(LCOuterParticleIterator it);

	/**
	 * @return the last element of the container
	 */
	LCOuterParticleIterator endOuter();

	LCInnerParticleIterator endInner(int i);

	void deleteHalo();

	/**
	 * updates the list of cells(also used to initialize)
	 */
	void updateCells();


	void initializeCells();

	/**
	 * @ return the particles list
	 */
	std::list<Particle>& getList();

	int size();

	void toList();

private:
	/**
	 * contains the list of the given particles
	 */
	std::list<Particle> particles;

	/**
	 * contains the vector of cells of the given particles
	 */
	std::vector<std::list<Particle> > cells;

	/**
	 * contains the list of the particles in the halo zone
	 */
	std::list<Particle> halo;

	/**
	 * contains the size of the domain.
	 * domain_size[0] - valid region of the "x-axis"
	 * domain_size[1] - valid region of the "y-axis"
	 * domain_size[2] - valid region of the "z-axis"
	 */
	utils::Vector<double, 3> domain_size;

	/**
	 * length of the edges(3D or 2D) of the cells
	 */
	double cutoff_radius;

	/**
	 * number of cells in the "x-axis" = domain_size[0] / cutoff_radius
	 */
	int width;

	/**
	 * number of cells in the "y-axis" = domain_size[1] / cutoff_radius
	 */
	int height;

	/**
	 * number of cells in the "z-axis" = domain_size[2] / cutoff_radius
	 */
	int depth;

	/**
	 * number of cells
	 */
	int num_of_cells;
};

} /* namespace utils */

#endif /* LCPARTICLECONTAINER_H_ */
