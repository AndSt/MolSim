/*
 * ParticleGeneratorTest.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: andal
 */

#include "ParticleGeneratorTest.h"
#include <iostream>
#include <string>

ParticleGeneratorTest::ParticleGeneratorTest() {

}

ParticleGeneratorTest::~ParticleGeneratorTest() {
	// TODO Auto-generated destructor stub
}

void ParticleGeneratorTest::setUp() {
	//Set up cuboid1
	utils::Vector<double, 3> oriXYZ(0.0);
	utils::Vector<double, 3> startVel(0.0);
	cuboid1 = Cuboid(8, 40, 1, 1.1225, 1, oriXYZ, startVel, 0.1);

	//Set up cuboid2
	double args[3] = { 15.0, 15.0, 0.0 };
	oriXYZ = utils::Vector<double, 3>(args);
	double argz[3] = { 0.0, -10.0, 0.0 };
	startVel = utils::Vector<double, 3>(argz);
	cuboid2 = Cuboid(8, 8, 1, 1.1225, 1, oriXYZ, startVel, 0.1);

	//set up the particle generator
	std::string fileName = "src/tests/testFiles/generator.txt";
	char *cstr = new char[fileName.length() + 1];
	strcpy(cstr, fileName.c_str());
	generator.readCuboids(cstr);

	/*FOR TESTEXTRACTPARTICLES*/
	//Set up par1
	double dataX1[3] = {0.0, 0.0, 0.0};
	double dataV1[3] = {0.0, 0.0, 0.0};
	utils::Vector<double, 3> x1(dataX1);
	utils::Vector<double, 3> v1(dataV1); 
	Particle par1(x1, v1, 1.0, 0);

	//Set up par2
	double dataX2[3] = {0.0, 1.0, 0.0};
	double dataV2[3] = {-1.0, 0.0, 0.0};
	utils::Vector<double, 3> x2(dataX2);
	utils::Vector<double, 3> v2(dataV2); 
	Particle par2(x2, v2, 3.0e-6, 0);

	//Set up par3
	double dataX3[3] = {0.0, 5.36, 0.0};
	double dataV3[3] = {-0.425, 0.0, 0.0};
	utils::Vector<double, 3> x3(dataX3);
	utils::Vector<double, 3> v3(dataV3); 
	Particle par3(x3, v3, 9.55e-4, 0);

	//Set up par4
	double dataX4[3] = {34.75, 0.0, 0.0};
	double dataV4[3] = {0.0, 0.0296, 0.0};
	utils::Vector<double, 3> x4(dataX4);
	utils::Vector<double, 3> v4(dataV4); 
	Particle par4(x4, v4, 1.0e-14, 0);

	//Set up particles
	particles.clear();
	particles.push_back(par1);
	particles.push_back(par2);
	particles.push_back(par3);
	particles.push_back(par4);

	/*FOR TESTEXTRACTSETTING*/
	start_time = 0.0;
 	end_time = 5.0;
	delta_t = 0.0002;
	EPSILON = 5.0;
	SIGMA = 1.0;
	inputNames.clear();
	inputNames.push_back("InputCuboids.xml"); 
	inputTypes.clear();
	inputTypes.push_back("cuboids");
	outputMask = "MolSimVTK";
	outputFreq = 10;

	double d[3] = {180.0, 90.0, 0.0};
	domainSize = utils::Vector<double, 3> (d);

	rcutoff = 3.0;
}

void ParticleGeneratorTest::tearDown() {

}

void ParticleGeneratorTest::testReadCuboids() {

	//Check first cuboid
	Cuboid testCuboid = *generator.getCuboidList().begin();
	CPPUNIT_ASSERT(cuboid1.getDepth() == testCuboid.getDepth());
	CPPUNIT_ASSERT(cuboid1.getHeight() == testCuboid.getHeight());
	CPPUNIT_ASSERT(cuboid1.getWidth() == testCuboid.getWidth());
	CPPUNIT_ASSERT(cuboid1.getMass() == testCuboid.getMass());
	CPPUNIT_ASSERT(cuboid1.getDistance() == testCuboid.getDistance());
	CPPUNIT_ASSERT(cuboid1.getOrigin() == testCuboid.getOrigin());
	CPPUNIT_ASSERT(cuboid1.getStartV() == testCuboid.getStartV());
	CPPUNIT_ASSERT(cuboid1.getMeanV() == testCuboid.getMeanV());

	//Check second cuboid
	testCuboid = *(++generator.getCuboidList().begin());
	CPPUNIT_ASSERT(cuboid2.getDepth() == testCuboid.getDepth());
	CPPUNIT_ASSERT(cuboid2.getHeight() == testCuboid.getHeight());
	CPPUNIT_ASSERT(cuboid2.getWidth() == testCuboid.getWidth());
	CPPUNIT_ASSERT(cuboid2.getMass() == testCuboid.getMass());
	CPPUNIT_ASSERT(cuboid2.getDistance() == testCuboid.getDistance());
	CPPUNIT_ASSERT(cuboid2.getOrigin() == testCuboid.getOrigin());
	CPPUNIT_ASSERT(cuboid2.getStartV() == testCuboid.getStartV());
	CPPUNIT_ASSERT(cuboid2.getMeanV() == testCuboid.getMeanV());
}

