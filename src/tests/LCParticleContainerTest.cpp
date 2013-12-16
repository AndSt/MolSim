/*
 * LCParticleContainerTest.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: andal
 */

#include "../utils/LCParticleContainer.h"
#include "LCParticleContainerTest.h"

#include <cppunit/Asserter.h>
#include <cppunit/Message.h>
#include <cppunit/SourceLine.h>
#include <cppunit/TestAssert.h>
#include <string>

#include "../utils/ParticleGenerator.h"

LCParticleContainerTest::LCParticleContainerTest() {
	// TODO Auto-generated constructor stub

}

LCParticleContainerTest::~LCParticleContainerTest() {
	// TODO Auto-generated destructor stub
}

void LCParticleContainerTest::setUp() {
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

void LCParticleContainerTest::tearDown() {

}

void LCParticleContainerTest::testInitializeCells() {

	std::cout << "testinitializeCells" << std::endl;
	// iterate over the original particles
	//		- test if they are in the right cell
	//		- or test if they are in the halo region

	std::list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		Particle &p = *iterator;
		if (p.getX()[0] <= domain_size[0] && p.getX()[1] <= domain_size[1]
				&& p.getX()[2] <= domain_size[2]) {
			int i = (int) (p.getX()[0] / cutoff_radius)
					+ ((int) (p.getX()[1] / cutoff_radius)) * width
					+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;

			//test if they are reachable threw LCOuterParticleIterator
			utils::LCOuterParticleIterator iiterator = container.beginOuter();
			while (iiterator != container.endOuter()) {
				if ((*iterator) == (*iiterator)) {
					break;
				}
				++iiterator;
			}
			CPPUNIT_ASSERT((*iterator) == (*iiterator));

			//test if they are reachable threw LCInnerParticleIterator
			utils::LCInnerParticleIterator iiiterator = container.beginInner(
					iiterator);
			while (iiiterator != container.endInner(iiterator.getCellNumber())) {
				if ((*iterator) == (*iiiterator)) {
					break;
				}
				++iiiterator;
			}
			CPPUNIT_ASSERT((*iterator) == (*iiiterator));
		}
		//test if they are in the halo region
		else {
//			std::list<Particle *>::iterator iiterator =
//					container.getHaloList().begin();
//			while (iiterator != container.getHaloList().end()) {
//				if ((*iterator) == (**iiterator)) {
//					break;
//				}
//				++iiterator;
//			}
//			CPPUNIT_ASSERT((*iterator) == (**iiterator));
		}
		++iterator;
	}
}

void LCParticleContainerTest::testUpdateCells() {
	container.updateCells();
	//we haven't changed the particles, so we only have to test, if all
	//the particles are in the right cell
	//testInitializeCells();
}


void LCParticleContainerTest::testSize() {
	int i = 0;
	std::list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		//test if they are in the right cell
		if (((*iterator).getX())[0] <= domain_size[0]
				&& (*iterator).getX()[1] <= domain_size[1]
				&& (*iterator).getX()[2] <= domain_size[2]) {
			++i;
		}
		++iterator;
	}
	CPPUNIT_ASSERT(i == container.size());
}

void LCParticleContainerTest::testBeginOuter() {

	int firstCell = num_of_cells + 10; //first cell which is containing particles
	std::list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		Particle &p = *iterator;
		if (p.getX()[0] <= domain_size[0] && p.getX()[1] <= domain_size[1]
				&& p.getX()[2] <= domain_size[2]) {
			int i = (int) (p.getX()[0] / cutoff_radius)
					+ ((int) (p.getX()[1] / cutoff_radius)) * width
					+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
			if (i < firstCell) {
				firstCell = i;
			}
		}
		++iterator;
	}
	//check if container.beginOuter() has the same cellNumber as the particle
	//with the lowest index computed out of the original particle list
	utils::LCOuterParticleIterator iiterator = container.beginOuter();
	CPPUNIT_ASSERT(firstCell == iiterator.getCellNumber());

	//check if container.beginOuter() is in the list
	iterator = particles.begin();
	while (iterator != particles.end()) {
		if ((*iterator) == (*iiterator)) {
			break;
		}
		++iterator;
	}
	CPPUNIT_ASSERT((*iterator) == (*iiterator));
}

