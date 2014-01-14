/*
 * LCOuterParticleIteratorTest.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: andal
 */

#include "utils/LCOuterParticleIterator.h"
#include "LCOuterParticleIteratorTest.h"

LCOuterParticleIteratorTest::LCOuterParticleIteratorTest() {
}

LCOuterParticleIteratorTest::~LCOuterParticleIteratorTest() {
}

void LCOuterParticleIteratorTest::setUp() {
	FileReader fileReader;
	std::string fileName = "src/tests/testFiles/lc_container.txt";
	char *cstr = new char[fileName.length() + 1];
	strcpy(cstr, fileName.c_str());
	utils::ParticleGenerator pgen;
	pgen.readCuboids(cstr);
	pgen.cuboidsToList();
	particles = pgen.getParticleList();
	//initialize container
	CPPUNIT_ASSERT(particles.empty() == false);
	cutoff_radius = 3.0;
	double domain_size_arg[3] = { 180, 90, 0 };
	domain_size = utils::Vector<double, 3>(domain_size_arg);

	width = domain_size[0] / cutoff_radius;
	height = domain_size[1] / cutoff_radius;
	depth = domain_size[2] / cutoff_radius;
	num_of_cells = width * height * 1;

	container.initialize(particles, domain_size, cutoff_radius);
}

void LCOuterParticleIteratorTest::tearDown() {

}

void LCOuterParticleIteratorTest::testAssignment() {
	//setUp Variables
	utils::LCOuterParticleIterator iterator1 = container.beginOuter();
	utils::LCOuterParticleIterator iterator2 = iterator1;
	utils::LCOuterParticleIterator iterator3 = container.beginOuter();
	++iterator3;

	CPPUNIT_ASSERT(!(iterator1 != iterator2));
	CPPUNIT_ASSERT(iterator1.getCellNumber() == iterator2.getCellNumber());
	CPPUNIT_ASSERT((iterator1 != iterator3));
	CPPUNIT_ASSERT(iterator1.getCellNumber() != iterator3.getCellNumber());

}

void LCOuterParticleIteratorTest::testInequality() {

	utils::LCOuterParticleIterator iterator1 = container.beginOuter();
	utils::LCOuterParticleIterator iterator2 = iterator1;
	utils::LCOuterParticleIterator iterator3 = container.beginOuter();
	++iterator3;
	//two features to test:

	//1. != operation

	CPPUNIT_ASSERT(!(iterator1 != iterator2));
	CPPUNIT_ASSERT(iterator1 != iterator3);

	//2. check if the function returns false, if the cell number of first
	// 	 element is bigger than the cell number of the second element
	//	 (otherwise we will go further than the last element of the outerIterator..)

	CPPUNIT_ASSERT(!(iterator2 != iterator1));

}

void LCOuterParticleIteratorTest::testParticleReference() {
	//setUp Variables
	utils::LCOuterParticleIterator iterator1 = container.beginOuter();
	utils::LCOuterParticleIterator iterator2 = iterator1;
	utils::LCOuterParticleIterator iterator3 = container.beginOuter();
	++iterator3;

	CPPUNIT_ASSERT((*iterator1) == (*iterator2));
	CPPUNIT_ASSERT(!((*iterator1) == (*iterator3)));
}

void LCOuterParticleIteratorTest::testIteration() {
	//gehe durch alle elemente
	//checke, ob es für
	//fill the array with the size of each cell:
	int size[num_of_cells];
	for (int i = 0; i < num_of_cells; i++) {
		size[i] = 0;
	}
	std::list<Particle*>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		Particle p = **iterator;
		if (p.getX()[0] <= domain_size[0] && p.getX()[1] <= domain_size[1]
				&& p.getX()[2] <= domain_size[2]) {
			int i = (int) (p.getX()[0] / cutoff_radius)
					+ ((int) (p.getX()[1] / cutoff_radius)) * width
					+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
			size[i]++;
		}
		++iterator;
	}

	//go threw all particles and minimize the size array
	utils::LCOuterParticleIterator iiterator = container.beginOuter();
	while (iiterator != container.endOuter()) {
		Particle &p = (*iiterator);
		int i = (int) (p.getX()[0] / cutoff_radius)
				+ ((int) (p.getX()[1] / cutoff_radius)) * width
				+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
		size[i]++;
		++iiterator;
	}

	for(int i = 0; i < num_of_cells; i++){
		CPPUNIT_ASSERT(size[i] == 0);
	}
}

void LCOuterParticleIteratorTest::testGetCellNumber() {
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	while (iterator != container.endOuter()) {
		Particle &p = *iterator;
		int i = (int) (p.getX()[0] / cutoff_radius)
				+ ((int) (p.getX()[1] / cutoff_radius)) * width
				+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
		CPPUNIT_ASSERT(i == iterator.getCellNumber());
		++iterator;
	}
}

void LCOuterParticleIteratorTest::testGetIterator() {
	utils::LCOuterParticleIterator iterator1 = container.beginOuter();
	utils::LCOuterParticleIterator iterator2 = iterator1;
	utils::LCOuterParticleIterator iterator3 = container.beginOuter();
	++iterator3;

	std::list<Particle *>::iterator iiterator1 = iterator1.getIterator();
	std::list<Particle *>::iterator iiterator2 = iterator1.getIterator();
	std::list<Particle *>::iterator iiterator3 = iterator1.getIterator();

	CPPUNIT_ASSERT((*iterator1) == *(*iiterator1));
	CPPUNIT_ASSERT((*iterator1) == *(*iiterator2));
	CPPUNIT_ASSERT(((*iterator1) == *(*iiterator3)));
}

CppUnit::Test *LCOuterParticleIteratorTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"LCOuterParticleIteratorTest");

	// add the tests
	testSuite->addTest(
			new CppUnit::TestCaller<LCOuterParticleIteratorTest>(
					"testAssignment",
					&LCOuterParticleIteratorTest::testAssignment));
	testSuite->addTest(
			new CppUnit::TestCaller<LCOuterParticleIteratorTest>(
					"testGetIterator",
					&LCOuterParticleIteratorTest::testGetIterator));
	testSuite->addTest(
			new CppUnit::TestCaller<LCOuterParticleIteratorTest>(
					"testParticleReference",
					&LCOuterParticleIteratorTest::testParticleReference));
	testSuite->addTest(
			new CppUnit::TestCaller<LCOuterParticleIteratorTest>(
					"testGetCellNumber",
					&LCOuterParticleIteratorTest::testGetCellNumber));
	testSuite->addTest(
			new CppUnit::TestCaller<LCOuterParticleIteratorTest>(
					"testInequality",
					&LCOuterParticleIteratorTest::testInequality));

	return testSuite;
}
