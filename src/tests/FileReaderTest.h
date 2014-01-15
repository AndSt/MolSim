/*
 * FileReaderTest.h
 *
 *  Created on: Dec 18, 2013
 *      Author: son
 */

#ifndef FILEREADERTEST_H_
#define FILEREADERTEST_H_

#include "Particle.h"

#include <list>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

class FileReaderTest : public CppUnit::TestCase{
public:
	FileReaderTest();

	void setUp();

	void tearDown();

	void testReadStatus();

	static Test *suite();

	virtual ~FileReaderTest();

private:
	std::list<Particle> testL;
};

#endif /* FILEREADERTEST_H_ */
