/*
 * ParticleGeneratorTest.cpp
 *
 *  Created on: Nov 13, 2013
 *      Author: andal
 */

#include "ParticleGeneratorTest.h"

#include <iostream>
#include <string>
#include <vector>

ParticleGeneratorTest::ParticleGeneratorTest() {

}

ParticleGeneratorTest::~ParticleGeneratorTest() {
	// TODO Auto-generated destructor stub
}

void ParticleGeneratorTest::setUp() {
	//Set up cuboid1
	utils::Vector<double, 3> oriXYZ(0.0);
	utils::Vector<double, 3> startVel(0.0);
	cuboid1 = Cuboid(8, 40, 1, 1.1225, 1, oriXYZ, startVel, 0.1, 0, 5.0, 1.0);

	//Set up cuboid2
	double args[3] = { 15.0, 15.0, 0.0 };
	oriXYZ = utils::Vector<double, 3>(args);
	double argz[3] = { 0.0, -10.0, 0.0 };
	startVel = utils::Vector<double, 3>(argz);
	cuboid2 = Cuboid(8, 8, 1, 1.1225, 1, oriXYZ, startVel, 0.1, 1, 5.0, 1.0);

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
 	end_time = 20.0;
	delta_t = 0.0005;
	inputSize = 2;
	g = -12.44;
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
	CPPUNIT_ASSERT(cuboid1.getType() == testCuboid.getType());
	CPPUNIT_ASSERT(cuboid1.getEpsilon() == testCuboid.getEpsilon());
	CPPUNIT_ASSERT(cuboid1.getSigma() == testCuboid.getSigma());

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
	CPPUNIT_ASSERT(cuboid2.getType() == testCuboid.getType());
	CPPUNIT_ASSERT(cuboid2.getEpsilon() == testCuboid.getEpsilon());
	CPPUNIT_ASSERT(cuboid2.getSigma() == testCuboid.getSigma());
}

void ParticleGeneratorTest::testExtractCuboids(){
	
	generator.extractCuboids("InputCuboids.xml");
	Cuboid testCuboid = *generator.getCuboidList().begin();
	CPPUNIT_ASSERT(testCuboid.getDepth()==1);
	CPPUNIT_ASSERT(testCuboid.getHeight()==20);
	CPPUNIT_ASSERT(testCuboid.getWidth()==100);
	CPPUNIT_ASSERT(testCuboid.getMass()==1);
	CPPUNIT_ASSERT(testCuboid.getDistance()==1.1225);
	double v[] = {20.0, 20.0, 0.0};
	utils::Vector<double,3> vv(v);
	CPPUNIT_ASSERT(testCuboid.getOrigin()==vv);
	double x[] = {0.0, 0.0, 0.0};
	vv = utils::Vector<double,3> (x);
	CPPUNIT_ASSERT(testCuboid.getStartV()==vv);
	CPPUNIT_ASSERT(testCuboid.getMeanV()==0.1);
	CPPUNIT_ASSERT(testCuboid.getType() == 0);
	CPPUNIT_ASSERT(testCuboid.getEpsilon() == 5.0);
	CPPUNIT_ASSERT(testCuboid.getSigma() == 1.0);

	//Check second cuboid
	testCuboid = *(++generator.getCuboidList().begin());
	CPPUNIT_ASSERT(testCuboid.getDepth()==1);
	CPPUNIT_ASSERT(testCuboid.getHeight()==20);
	CPPUNIT_ASSERT(testCuboid.getWidth()==20);
	CPPUNIT_ASSERT(testCuboid.getMass()==1);
	CPPUNIT_ASSERT(testCuboid.getDistance()==1.1225);
	double v1[] = {70.0, 60.0, 0.0};
	vv = utils::Vector<double,3>(v1);
	CPPUNIT_ASSERT(testCuboid.getOrigin()==vv);
	double x1[] = {0.0, -10.0, 0.0};
	vv = utils::Vector<double,3> (x1);
	CPPUNIT_ASSERT(testCuboid.getStartV()==vv);
	CPPUNIT_ASSERT(testCuboid.getMeanV()==0.1);
	CPPUNIT_ASSERT(testCuboid.getType() == 1);
	CPPUNIT_ASSERT(testCuboid.getEpsilon() == 5.0);
	CPPUNIT_ASSERT(testCuboid.getSigma() == 1.0);
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
		utils::Vector<double, 3> temp = p.getX() - cen;
		CPPUNIT_ASSERT(temp.L2Norm() - rDouble <= sp.getMeshWidth());
	}
	
	CPPUNIT_ASSERT(sp.getCenter()[0]==60);
	CPPUNIT_ASSERT(sp.getCenter()[1]==25);
	CPPUNIT_ASSERT(sp.getCenter()[2]==0);
	CPPUNIT_ASSERT(sp.getRadius()==15);
	CPPUNIT_ASSERT(sp.getStartV()[0]==0);
	CPPUNIT_ASSERT(sp.getStartV()[1]==-10);
	CPPUNIT_ASSERT(sp.getStartV()[2]==0);
	CPPUNIT_ASSERT(sp.getType()==0);
	CPPUNIT_ASSERT(sp.getEpsilon() == 5.0);
	CPPUNIT_ASSERT(sp.getSigma() == 1.0);
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
	double start_timeT, end_timeT, delta_tT;
	std::list<std::string> inputNamesT, inputTypesT;
	string outputMaskT;
	int outputFreqT;
	utils::Vector<double, 3> domainSizeT;
	double rcutoffT;
	std::vector<int> cond;
	double gT;
	int inputSizeT;
	
	string inputName = "InputSetting.xml";
	generator.extractSetting(inputName, start_timeT, end_timeT, delta_tT,
				inputNamesT, inputTypesT, outputMaskT,
				outputFreqT, domainSizeT, rcutoffT, cond, gT, inputSize);

	CPPUNIT_ASSERT(start_time==start_timeT);
	CPPUNIT_ASSERT(end_time==end_timeT);
	CPPUNIT_ASSERT(delta_t==delta_tT);
	CPPUNIT_ASSERT(g==gT);
	CPPUNIT_ASSERT(inputSize==inputSizeT);

	list<string>::iterator itN = inputNamesT.begin();
	list<string>::iterator itT = inputTypesT.begin();
	CPPUNIT_ASSERT(*itN == "InputCuboids.xml");
	CPPUNIT_ASSERT(*itT == "cuboids");

	CPPUNIT_ASSERT(cond[0] == 2);
	CPPUNIT_ASSERT(cond[1] == 2);
	CPPUNIT_ASSERT(cond[2] == 2);
	CPPUNIT_ASSERT(cond[3] == 2);
	CPPUNIT_ASSERT(cond[4] == 2);
	CPPUNIT_ASSERT(cond[5] == 2);

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
