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

void ParticleIteratorTest::setUp(){
	FileReader fileReader;
	fileReader.readFile(particles, "container_iterator_tests.txt");
	container.initialize(particles);

	particle1 = new ParticleIterator(container.begin());
	particle2 = new ParticleIterator(container.begin());
	particle3=  new ParticleIterator((++container.begin()));
}

void ParticleIteratorTest::tearDown(){
	delete particle1;
	delete particle2;
	delete particle3;
}

void ParticleIteratorTest::testConstructor(){
	CPPUNIT_ASSERT(*ParticleIterator(container.begin) == *particle1);
	CPPUNIT_ASSERT(!(*ParticleIterator(container.begin) == *particle3));
}

void ParticleIteratorTest::testInequality(){
	CPPUNIT_ASSERT(!(particle1 != particle2));
	CPPUNIT_ASSERT(particle1 != particle3);
}

void ParticleIteratorTest::testParticleReference(){
	CPPUNIT_ASSERT(*particle1 == *particle2);
	CPPUNIT_ASSERT(!(*particle1 == *particle3));
}

void ParticleIteratorTest::testIteration(){
	CPPUNIT_ASSERT(++particle1 == ++particle2);
	CPPUNIT_ASSERT(!(++particle1 == ++particle3));
}


