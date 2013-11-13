/*
 * ParticleIteratorTest.h
 *
 *  Created on: Nov 10, 2013
 *      Author: andal
 */

#ifndef PARTICLEITERATORTEST_H_
#define PARTICLEITERATORTEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include <utils/ParticleContainer.h>
#include <utils/ParticleIterator.h>
#include <Particle.h>
#include <FileReader.h>

class ParticleIteratorTest: public CppUnit::TestCase {
public:
	ParticleIteratorTest();
	virtual ~ParticleIteratorTest();

	/**process:
	 * Set up the test variables
	 */
	void setUp();
	/**
	 * Delete the variables
	 */
	void tearDown();

	/**
	 * Check the Constructor of the Iterator
	 */
	void testConstructor();

	/**
	 * Check the "!=" operator of the iterator
	 */
	void testInequality();

	/**
	 * Check the "*" operator of the iterator
	 */
	void testParticleReference();

	/**
	 * Check the "++" operator of the iterator
	 */
	void testIteration();

	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleIterator
	 */
	static Test* suite();

private:
	/**
	 * Used Container to Check the Iterator
	 */
	ParticleContainer container;
	/**
	 * Used Iterators
	 */
	ParticleIterator particle1, particle2, particle3;

};

#endif /* PARTICLEITERATORTEST_H_ */
