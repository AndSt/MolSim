/*
 * ThermostatTest.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: son
 */

#include "ThermostatTest.h"
#include "FileReader.h"

#include <string.h>
#include <cmath>

ThermostatTest::ThermostatTest() {}

ThermostatTest::~ThermostatTest() {}

void ThermostatTest::setUp(){
	FileReader fileReader;
	std::list<Particle> pList;
	pList.clear();
	std::string fileName = "src/tests/testFiles/container+iterator.txt";
	char *cstr = new char[fileName.length() + 1];
	strcpy(cstr, fileName.c_str());
	fileReader.readFile(pList, cstr);

	for(std::list<Particle>::iterator it = pList.begin(); it!= pList.end(); it++){
		parList.push_back(&(*it));
	}

	std::string inp = "src/tests/testFiles/TestInputSetting.xml";
	thermo = Thermostat(inp);

	eKin = 0.5*(3.0e-6 + 9.55e-4*pow(0.425,2) + 1.0e-14*pow(0.0296,2));

	brownian_flag = true;
}

void ThermostatTest::tearDown(){}

void ThermostatTest::testGetEKin(){
	CPPUNIT_ASSERT(thermo.getEKin(parList) == eKin);
}

void ThermostatTest::testMeanV(){
	//Hardcode: mass = 1
	double v = sqrt(2*eKin/(2*4*1.0));
	CPPUNIT_ASSERT((brownian_flag==true)&&(thermo.getMeanV(parList, 2, 1.0)==v));
}

void ThermostatTest::testSetThermo(){
	//T_init = 0.5
	//delta_t=1.0
	thermo.setThermo(parList, 2, 40);
	// rounding error taken into account
	CPPUNIT_ASSERT(std::abs(thermo.getEKin(parList)/4 - 40) < 1 );
}

void ThermostatTest::testDefaultConstructor(){
	/*
	<enabled>false</enabled>
	<brownianFlag>true</brownianFlag>
	<initT>0.5</initT>
	<targetT>80</targetT>
	<deltaT>1.0</deltaT>
	<nThermo>1000</nThermo>
	<nDelta>40000</nDelta>
	*/
	CPPUNIT_ASSERT(thermo.getEnabled()==false);
	CPPUNIT_ASSERT(thermo.getBrownian_flag()==true);
	CPPUNIT_ASSERT(thermo.getT_init()==0.5);
	CPPUNIT_ASSERT(thermo.getT_target()==80);
	CPPUNIT_ASSERT(thermo.getDelta_T()==1.0);
	CPPUNIT_ASSERT(thermo.getn_thermo()==1000);
	CPPUNIT_ASSERT(thermo.getn_delta()==40000);
}

CppUnit::Test *ThermostatTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"ThermoTest");

	// add the tests
	testSuite->addTest(
			new CppUnit::TestCaller<ThermostatTest>("testGetEKin",
					&ThermostatTest::testGetEKin));
	testSuite->addTest(
				new CppUnit::TestCaller<ThermostatTest>("testMeanV",
						&ThermostatTest::testMeanV));
	testSuite->addTest(
				new CppUnit::TestCaller<ThermostatTest>("testSetThermo",
						&ThermostatTest::testSetThermo));
	testSuite->addTest(
					new CppUnit::TestCaller<ThermostatTest>("testDefaultConstructor",
							&ThermostatTest::testDefaultConstructor));
	return testSuite;
}
