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
#include <FileReader.h>

class ParticleGeneratorTest : CppUnit::TestCase {
public:
	ParticleGeneratorTest();
	virtual ~ParticleGeneratorTest();

	void setUp();

	void tearDown();

	void testReadCuboids();

	void testCuboidsToList();

	static Test *suite();

private:
	Cuboid cuboid1, cuboid2;
};

#endif /* PARTICLEGENERATORTEST_H_ */
