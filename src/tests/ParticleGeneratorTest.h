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

#include <string.h>
#include <list>
#include <Cuboid.h>
#include <utils/ParticleGenerator.h>
#include <utils/Vector.h>
#include <FileReader.h>
#include "Particle.h"
#include "Sphere.h"

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

	void testExtractSpheres();

	void testExtractCuboids();

	void testExtractParticles();
	
	void testExtractSetting();

	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleGenerator
	 */
	static Test *suite();

private:
	utils::ParticleGenerator generator;
};

#endif /* PARTICLEGENERATORTEST_H_ */
