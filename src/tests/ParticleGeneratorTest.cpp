/*
 * ParticleGeneratorTest.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: andal
 */

#include "ParticleGeneratorTest.h"

ParticleGeneratorTest::ParticleGeneratorTest() {

}

ParticleGeneratorTest::~ParticleGeneratorTest() {
	// TODO Auto-generated destructor stub
}

void ParticleGeneratorTest::setUp() {
	//Set up cuboid1
	utils::Vector<double, 3> oriXYZ(0.0);
	utils::Vector<double, 3> startVel(0.0);
	cuboid1 = Cuboid(8, 40, 1, 1.1225, 1, oriXYZ, startVel, 0.1);

	//Set up cuboid2
	double args[3] = { 15.0, 15.0, 0.0 };
	oriXYZ = utils::Vector<double, 3>(args);
	double argz[3] = { 0.0, -10.0, 0.0 };
	startVel = utils::Vector<double, 3>(argz);
	cuboid2 = Cuboid(8, 8, 1, 1.1225, 1, oriXYZ, startVel, 0.1);

	//set up the particle generator
	std::string fileName = "src/tests/testFiles/generator.txt";
	char *cstr = new char[fileName.length() + 1];
	strcpy(cstr, fileName.c_str());
	generator.readCuboids(cstr);
}

void ParticleGeneratorTest::tearDown() {

}

void ParticleGeneratorTest::testReadCuboids() {

	//Check first cuboid
	Cuboid testCuboid = *generator.getCuboidList().begin();
	CPPUNIT_ASSERT(cuboid1.getDepth() == testCuboid.getDepth());
	CPPUNIT_ASSERT(cuboid1.getHeight() == testCuboid.getHeight());
	CPPUNIT_ASSERT(cuboid1.getWidth() == testCuboid.getWidth());
	CPPUNIT_ASSERT(cuboid1.getMass() == testCuboid.getMass());
	CPPUNIT_ASSERT(cuboid1.getDistance() == testCuboid.getDistance());
	CPPUNIT_ASSERT(cuboid1.getOrigin() == testCuboid.getOrigin());
	CPPUNIT_ASSERT(cuboid1.getStartV() == testCuboid.getStartV());
	CPPUNIT_ASSERT(cuboid1.getMeanV() == testCuboid.getMeanV());

	//Check second cuboid
	testCuboid = *(++generator.getCuboidList().begin());
	CPPUNIT_ASSERT(cuboid2.getDepth() == testCuboid.getDepth());
	CPPUNIT_ASSERT(cuboid2.getHeight() == testCuboid.getHeight());
	CPPUNIT_ASSERT(cuboid2.getWidth() == testCuboid.getWidth());
	CPPUNIT_ASSERT(cuboid2.getMass() == testCuboid.getMass());
	CPPUNIT_ASSERT(cuboid2.getDistance() == testCuboid.getDistance());
	CPPUNIT_ASSERT(cuboid2.getOrigin() == testCuboid.getOrigin());
	CPPUNIT_ASSERT(cuboid2.getStartV() == testCuboid.getStartV());
	CPPUNIT_ASSERT(cuboid2.getMeanV() == testCuboid.getMeanV());
}

CppUnit::Test *ParticleGeneratorTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"ParticleGeneratorTest");
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleGeneratorTest>("testReadCuboids",
					&ParticleGeneratorTest::testReadCuboids));
	return testSuite;
}
