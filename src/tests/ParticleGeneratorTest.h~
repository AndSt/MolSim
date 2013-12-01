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

	void testExtractCuboids();

	void testExtractParticles();
	
	void testExtractSetting();

	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleGenerator
	 */
	static Test *suite();

private:
	/**
	 * Cuboids, to test the readCuboids() method
	 */
	Cuboid cuboid1, cuboid2;

	/**
	 * Generated particle list
	 */
	std::list<Particle> particles;
	/**
	 * Generator to test
	 */
	utils::ParticleGenerator generator;

	double start_time, end_time, delta_t, EPSILON, SIGMA; 
	string inputName, inputType, outputMask;
	int outputFreq;
	utils::Vector<double, 3> domainSize;
	double rcutoff;
};

#endif /* PARTICLEGENERATORTEST_H_ */
