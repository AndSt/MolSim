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

void ParticleContainerTest::setUp(){
	FileReader fileReader;
	fileReader.readFile(particles, "container_iterator_tests.txt");
	container.initialize(particles);
}

void ParticleContainerTest::tearDown(){
}


void ParticleContainerTest::testBegin(){
	CPPUNIT_ASSERT(*particles.begin() == *container.begin());
}

void ParticleContainerTest::testEnd(){
	CPPUNIT_ASSERT(*particles.end() == *container.end());
}

void ParticleContainerTest::testGetList(){
	CPPUNIT_ASSERT(particles == container.getList());
}

void ParticleContainerTest::testSize(){
	CPPUNIT_ASSERT(particles.size == container.size());
}
