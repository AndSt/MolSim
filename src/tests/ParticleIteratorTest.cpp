/*
 * ParticleIteratorTest.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: andal
 */

#include "ParticleIteratorTest.h"

ParticleIteratorTest::ParticleIteratorTest() {
	// TODO Auto-generated constructor stub

}

ParticleIteratorTest::~ParticleIteratorTest() {
	// TODO Auto-generated destructor stub
}

void ParticleIteratorTest::setUp() {
	FileReader fileReader;
	std::list<Particle> particles;
	fileReader.readFile(particles, "eingabe-brownian.txt");
	container.initialize(particles);

	particle1 = container.begin();
	particle2 = container.begin();
	particle3 = container.begin();
	++particle3;
}

void ParticleIteratorTest::tearDown() {

}

void ParticleIteratorTest::testConstructor() {
	ParticleIterator testIt(container.begin());
	CPPUNIT_ASSERT(*testIt == *particle1);
	CPPUNIT_ASSERT(!(*testIt == *particle3));
}

void ParticleIteratorTest::testInequality() {
	CPPUNIT_ASSERT(!(particle1 != particle2));
	CPPUNIT_ASSERT(particle1 != particle3);
}

void ParticleIteratorTest::testParticleReference() {
	CPPUNIT_ASSERT(*particle1 == *particle2);
	CPPUNIT_ASSERT(!(*particle1 == *particle3));
}

void ParticleIteratorTest::testIteration() {
	CPPUNIT_ASSERT(*particle1 == *particle2);
	CPPUNIT_ASSERT(!(*particle1 == *particle3));
}

CppUnit::Test *ParticleIteratorTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"ParticleIteratorTest");

	// add the tests
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleIteratorTest>("testConstructor",
					&ParticleIteratorTest::testConstructor));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleIteratorTest>("testInequality", &ParticleIteratorTest::testInequality));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleIteratorTest>("testParticleReference",
					&ParticleIteratorTest::testParticleReference));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleIteratorTest>("testIteration", &ParticleIteratorTest::testIteration));

	return testSuite;
}
