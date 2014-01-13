/*
 * MembraneTest.h
 *
 *  Created on: Jan 12, 2014
 *      Author: son
 */

#ifndef MEMBRANETEST_H_
#define MEMBRANETEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include <list>

#include "Cuboid.h"
#include "Particle.h"
#include "utils/ParticleGenerator.h"

class MembraneTest: public CppUnit::TestCase {
private:
	utils::ParticleGenerator pgen;

	std::list<Particle> parList;

	Cuboid cub;

public:
	MembraneTest();

	void setUp();

	void tearDown();

	void testInitNeighbors();

	void testGetParticleAtID();

	void testGetDirectNeighbors();

	void testGetDiagNeighbors();

	void testGetID();

	void testIsDirectNeighborTo();

	void testIsDiagNeighborTo();

	static Test *suite();

	virtual ~MembraneTest();
};

#endif /* MEMBRANETEST_H_ */