void ParticleGeneratorTest::testExtractCuboids(){
	
	generator.extractCuboids("InputCuboids.xml");
	
	this->testReadCuboids();
}


void ParticleGeneratorTest::testExtractSpheres(){
	
	generator.extractSpheres("InputSpheres.xml");
	Sphere sp = *generator.getSphereList().begin();
	double rDouble = sp.getRadius() * sp.getMeshWidth();
	utils::Vector<double, 3> cen = sp.getCenter();
	generator.spheresToList();
	std::list<Particle> parList = generator.getParticleList();

	for (std::list<Particle>::iterator it = parList.begin(); it != parList.end(); it++){
		Particle p = *it;		
		CPPUNIT_ASSERT(pow(p.getX()[0]-cen[0],2) + pow(p.getX()[1]-cen[1],2) + pow(p.getX()[2]-cen[2],2) <= pow(15*1.1225,2));
	}
	
	CPPUNIT_ASSERT(sp.getCenter()[0]==60);
	CPPUNIT_ASSERT(sp.getCenter()[1]==25);
	CPPUNIT_ASSERT(sp.getCenter()[2]==0);
	CPPUNIT_ASSERT(sp.getRadius()==15);
	CPPUNIT_ASSERT(sp.getStartV()[0]==0);
	CPPUNIT_ASSERT(sp.getStartV()[1]==-10);
	CPPUNIT_ASSERT(sp.getStartV()[2]==0);
	
}
	
void ParticleGeneratorTest::testExtractParticles(){
	generator.extractParticles("InputParticles.xml");
	std::list<Particle>::iterator iterator = particles.begin();
	std::list<Particle>::iterator testIterator;
	for (testIterator = generator.getParticleList().begin(); testIterator != generator.getParticleList().end(); ++testIterator){
		Particle par = *iterator;		
		Particle testPar = *testIterator;
		CPPUNIT_ASSERT(par.getX()==testPar.getX());
		CPPUNIT_ASSERT(par.getV()==testPar.getV());
		CPPUNIT_ASSERT(par.getM()==testPar.getM());
		CPPUNIT_ASSERT(par.getType()==testPar.getType());
		
		++iterator;
	}

}
	
void ParticleGeneratorTest::testExtractSetting(){
	double start_timeT, end_timeT, delta_tT, EPSILONT, SIGMAT; 
	std::list<std::string> inputNamesT, inputTypesT;
	string outputMaskT;
	int outputFreqT;
	utils::Vector<double, 3> domainSizeT;
	double rcutoffT;
	string cond;
	
	generator.extractSetting(start_timeT, end_timeT, delta_tT, EPSILONT, SIGMAT, inputNamesT, inputTypesT, outputMaskT, outputFreqT,
							domainSizeT, rcutoffT, cond);

	CPPUNIT_ASSERT(start_time==start_timeT);
	CPPUNIT_ASSERT(end_time==end_timeT);
	CPPUNIT_ASSERT(delta_t==delta_tT);
	CPPUNIT_ASSERT(EPSILON==EPSILONT);
	CPPUNIT_ASSERT(SIGMA==SIGMAT);

	list<string>::iterator itN = inputNamesT.begin();
	list<string>::iterator itT = inputTypesT.begin();
	CPPUNIT_ASSERT(*itN == "InputSpheres.xml");
	CPPUNIT_ASSERT(*itT == "spheres");
	CPPUNIT_ASSERT(cond == "reflecting");

	CPPUNIT_ASSERT(outputMask==outputMaskT);
	CPPUNIT_ASSERT(outputFreq==outputFreqT);
	CPPUNIT_ASSERT(domainSizeT==domainSizeT);
	CPPUNIT_ASSERT(rcutoff==rcutoffT);
}

CppUnit::Test *ParticleGeneratorTest::suite() {
	CppUnit::TestSuite *testSuite = new CppUnit::TestSuite(
			"ParticleGeneratorTest");
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleGeneratorTest>("testReadCuboids",
					&ParticleGeneratorTest::testReadCuboids));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleGeneratorTest>("testExtractCuboids",
					&ParticleGeneratorTest::testExtractCuboids));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleGeneratorTest>("testExtractParticles",
					&ParticleGeneratorTest::testExtractParticles));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleGeneratorTest>("testExtractSetting",
					&ParticleGeneratorTest::testExtractSetting));
	testSuite->addTest(
			new CppUnit::TestCaller<ParticleGeneratorTest>("testExtractSpheres",
					&ParticleGeneratorTest::testExtractSpheres));
	return testSuite;
}
