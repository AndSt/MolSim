/*
 * ParticleContainerTest.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: andal
 */

#include "ParticleContainerTest.h"

ParticleContainerTest::ParticleContainerTest() {
	// TODO Auto-generated constructor stub

}

ParticleContainerTest::~ParticleContainerTest() {
	// TODO Auto-generated destructor stub
}

void ParticleContainerTest::setUp() {
	FileReader fileReader;
	fileReader.readFile(particles, "container_iterator_tests.txt");
	container.initialize(particles);
}

void ParticleContainerTest::tearDown() {
}

void ParticleContainerTest::testBegin() {
	CPPUNIT_ASSERT(*particles.begin() == *container.begin());
}

void ParticleContainerTest::testEnd() {
	CPPUNIT_ASSERT(*particles.end() == *container.end());
}

void ParticleContainerTest::testGetList() {
	ParticleIterator pIterator = container.begin();
	std::list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		CPPUNIT_ASSERT(*iterator == *pIterator);
		++iterator;
		++pIterator;
	}
}

void ParticleContainerTest::testSize() {
	CPPUNIT_ASSERT(particles.size() == container.size());
}

CppUnit::Test *ParticleContainerTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"ParticleContainerTest");

	// add the tests
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleContainerTest>("testBegin",
					&ParticleContainerTest::testBegin));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleContainerTest>("testEnd",
					&ParticleContainerTest::testEnd));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleContainerTest>("testGetList",
					&ParticleContainerTest::testGetList));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleContainerTest>("testSize",
					&ParticleContainerTest::testSize));

	return testSuite;
}
