/*
 * ParticleGeneratorTest.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: andal
 */

#include "ParticleGeneratorTest.h"

ParticleGeneratorTest::ParticleGeneratorTest(){

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
	generator.readCuboids("src/tests/testFiles/generator.txt");

}

void ParticleGeneratorTest::tearDown() {

}

void ParticleGeneratorTest::testReadCuboids() {

	//Check first cuboid
	Cuboid testCuboid = *generator.getCuboids().begin();
	CPPUNIT_ASSERT(cuboid1.getDepth() == testCuboid.getDepth());
	CPPUNIT_ASSERT(cuboid1.getHeight() == testCuboid.getHeight());
	CPPUNIT_ASSERT(cuboid1.getWidth() == testCuboid.getWidth());
	CPPUNIT_ASSERT(cuboid1.getMass() == testCuboid.getMass());
	CPPUNIT_ASSERT(cuboid1.getDistance() == testCuboid.getDistance());
	CPPUNIT_ASSERT(cuboid1.getOrigin() == testCuboid.getOrigin());
	CPPUNIT_ASSERT(cuboid1.getStartV() == testCuboid.getStartV());
	CPPUNIT_ASSERT(cuboid1.getMeanV() == testCuboid.getMeanV());

	//Check second cuboid
	testCuboid = *(++generator.getCuboids().begin());
	CPPUNIT_ASSERT(cuboid2.getDepth() == testCuboid.getDepth());
	CPPUNIT_ASSERT(cuboid2.getHeight() == testCuboid.getHeight());
	CPPUNIT_ASSERT(cuboid2.getWidth() == testCuboid.getWidth());
	CPPUNIT_ASSERT(cuboid2.getMass() == testCuboid.getMass());
	CPPUNIT_ASSERT(cuboid2.getDistance() == testCuboid.getDistance());
	CPPUNIT_ASSERT(cuboid2.getOrigin() == testCuboid.getOrigin());
	CPPUNIT_ASSERT(cuboid2.getStartV() == testCuboid.getStartV());
	CPPUNIT_ASSERT(cuboid2.getMeanV() == testCuboid.getMeanV());
}

void ParticleGeneratorTest::testCuboidsToList(){
	generator.cuboidsToList(particles);

	//Test first part of the list by checking the equality of the list in
	//cuboid1
	std::list<Particle>::iterator particleIterator = particles.begin();
	std::list<Particle>::iterator cuboidIterator = cuboid1.getCuboid().begin();
	while(cuboidIterator != cuboid1.getCuboid().end()){
		CPPUNIT_ASSERT(*cuboidIterator == *particleIterator);
		++particleIterator;
		++cuboidIterator;
	}

	//Test second part of the list by checking the equality of the list in
	//cuboid2
	cuboidIterator = cuboid2.getCuboid().begin();
	while(cuboidIterator != cuboid2.getCuboid().end()){
			CPPUNIT_ASSERT(*cuboidIterator == *particleIterator);
			++particleIterator;
			++cuboidIterator;
		}
}

CppUnit::Test *ParticleGeneratorTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"ParticleGeneratorTest");
	testSuite->addTest(
				new CppUnit::TestCaller<ParticleGeneratorTest>("testReadCuboids",
						&ParticleGeneratorTest::testReadCuboids));
	std::cout << "##############################################################" << std::endl;
	testSuite->addTest(
					new CppUnit::TestCaller<ParticleGeneratorTest>("testCuboidstoList",
							&ParticleGeneratorTest::testCuboidsToList));
	return testSuite;
}
