/*
 * FileReaderTest.cpp
 *
 *  Created on: Dec 18, 2013
 *      Author: son
 */

#include "FileReaderTest.h"
#include "Particle.h"
#include "utils/Vector.h"
#include "FileReader.h"

#include <string.h>

FileReaderTest::FileReaderTest() {}

FileReaderTest::~FileReaderTest() {}

void FileReaderTest::setUp(){
	// x v m t
	double x1[] = {1.0, 2.0, 0.0};
	double x2[] = {3.0, 4.0, 0.0};
	double x3[] = {5.0, 6.0, 0.0};

	utils::Vector<double, 3> xp1(x1);
	utils::Vector<double, 3> xp2(x2);
	utils::Vector<double, 3> xp3(x3);

	double v1[] = {10.0, 20.0, 0.0};
	double v2[] = {30.0, 40.0, 0.0};
	double v3[] = {50.0, 60.0, 0.0};

	utils::Vector<double, 3> vp1(v1);
	utils::Vector<double, 3> vp2(v2);
	utils::Vector<double, 3> vp3(v3);

	Particle p1(xp1, vp1, 11.0, 40);
	Particle p2(xp2, vp2, 22.0, 41);
	Particle p3(xp3, vp3, 33.0, 42);

	double f1[] = {-1.0, -2.0, 0.0};
	double f2[] = {-3.0, -4.0, 0.0};
	double f3[] = {-5.0, -6.0, 0.0};

	utils::Vector<double, 3> fp1(f1);
	utils::Vector<double, 3> fp2(f2);
	utils::Vector<double, 3> fp3(f3);

	double of1[] = {-10.0, -20.0, 0.0};
	double of2[] = {-30.0, -40.0, 0.0};
	double of3[] = {-50.0, -60.0, 0.0};

	utils::Vector<double, 3> ofp1(of1);
	utils::Vector<double, 3> ofp2(of2);
	utils::Vector<double, 3> ofp3(of3);

	p1.getF() = fp1;
	p2.getF() = fp2;
	p3.getF() = fp3;

	p1.getOldF() = ofp1;
	p2.getOldF() = ofp2;
	p3.getOldF() = ofp3;

	testL.clear();
	testL.push_back(&p1);
	testL.push_back(&p2);
	testL.push_back(&p3);
}

void FileReaderTest::tearDown(){

}

void FileReaderTest::testReadStatus(){
	FileReader fileReader;
	std::list<Particle*> parList;
	parList.clear();
	double eps = 10;
	double sig = 10;
	std::string n = "src/tests/testFiles/TestParListStatus.txt";
	char *cstr = new char[n.length() + 1];
	strcpy(cstr, n.c_str());
	fileReader.readStatus(parList, eps, sig, cstr);

	CPPUNIT_ASSERT(eps==1);
	CPPUNIT_ASSERT(sig==1);
	CPPUNIT_ASSERT(parList.size()==3);

	std::list<Particle*>::iterator itT = testL.begin();
	for (std::list<Particle*>::iterator it = parList.begin();
			it != parList.end(); it++){
		CPPUNIT_ASSERT((*(*it)).getX()==(*(*itT)).getX());
		CPPUNIT_ASSERT((*(*it)).getV()==(*(*itT)).getV());
		CPPUNIT_ASSERT((*(*it)).getF()==(*(*itT)).getF());
		CPPUNIT_ASSERT((*(*it)).getOldF()==(*(*itT)).getOldF());
		CPPUNIT_ASSERT((*(*it)).getM()==(*(*itT)).getM());
		CPPUNIT_ASSERT((*(*it)).getType()==(*(*itT)).getType());
		itT++;
	}

}

CppUnit::Test *FileReaderTest::suite(){
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"FileReaderTest");

	testSuite->addTest(
			new CppUnit::TestCaller<FileReaderTest>("testReadStatus",
					&FileReaderTest::testReadStatus));
	return testSuite;
}
