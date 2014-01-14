/*
 * MembraneTest.cpp
 *
 *  Created on: Jan 12, 2014
 *      Author: son
 */

#include <string>
#include <cstring>
#include <algorithm>
#include <iostream>

#include "MembraneTest.h"
#include "utils/Vector.h"

MembraneTest::MembraneTest() {
	// TODO Auto-generated constructor stub

}

MembraneTest::~MembraneTest() {
	// TODO Auto-generated destructor stub
}

void MembraneTest::setUp(){
	std::string fileName = "src/tests/testFiles/TestMembrane.xml";
	char *cstr = new char[fileName.length() + 1];
	strcpy(cstr, fileName.c_str());

	pgen.extractCuboids(cstr);
	(*(*pgen.getCuboidList().begin())).initNeighbors();
	cub = **pgen.getCuboidList().begin();
	pgen.cuboidsToList();
	parList = pgen.getParticleList();
}

void MembraneTest::tearDown(){

}

void MembraneTest::testInitNeighbors(){
	//testGetDirectNeighbors();
	//testGetDiagNeighbors();
}

void MembraneTest::testGetParticleAtID(){
	Particle pNull(
			utils::Vector<double, 3>(0.0),
			utils::Vector<double, 3>(0.0),
			1.0, 1);
	pNull.getID() = -1;

	for (int i = 0; i<100; i++){
		Particle* p = cub.getParticleAtID(&pNull, i);
		//CPPUNIT_ASSERT(p->getID() != -1);
		CPPUNIT_ASSERT(p->getID() == i);
	}

	Particle* p1 = cub.getParticleAtID(&pNull, -1);
	CPPUNIT_ASSERT(p1->getID() == -1);
	p1 = cub.getParticleAtID(&pNull, -2);
	CPPUNIT_ASSERT(p1->getID() == -1);
	p1 = cub.getParticleAtID(&pNull, -20);
	CPPUNIT_ASSERT(p1->getID() == -1);

	p1 = cub.getParticleAtID(&pNull, 101);
	CPPUNIT_ASSERT(p1->getID() == -1);
	p1 = cub.getParticleAtID(&pNull, 102);
	CPPUNIT_ASSERT(p1->getID() == -1);
	p1 = cub.getParticleAtID(&pNull, 200);
	CPPUNIT_ASSERT(p1->getID() == -1);

}

void MembraneTest::testGetDirectNeighbors(){
	for (std::list<Particle*>::iterator it = parList.begin();
			it != parList.end(); it++){
		int count = 0;
		for(std::list<Particle*>::iterator its = (*(*it)).getDirectNeighbors().begin();
				its != (*(*it)).getDirectNeighbors().end(); its++){
			//no more pNull in the list
			CPPUNIT_ASSERT((*(*its)).getID() != -1);

			double distance = ((*(*it)).getX() - (*(*its)).getX()).L2Norm();
			CPPUNIT_ASSERT(distance <= 1.0);

			count++;
			CPPUNIT_ASSERT(count <= 4);
		}
	}
}

void MembraneTest::testGetDiagNeighbors(){
	for (std::list<Particle*>::iterator it = parList.begin();
			it != parList.end(); it++){
		int count = 0;
		for(std::list<Particle*>::iterator its = (*(*it)).getDiagNeighbors().begin();
				its != (*(*it)).getDiagNeighbors().end(); its++){
			//no more pNull in the list
			CPPUNIT_ASSERT((*(*its)).getID() != -1);

			double distance = ((*(*it)).getX() - (*(*its)).getX()).L2Norm();
			CPPUNIT_ASSERT(distance <= 1.0*sqrt(2.0));

			count++;
			CPPUNIT_ASSERT(count <= 4);
		}
	}
}

void MembraneTest::testGetID(){
	std::list<int> idList;
	idList.clear();
	for (std::list<Particle*>::iterator it = parList.begin();
			it != parList.end(); it++){
		idList.push_back((*(*it)).getID());
	}
	//test size
	CPPUNIT_ASSERT(idList.size() == 100);

	//test uniqueness of each ID (each ID must exist only once)
	idList.sort();

	std::list<int>::iterator ii = idList.begin();
	CPPUNIT_ASSERT(*ii == 0);
	ii++;
	CPPUNIT_ASSERT(*ii == 1);
	ii++;
	CPPUNIT_ASSERT(*ii == 2);

	int i = 0;
	for (std::list<int>::iterator iti = idList.begin();
			iti != idList.end(); iti++){
		CPPUNIT_ASSERT(*iti == i);
		i++;
	}

	//test coordinates
	//input: h=1, size=10x10, origin={0,0,0}
	for (std::list<Particle*>::iterator it = parList.begin();
			it != parList.end(); it++){
		int id = (*(*it)).getID();
		int pos_of_line = id/10;
		int pos_of_col = id % 10;
		CPPUNIT_ASSERT((*(*it)).getX()[0] == pos_of_col*1.0);
		CPPUNIT_ASSERT((*(*it)).getX()[1] == pos_of_line*1.0);
	}
}

