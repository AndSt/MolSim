/*
 * ParticleGenerator.cpp
 *
 *  Created on: 13.11.2013
 *      Author: Son
 */

#include "ParticleGenerator.h"
#include "FileReader.h"

#include "Cuboid.h"
#include "InputCuboids.h"
#include "InputParticles.h"
#include "InputSetting.h"

#include <memory>
#include <string>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace utils;
using namespace std;

//log4cxx::LoggerPtr particlegeneratorlogger(log4cxx::Logger::getLogger("ParticleGenerator"));

ParticleGenerator::ParticleGenerator() {
	//LOG4CXX_INFO(particlegeneratorlogger,"Constructed.");
}

ParticleGenerator::ParticleGenerator(std::list<Cuboid>& cubList){
	//LOG4CXX_INFO(particlegeneratorlogger,"Constructed with CuboidList.");
	cuboidList = cubList;
}

ParticleGenerator::ParticleGenerator(std::list<Particle>& parList){
	particleList = parList;
}

ParticleGenerator::~ParticleGenerator() {
	//LOG4CXX_INFO(particlegeneratorlogger,"Destructed.");
}

void ParticleGenerator::readCuboids(char* filename){
	FileReader fileReader;
	//LOG4CXX_INFO(particlegeneratorlogger,"Reading Cuboids.");
	fileReader.readFileCub(cuboidList, filename);
}

void ParticleGenerator::cuboidsToList() {
	std::list<Cuboid>::iterator iterator;
	//LOG4CXX_INFO(particlegeneratorlogger,"Doing cuboidsToList.");
	particleList.clear();
	for (iterator = cuboidList.begin(); iterator != cuboidList.end(); iterator++) {
		Cuboid& temp = *iterator;
		std::list<Particle>::iterator iterator1;
		for (iterator1 = temp.getCuboid().begin();
				iterator1 != temp.getCuboid().end(); iterator1++) {
			Particle& tempP = *iterator1;
			particleList.push_back(tempP);
		}
	}
}

std::list<Cuboid>& ParticleGenerator::getCuboidList(){
	//LOG4CXX_INFO(particlegeneratorlogger,"Returning cuboid list.");
	return cuboidList;
}

std::list<Particle>& ParticleGenerator::getParticleList(){
	//LOG4CXX_INFO(particlegeneratorlogger,"Returning particle list.");
	return particleList;
}

void ParticleGenerator::extractCuboids(const string filename)
{
  try
  {
	auto_ptr<cuboids_t> h (cuboids (filename, xml_schema::flags::dont_validate));
	cuboids_t::cuboid_const_iterator i;
    	for (i = h->cuboid().begin (); i != h->cuboid().end(); ++i)
    	{		
		double a[] = {i->originVector().oriX(), i->originVector().oriY(), i->originVector().oriZ()};
		utils::Vector<double, 3> ori(a);
		double b[] = {i->startVelocity().velX(), i->startVelocity().velY(), i->startVelocity().velZ()};
		utils::Vector<double, 3> vel(b);
		int hei = i->size3D().height();
		int w = i->size3D().width();
		int d = i->size3D().depth();
		int mesh = h->meshWidth();
		double m = h->mass();
		double meanV = h->meanV();

      		Cuboid c(hei, w, d, mesh, m, ori, vel, meanV);
		cuboidList.push_back(c);
    	}
	
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    exit(-1);
  }
}

void ParticleGenerator::extractParticles(const string filename)
{
  try
  {
	auto_ptr<particles_t> h (particles (filename, xml_schema::flags::dont_validate));
	particles_t::particle_const_iterator i;
    	for (i = h->particle().begin (); i != h->particle().end(); ++i)
    	{		
		double a[] = {i->position().x(), i->position().y(), i->position().z()};
		utils::Vector<double, 3> pos(a);
		double b[] = {i->velocity().x(), i->velocity().y(), i->velocity().z()};
		utils::Vector<double, 3> vel(b);
		double m = i->mass();

      		Particle p(pos, vel, m, 1);
		particleList.push_back(p);
    	}
	
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    exit(-1);
  }
}

void ParticleGenerator::extractSetting(double& start_time, double& end_time, double& delta_t, double& EPSILON, double& SIGMA, 
	string& inputName, string& inputType, string& outputMask, int& outputFreq)
{
  try
  {
	auto_ptr<pse_t> h (pse ("InputSetting.xml", xml_schema::flags::dont_validate));
	start_time = h->start_time();
	end_time = h->t_end();
	delta_t = h->delta_t();

	EPSILON = h->ljf().epsilon();
	SIGMA = h->ljf().sigma();

	inputName = h->inputfile().name();
	inputType = h->inputfile().type();

	outputMask = h->outputfile().name();
	outputFreq = h->outputfile().freq();
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    exit(-1);
  }
}
