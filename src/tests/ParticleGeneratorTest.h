/*
 * ParticleGeneratorTest.h
 *
 *  Created on: Nov 13, 2013
 *      Author: andal
 */

#ifndef PARTICLEGENERATORTEST_H_
#define PARTICLEGENERATORTEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include <list>
#include <Cuboid.h>
#include <utils/ParticleGenerator.h>
#include <utils/Vector.h>
#include <FileReader.h>

class ParticleGeneratorTest : CppUnit::TestCase {
public:
	ParticleGeneratorTest();
	virtual ~ParticleGeneratorTest();

	/**
	 *	Set up the two cuboids and the 3 tested particles
	 */
	void setUp();

	/**
	 *
	 */
	void tearDown();

	/**
	 * Tests the readCuboids() method
	 */
	void testReadCuboids();

	/**
	 * Tests the cuboidsToList() method
	 */
	void testCuboidsToList();

	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleGenerator
	 */
	static Test *suite();

private:
	Cuboid cuboid1, cuboid2;
	std::list<Particle> particles;
	ParticleGenerator generator;
};

#endif /* PARTICLEGENERATORTEST_H_ */
