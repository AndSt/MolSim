/*
 * ParticleContainerTest.h
 *
 *  Created on: Nov 10, 2013
 *      Author: andal
 */

#ifndef PARTICLECONTAINERTEST_H_
#define PARTICLECONTAINERTEST_H_

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string.h>
#include <list>
#include <Particle.h>
#include <utils/ParticleContainer.h>
#include <FileReader.h>

class ParticleContainerTest: public CppUnit::TestCase {
public:
	ParticleContainerTest();
	virtual ~ParticleContainerTest();

	/**
	 * Set up the test variables(container, particles)
	 */
	void setUp();

	/**
	 *
	 */
	void tearDown();

	/**
	 * Check the initialization of the ParticleContainer
	 */
	void testInitialize();

	/**
	 * Check the begin() method of the ParticleContainer
	 */
	void testBegin();

	/**
	 * Check the end() method of the ParticleContainer
	 */
	void testEnd();

	/**
	 * Check the getList() method of the ParticleContainer
	 */
	void testGetList();

	/**
	 * Check the size() method of the ParticleContainer
	 */
	void testSize();

	/**
	 *
	 * @return the TestSuite for the tested methods of ParticleContainer
	 */
	static Test *suite();

private:
	/**
	 * The particle container who will be tested
	 */
	utils::ParticleContainer container;
	/**
	 * The particle list, which will be used to compare to the container
	 */
	std::list<Particle> particles;
};

#endif /* PARTICLECONTAINERTEST_H_ */
