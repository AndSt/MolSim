/*
 * LCInnerParticleIteratorTest.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: andal
 */

#include "LCInnerParticleIteratorTest.h"

LCInnerParticleIteratorTest::LCInnerParticleIteratorTest() {
	// TODO Auto-generated constructor stub

}

LCInnerParticleIteratorTest::~LCInnerParticleIteratorTest() {
	// TODO Auto-generated destructor stub
}

void LCInnerParticleIteratorTest::setUp() {
	FileReader fileReader;
	std::string fileName = "src/tests/testFiles/innerParticleIteratorTest.txt";
	char *cstr = new char[fileName.length() + 1];
	strcpy(cstr, fileName.c_str());
	utils::ParticleGenerator pgen;
	pgen.readCuboids(cstr);
	pgen.cuboidsToList();
	particles = pgen.getParticleList();
	//initialize container
	CPPUNIT_ASSERT(particles.empty() == false);
	cutoff_radius = 3.0;
	double domain_size_arg[3] = { 50, 20, 0 };
	domain_size = utils::Vector<double, 3>(domain_size_arg);

	width = domain_size[0] / cutoff_radius;
	height = domain_size[1] / cutoff_radius;
	depth = domain_size[2] / cutoff_radius;
	num_of_cells = width * height * 1;

	container.initialize(particles, domain_size, cutoff_radius);

}

void LCInnerParticleIteratorTest::tearDown() {

}

void LCInnerParticleIteratorTest::testParticleReference() {
	//setUp Variables
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator iterator1 = container.beginInner(iterator);
	utils::LCInnerParticleIterator iterator2 = container.beginInner(iterator);
	++iterator;
	utils::LCInnerParticleIterator iterator3 = container.beginInner(iterator);

	CPPUNIT_ASSERT((*iterator1) == (*iterator2));
	CPPUNIT_ASSERT(!((*iterator1) == (*iterator3)));
	std::cout << "testParticleReference" << std::endl;
}

void LCInnerParticleIteratorTest::testAssignment() {
	//setUp Variables
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator iterator1 = container.beginInner(iterator);
	utils::LCInnerParticleIterator iterator2 = container.beginInner(iterator);
	++iterator;
	utils::LCInnerParticleIterator iterator3 = container.beginInner(iterator);

	CPPUNIT_ASSERT((*iterator1) == (*iterator2));
	CPPUNIT_ASSERT(!((*iterator1) == (*iterator3)));

	std::cout << "testAssignment" << std::endl;
}

void LCInnerParticleIteratorTest::testInequality() {
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator iterator1 = container.beginInner(iterator);
	utils::LCInnerParticleIterator iterator2 = container.beginInner(iterator);
	++iterator;
	utils::LCInnerParticleIterator iterator3 = container.beginInner(iterator);

	CPPUNIT_ASSERT(!(iterator1 != iterator2));
	CPPUNIT_ASSERT(iterator1 != iterator3);

	std::cout << "testInequality" << std::endl;
}

void LCInnerParticleIteratorTest::testGetCellNumber() {

	//walk over all particles in domain and check if it returnes the truth
	//for all cells, which aren't empty

	utils::LCOuterParticleIterator outerIterator = container.beginOuter();
	while (outerIterator != container.endOuter()) {
		utils::LCInnerParticleIterator innerIterator = container.beginInner(
				outerIterator);
		Particle &p = *innerIterator;
		if (p.getX()[0] <= domain_size[0] && p.getX()[1] <= domain_size[1]
				&& p.getX()[2] <= domain_size[2]) {
			int i = (int) (p.getX()[0] / cutoff_radius)
					+ ((int) (p.getX()[1] / cutoff_radius)) * width
					+ ((int) (p.getX()[2] / cutoff_radius)) * width * height;
			CPPUNIT_ASSERT(i == innerIterator.getCellNumber());
		}
		++outerIterator;
	}

	std::cout << "testGetCellNumber" << std::endl;
}

void LCInnerParticleIteratorTest::testCheckLeft() {

	//the input is a cuboid, so (*iterator) should have no left side
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator testIterator1 = container.beginInner(
			iterator);
	CPPUNIT_ASSERT(testIterator1.checkLeft() == false);

	//the input is a cuboid, so (*iterator) should a left side
	int i = iterator.getCellNumber();
	while(iterator.getCellNumber() <= i){
		++iterator;
	}
	utils::LCInnerParticleIterator testIterator2 = container.beginInner(
				iterator);
	CPPUNIT_ASSERT(testIterator2.checkLeft() == true);

	//in (i+width), which is the first cell in the next line, should be no
	//left side
	utils::LCInnerParticleIterator testIterator3 = container.beginInner(
					iterator);
	while(iterator.getCellNumber() < (i+width)){
			++iterator;
		}
	CPPUNIT_ASSERT(i + width == testIterator3.getCellNumber());
	CPPUNIT_ASSERT(testIterator3.checkLeft() == false);
	std::cout << "testCheckLeft" << std::endl;
}