void MembraneTest::testIsDirectNeighborTo(){
	int count = 0;
	for (std::list<Particle*>::iterator it1 = parList.begin();
			it1 != parList.end(); it1++){
		for (std::list<Particle*>::iterator it2 = parList.begin();
				it2 != parList.end(); it2++){
			std::list<Particle*> listS = (*(*it1)).getDirectNeighbors();
			std::list<Particle*>::iterator its = std::find(listS.begin(), listS.end(), *it2);
			if (its == listS.end()){
				CPPUNIT_ASSERT((*(*it1)).isDirectNeighborTo(*it2) == false);
			}else{
				CPPUNIT_ASSERT((*(*it1)).isDirectNeighborTo(*it2) == true);
				count++;
			}
		}
	}

	CPPUNIT_ASSERT(count <= 4);

	count = 0;
	for (std::list<Particle*>::iterator it1 = parList.begin();
			it1 != parList.end(); it1++){
		for (std::list<Particle*>::iterator it2 = parList.begin();
				it2 != parList.end(); it2++){
			double distance = ((*(*it1)).getX() - (*(*it2)).getX()).L2Norm();
			if ((*(*it1)).isDirectNeighborTo(*it2)){
				CPPUNIT_ASSERT(distance <= 1.0);
				count++;
			}else{
				CPPUNIT_ASSERT(distance > 1.0);
			}
		}
	}

	CPPUNIT_ASSERT(count <= 4);
}

void MembraneTest::testIsDiagNeighborTo(){
	int count = 0;
	for (std::list<Particle*>::iterator it1 = parList.begin();
			it1 != parList.end(); it1++){
		for (std::list<Particle*>::iterator it2 = parList.begin();
				it2 != parList.end(); it2++){
			std::list<Particle*> listS = (*(*it1)).getDiagNeighbors();
			std::list<Particle*>::iterator its = std::find(listS.begin(), listS.end(), *it2);
			if (its == listS.end()){
				CPPUNIT_ASSERT((*(*it1)).isDiagNeighborTo(*it2) == false);
			}else{
				CPPUNIT_ASSERT((*(*it1)).isDiagNeighborTo(*it2) == true);
				count++;
			}
		}
	}

	CPPUNIT_ASSERT(count <= 4);

	count = 0;
	for (std::list<Particle*>::iterator it1 = parList.begin();
			it1 != parList.end(); it1++){
		for (std::list<Particle*>::iterator it2 = parList.begin();
				it2 != parList.end(); it2++){
			double distance = ((*(*it1)).getX() - (*(*it2)).getX()).L2Norm();
			if ((*(*it1)).isDiagNeighborTo(*it2)){
				CPPUNIT_ASSERT(distance <= 1.0*sqrt(2.0));
				count++;
			}else{
				CPPUNIT_ASSERT(distance > 1.0*sqrt(2.0));
			}
		}
	}

	CPPUNIT_ASSERT(count <= 4);
}

CppUnit::Test *MembraneTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"ParticleContainerTest");

	testSuite->addTest(
			new CppUnit::TestCaller<MembraneTest>("testGetDiagNeighbors",
					&MembraneTest::testGetDiagNeighbors));

	testSuite->addTest(
			new CppUnit::TestCaller<MembraneTest>("testGetDirectNeighbors",
					&MembraneTest::testGetDirectNeighbors));

	testSuite->addTest(
			new CppUnit::TestCaller<MembraneTest>("testGetID",
					&MembraneTest::testGetID));

	testSuite->addTest(
			new CppUnit::TestCaller<MembraneTest>("testGetParticleAtID",
					&MembraneTest::testGetParticleAtID));

	testSuite->addTest(
			new CppUnit::TestCaller<MembraneTest>("testInitNeighbors",
					&MembraneTest::testInitNeighbors));

	testSuite->addTest(
			new CppUnit::TestCaller<MembraneTest>("testIsDiagNeighborTo",
					&MembraneTest::testIsDiagNeighborTo));

	testSuite->addTest(
			new CppUnit::TestCaller<MembraneTest>("testIsDirectNeighborTo",
					&MembraneTest::testIsDirectNeighborTo));

	return testSuite;
}