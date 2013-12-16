/*
 * LCParticleContainerTest.h
 *
 *  Created on: Dec 4, 2013
 *      Author: andal
 */

#ifndef LCPARTICLECONTAINERTEST_H_
#define LCPARTICLECONTAINERTEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <list>
#include <Particle.h>
#include <utils/LCParticleContainer.h>
#include <FileReader.h>
#include <utils/ParticleGenerator.h>

class LCParticleContainerTest: public CppUnit::TestCase {
public:
	LCParticleContainerTest();
	virtual ~LCParticleContainerTest();

	/**
	 * Set up the test variables(container, particles)
	 */
	void setUp();

	/**
	 * Tear down the test
	 */
	void tearDown();

	/**
	 * Check the initialization of the ParticleContainer
	 */
	void testInitializeCells();

	/**
	 * Check the updateCells() method of the ParticleContainer
	 */
	void testUpdateCells();

	/**
	 * Check the size() method of the ParticleContainer
	 */
	void testSize();

	/**
	 * Check the beginOuter() method of the ParticleContainer
	 */
	void testBeginOuter();

	/**
	 * Check the endOuter() method of the ParticleContainer
	 */
	void testEndOuter();

	/**
	 * Check the beginInner() method of the ParticleContainer
	 */
	void testBeginInner();

	/**
	 * Check the endInner() method of the ParticleContainer
	 */
	void testEndInner();


	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleContainer
	 */
	static Test *suite();

private:
	/**
	 * The particle container who will be tested
	 */
	utils::LCParticleContainer container;

	/**
	 * width is the number of cells in x direction
	 * height is the number of cells in y direction
	 * depth is the number of cells in z direction
	 * num_of_cells is the total number of cells, width * height * depth (in case that depth is larger than 0
	 */
	int width, height, depth, num_of_cells;

	/**
	 * cutoff_radius is the cutoff_radius from the Lennard-Lones-Potential
	 * domain_size is the side length of the domain
	 */
	double cutoff_radius;
	utils::Vector<double, 3> domain_size;

	/**
	 * The particle list, which will be used to compare to the container
	 */
	std::list<Particle> particles;
};
#endif /* LCPARTICLECONTAINERTEST_H_ */
