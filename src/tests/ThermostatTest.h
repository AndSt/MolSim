/*
 * ThermostatTest.h
 *
 *  Created on: Dec 10, 2013
 *      Author: son
 */

#ifndef THERMOSTATTEST_H_
#define THERMOSTATTEST_H_

#include "Particle.h"
#include "utils/Thermostat.h"

#include <list>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

class ThermostatTest : CppUnit::TestCase{
private:
	std::list<Particle> parList;

	Thermostat thermo;

	double eKin;

	bool brownian_flag;

public:
	ThermostatTest();
	virtual ~ThermostatTest();

	void setUp();

	void tearDown();

	void testDefaultConstructor();

	void testGetEKin();

	void testMeanV();

	void testSetThermo();

	static Test *suite();
};

#endif /* THERMOSTATTEST_H_ */
