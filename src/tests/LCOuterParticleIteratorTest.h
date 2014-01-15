/*
 * LCOuterParticleIteratorTest.h
 *
 *  Created on: Nov 10, 2013
 *      Author: andal
 */

#ifndef LCOUTERPARTICLEITERATORTEST_H_
#define LCOUTERPARTICLEITERATORTEST_H_

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

class LCOuterParticleIteratorTest: public CppUnit::TestCase {
public:
	LCOuterParticleIteratorTest();
	virtual ~LCOuterParticleIteratorTest();

	/**process:
	 * Set up the test variables
	 */
	void setUp();
	/**
	 * Delete the variables
	 */
	void tearDown();

	/**
	 * Check the "!=" operator of the iterator
	 */
	void testInequality();

	/**
	 * Check the "=" operator of the iterator
	 */
	void testAssignment();

	/**
	 * Check the "*" operator of the iterator
	 */
	void testParticleReference();

	/**
	 * Check the "++" operator of the iterator
	 */
	void testIteration();

	/**
	 * Check the getIterator() method
 	 */
	void testGetIterator();


	/**
	 * Check the getCellNumber() method
 	 */
	void testGetCellNumber();


	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleIterator
	 */
	static Test* suite();

private:
	/**
	 * Used Container to Check the Iterator
	 */
	utils::LCParticleContainer container;

	int width, height, depth, cutoff_radius, num_of_cells;

	utils::Vector<double, 3> domain_size;

	std::list<Particle> particles;

	/**
	 * Used Iterators
	 */

};

#endif /* LCOUTERPARTICLEITERATORTEST_H_ */