void LCParticleContainerTest::testEndOuter() {
	int lastCell = 0; 	//first cell which is containing particles
	std::list<Particle>::iterator iterator = particles.begin();
	while (iterator != particles.end()) {
		Particle &p = *iterator;
		if (p.getX()[0] <= domain_size[0] && p.getX()[1] <= domain_size[1]
				&& p.getX()[2] <= domain_size[2]) {
			int i = (int) (p.getX()[0] / cutoff_radius)
					+ ((int) (p.getX()[1] / cutoff_radius)) * width
					+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
			if (i > lastCell) {
				lastCell = i;
			}
		}
		++iterator;
	}
	--iterator;
	utils::LCOuterParticleIterator iiterator = container.endOuter();

	//check if container.endOuter() has the same cellNumber as the particle
	//with the highest index computed out of the original particle list
	CPPUNIT_ASSERT(lastCell == iiterator.getCellNumber());

	//check if container.endOuter() is in the list
	utils::LCOuterParticleIterator outerIterator = container.beginOuter();
	while (outerIterator != container.endOuter()) {
		if ((*iterator) == (*outerIterator)) {
			break;
		}
		++outerIterator;
	}

	CPPUNIT_ASSERT((*iterator) == (*outerIterator));
	++outerIterator;
	CPPUNIT_ASSERT(!(outerIterator != container.endOuter()));
}

void LCParticleContainerTest::testBeginInner() {

	// go threw all cells (in the tests before we checked that they are in
	// the old particle list)
	//		check for all beginning elements of these cells if there is an
	//		element before them in this cell

	utils::LCOuterParticleIterator outerIterator = container.beginOuter();
	int i = 0;
	while (outerIterator != container.endOuter()) {
		i = outerIterator.getCellNumber();
		utils::LCInnerParticleIterator begin = container.beginInner(
				outerIterator);
		utils::LCOuterParticleIterator innerIterator1 = container.beginOuter();
		while (innerIterator1 != container.endOuter()) {
			if (innerIterator1.getCellNumber() == i) {
				utils::LCOuterParticleIterator innerIterator2 = innerIterator1;
				while (innerIterator2 != container.endOuter()) {
					if ((*innerIterator2) == (*begin)) {
						break;
					}
					++innerIterator2;
				}
				if (innerIterator2 != container.endOuter()) {
					CPPUNIT_ASSERT((*innerIterator2) == (*begin));
				}

			}
			++innerIterator1;
		}
		++outerIterator;
	}
}

void LCParticleContainerTest::testEndInner() {

	//go threw all cells:
	//		1. check the size of the cell
	//		2. call |size| times ++
	//		3. check if it's the end of list of the cell

	utils::LCOuterParticleIterator outerIterator = container.beginOuter();
	int i = 0;
	while (outerIterator != container.endOuter()) {
		i = outerIterator.getCellNumber();
		std::list<Particle>::iterator sizeIterator = particles.begin();
		int size = 0;
		while (sizeIterator != particles.end()) {
			Particle &p = *sizeIterator;
			if (p.getX()[0] <= domain_size[0] && p.getX()[1] <= domain_size[1]
					&& p.getX()[2] <= domain_size[2]) {
				int j = (int) (p.getX()[0] / cutoff_radius)
						+ ((int) (p.getX()[1] / cutoff_radius)) * width
						+ ((int) (p.getX()[2] / cutoff_radius)) * width
								* height;
				if (i == j) {
					size++;
				}
			}
			++sizeIterator;
		}
		std::cout << size << std::endl;

		utils::LCInnerParticleIterator innerIterator = container.beginInner(
				outerIterator);
		for (int j = 0; j < size; j++) {
			++innerIterator;
		}
		++innerIterator;
		CPPUNIT_ASSERT((*innerIterator) == (*(container.endInner(i))));
	}
}

CppUnit::Test *LCParticleContainerTest::suite() {

	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"LCParticleContainerTest");

	testSuite->addTest(
			new CppUnit::TestCaller<LCParticleContainerTest>(
					"testInitializeCells",
					&LCParticleContainerTest::testInitializeCells));
	testSuite->addTest(
			new CppUnit::TestCaller<LCParticleContainerTest>("testUpdateCells",
					&LCParticleContainerTest::testUpdateCells));
	testSuite->addTest(
			new CppUnit::TestCaller<LCParticleContainerTest>("testSize",
					&LCParticleContainerTest::testSize));
	testSuite->addTest(
			new CppUnit::TestCaller<LCParticleContainerTest>("testBeginOuter",
					&LCParticleContainerTest::testBeginOuter));
	testSuite->addTest(
			new CppUnit::TestCaller<LCParticleContainerTest>("testEndOuter",
					&LCParticleContainerTest::testEndOuter));
	testSuite->addTest(
			new CppUnit::TestCaller<LCParticleContainerTest>("testBeginInner",
					&LCParticleContainerTest::testBeginInner));
	testSuite->addTest(
			new CppUnit::TestCaller<LCParticleContainerTest>("testEndInner",
					&LCParticleContainerTest::testEndInner));

	return testSuite;
}
