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
	fileReader.readFile(particles, "eingabe-brownian.txt");
	container.initialize(particles);
}

void ParticleContainerTest::tearDown() {
}

void ParticleContainerTest::testInitialize() {
	container.initialize(particles);
	CPPUNIT_ASSERT(*particles.begin() == *container.begin());
}

void ParticleContainerTest::testBegin() {
	CPPUNIT_ASSERT(*particles.begin() == *container.begin());
}

void ParticleContainerTest::testEnd() {

	//go to the the last element in both lists and check equality
	std::list<Particle>::iterator iterator1 = particles.begin();
	std::list<Particle>::iterator testIterator1;
	while (iterator1 != particles.end()) {
		testIterator1 = iterator1;
		++iterator1;
	}

	ParticleIterator iterator2 = container.begin();
	ParticleIterator testIterator2;
	while (iterator2 != container.end()) {
		testIterator2 = iterator2;
		++iterator2;
	}
	CPPUNIT_ASSERT(*testIterator1 == *testIterator2);
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

	testSuite->addTest(
			new CppUnit::TestCaller<ParticleContainerTest>("testInitialize",
					&ParticleContainerTest::testInitialize));
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
