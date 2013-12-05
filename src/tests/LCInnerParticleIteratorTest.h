/*
 * LCInnerParticleIteratorTest.h
 *
 *  Created on: Dec 4, 2013
 *      Author: andal
 */

#ifndef LCINNERPARTICLEITERATORTEST_H_
#define LCINNERPARTICLEITERATORTEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <utils/LCParticleContainer.h>
#include <utils/LCInnerParticleIterator.h>
#include <utils/LCOuterParticleIterator.h>
#include <utils/ParticleGenerator.h>
#include <Particle.h>
#include <FileReader.h>

class LCInnerParticleIteratorTest: public CppUnit::TestCase {
public:
	LCInnerParticleIteratorTest();
	virtual ~LCInnerParticleIteratorTest();

	/**process:
	 * Set up the test variables
	 */
	void setUp();
	/**
	 * Delete the variables
	 */
	void tearDown();

/**
	 * Check the "*" operator of the iterator
	 */
	void testParticleReference();

	void testGetCellNumber();

	void testAssignment();

	/**
	 * Check the "!=" operator of the iterator
	 */
	void testInequality();


	/**
	 * Check the "++" operator of the iterator
	 */
	void testIteration();

	void testCheckLeft();

	void testCheckRight();

	void testCheckBottom();

	void testCheckBack();

	void testCheckTop();

	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleIterator
	 */
	static Test* suite();

private:


	/**
		 * The particle container to check the Iterator
		 */
		utils::LCParticleContainer container;

		int width, height, depth, num_of_cells;

		double cutoff_radius;
		utils::Vector<double, 3> domain_size;

		/**
		 * The particle list, which will be used to compare to the container
		 */
		std::list<Particle> particles;

};


#endif /* LCINNERPARTICLEITERATORTEST_H_ */