void LCInnerParticleIteratorTest::testCheckRight() {

	//the input is a cuboid, so (*iterator) should have a right side
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator testIterator1 = container.beginInner(
			iterator);
	CPPUNIT_ASSERT(testIterator1.checkRight() == true);

	//the input is a cuboid, so (*iterator) should have a right side
	int i = iterator.getCellNumber();
	while(iterator.getCellNumber() <= i){
		++iterator;
	}
	utils::LCInnerParticleIterator testIterator2 = container.beginInner(
				iterator);
	CPPUNIT_ASSERT(testIterator2.checkRight() == true);

	//in (i+width-1), which is the last cell in the first line, should be no
	//right side
	utils::LCInnerParticleIterator testIterator3 = container.beginInner(
					iterator);
	while(iterator.getCellNumber() < (i+width-1)){
			++iterator;
		}

	CPPUNIT_ASSERT(testIterator3.checkRight() == false);
	std::cout << "testCheckRight" << std::endl;
}

void LCInnerParticleIteratorTest::testCheckBottom() {

	//the input is a cuboid who has particles in all cells, so there
	//should be bottom cell
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator testIterator1 = container.beginInner(
			iterator);
	CPPUNIT_ASSERT(testIterator1.checkBottom() == false);

	//the input is a cuboid, so (*iterator) should have a right side
	int i = iterator.getCellNumber();
	while(iterator.getCellNumber() <= i){
		++iterator;
	}
	utils::LCInnerParticleIterator testIterator2 = container.beginInner(
				iterator);
	CPPUNIT_ASSERT(testIterator2.checkBottom() == false);

	//in (i+width-1), which is the last cell in the first line, should be no
	//right side
	utils::LCInnerParticleIterator testIterator3 = container.beginInner(
					iterator);
	while(iterator.getCellNumber() < (i+width-1)){
			++iterator;
		}

	CPPUNIT_ASSERT(testIterator3.checkBottom() == true);
	std::cout << "testCheckBottom" << std::endl;
}

void LCInnerParticleIteratorTest::testCheckTop() {

	//the input is a cuboid who has particles in all cells, so there
	//should be bottom cell
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator testIterator1 = container.beginInner(
			iterator);
	CPPUNIT_ASSERT(testIterator1.checkTop() == true);

	//it should have a cell above it
	int i = iterator.getCellNumber();
	while(iterator.getCellNumber() <= i){
		++iterator;
	}
	utils::LCInnerParticleIterator testIterator2 = container.beginInner(
				iterator);
	CPPUNIT_ASSERT(testIterator2.checkTop() == true);

	//in (i+(width*(height-1))), which is the last line of cells on the front
	//layer
	utils::LCInnerParticleIterator testIterator3 = container.beginInner(
					iterator);
	while(iterator.getCellNumber() < (i+(width*(height-1)))){
			++iterator;
		}

	CPPUNIT_ASSERT(testIterator3.checkTop() == false);
	std::cout << "testCheckTop" << std::endl;
}

void LCInnerParticleIteratorTest::testCheckBack() {

	//all should fail, because of z-dimension 0
	utils::LCOuterParticleIterator iterator = container.beginOuter();
	utils::LCInnerParticleIterator testIterator1 = container.beginInner(
			iterator);
	CPPUNIT_ASSERT(testIterator1.checkBack() == false);

	int i = iterator.getCellNumber();
	while(iterator.getCellNumber() <= i){
		++iterator;
	}
	utils::LCInnerParticleIterator testIterator2 = container.beginInner(
				iterator);
	CPPUNIT_ASSERT(testIterator2.checkTop() == false);


	utils::LCInnerParticleIterator testIterator3 = container.beginInner(
					iterator);
	while(iterator.getCellNumber() < (i+(width*(height-1)))){
			++iterator;
		}

	CPPUNIT_ASSERT(testIterator3.checkTop() == false);
	std::cout << "testCheckBack" << std::endl;
}

void LCInnerParticleIteratorTest::testIteration(){

	utils::LCOuterParticleIterator firstOuter = container.beginOuter();
	utils::LCInnerParticleIterator iterator = container.beginInner(firstOuter);
	++iterator;
	++firstOuter;
	//every cell has particles, so this has to be true
	CPPUNIT_ASSERT((*iterator) == (*firstOuter));
	++firstOuter;
	CPPUNIT_ASSERT(!((*iterator) == (*firstOuter)));

}

CppUnit::Test *LCInnerParticleIteratorTest::suite() {

	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"LCInnerParticleIteratorTest");

	testSuite->addTest(
			new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
					"testParticleReference",
					&LCInnerParticleIteratorTest::testParticleReference));
	testSuite->addTest(
			new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
					"testAssignment",
					&LCInnerParticleIteratorTest::testAssignment));
	testSuite->addTest(
			new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
					"testInequality",
					&LCInnerParticleIteratorTest::testInequality));
	testSuite->addTest(
			new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
					"testGetCellNumber",
					&LCInnerParticleIteratorTest::testGetCellNumber));
	testSuite->addTest(
				new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
						"testCheckLeft",
						&LCInnerParticleIteratorTest::testCheckLeft));
	testSuite->addTest(
				new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
						"testCheckRight",
						&LCInnerParticleIteratorTest::testCheckRight));
	testSuite->addTest(
				new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
						"testCheckBottom",
						&LCInnerParticleIteratorTest::testCheckBottom));
	testSuite->addTest(
				new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
						"testCheckTop",
						&LCInnerParticleIteratorTest::testCheckTop));
	testSuite->addTest(
				new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
						"testCheckTop",
						&LCInnerParticleIteratorTest::testCheckBack));
	testSuite->addTest(
				new CppUnit::TestCaller<LCInnerParticleIteratorTest>(
						"testIteration",
						&LCInnerParticleIteratorTest::testIteration));


	return testSuite;
}
