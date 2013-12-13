/*
 * ParticleGenerator.cpp
 *
 *  Created on: 13.11.2013
 *      Author: Son
 */

#include "ParticleGenerator.h"
#include "FileReader.h"

#include "Cuboid.h"
#include "InputSpheres.h"
#include "InputCuboids.h"
#include "InputParticles.h"
#include "InputSetting.h"

#include <memory>
#include <string>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::xml;
using namespace utils;
using namespace std;

log4cxx::LoggerPtr particlegeneratorlogger(log4cxx::Logger::getLogger("utils.particlegenerator"));

ParticleGenerator::ParticleGenerator() {
	//LOG4CXX_INFO(particlegeneratorlogger,"Constructed.");
}

ParticleGenerator::ParticleGenerator(std::list<Cuboid>& cubList){
	LOG4CXX_INFO(particlegeneratorlogger,"Constructed with CuboidList.");
	cuboidList = cubList;
}

ParticleGenerator::ParticleGenerator(std::list<Particle>& parList){
	particleList = parList;
}

ParticleGenerator::ParticleGenerator(std::list<Sphere>& sphList){
	sphereList = sphList;
}

ParticleGenerator::~ParticleGenerator() {
	LOG4CXX_INFO(particlegeneratorlogger,"Destructed.");
}

void ParticleGenerator::mergeWithParticleList(std::list<Particle>& before){
	for (std::list<Particle>::iterator it = particleList.begin(); it!=particleList.end(); it++){
		before.push_back(*it);
	}
}

void ParticleGenerator::readCuboids(char* filename){
	FileReader fileReader;
	LOG4CXX_INFO(particlegeneratorlogger,"Reading Cuboids.");
	fileReader.readFileCub(cuboidList, filename);
}

void ParticleGenerator::cuboidsToList() {
	std::list<Cuboid>::iterator iterator;
	LOG4CXX_INFO(particlegeneratorlogger,"Doing cuboidsToList.");
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

void ParticleGenerator::spheresToList() {
	std::list<Sphere>::iterator iterator;
	particleList.clear();
	for (iterator = sphereList.begin(); iterator != sphereList.end(); iterator++) {
		Sphere& temp = *iterator;
		std::list<Particle>::iterator iterator1;
		for (iterator1 = temp.getSphere().begin();
				iterator1 != temp.getSphere().end(); iterator1++) {
			Particle& tempP = *iterator1;
			particleList.push_back(tempP);
		}
	}
}

std::list<Cuboid>& ParticleGenerator::getCuboidList(){
	LOG4CXX_INFO(particlegeneratorlogger,"Returning cuboid list.");
	return cuboidList;
}

std::list<Sphere>& ParticleGenerator::getSphereList(){
	return sphereList;
}

std::list<Particle>& ParticleGenerator::getParticleList(){
	LOG4CXX_INFO(particlegeneratorlogger,"Returning particle list.");
	return particleList;
}

void ParticleGenerator::extractCuboids(const string filename)
{
  	try
  	{
		cuboidList.clear();
		auto_ptr<cuboids_t> h (cuboids (filename, xml_schema::flags::dont_validate));
		double mesh = h->meshWidth();
		double m = h->mass();
		double meanV = h->meanV();
	
		cuboids_t::cuboid_const_iterator i;
	    	for (i = h->cuboid().begin(); i != h->cuboid().end(); ++i){
				double a[] = {i->originVector().oriX(), i->originVector().oriY(), i->originVector().oriZ()};
				utils::Vector<double, 3> ori(a);
				double b[] = {i->startVelocity().velX(), i->startVelocity().velY(), i->startVelocity().velZ()};
				utils::Vector<double, 3> vel(b);
				int hei = i->size3D().height();
				int w = i->size3D().width();
				int d = i->size3D().depth();
				double typeC = i->parTypeC();

				Cuboid c(hei, w, d, mesh, m, ori, vel, meanV, typeC);
				cuboidList.push_back(c);
	    	}
	
  	}
  	catch (const xml_schema::exception& e)
  	{
	    	cerr << e << endl;
	    	exit(-1);
  	}
}

void ParticleGenerator::extractSpheres(const string filename){
	try
  	{
		sphereList.clear();
		auto_ptr<spheres_t> h (spheres (filename, xml_schema::flags::dont_validate));
		double mesh = h->meshWidthS();
		double m = h->massS();
		double meanV = h->meanVS();
	
		spheres_t::sphere_const_iterator i;
	    	for (i = h->sphere().begin(); i != h->sphere().end(); ++i){
				double a[] = {i->centerPos().x(), i->centerPos().y(), i->centerPos().z()};
				utils::Vector<double, 3> centerP(a);
				double b[] = {i->startVel().vX(), i->startVel().vY(), i->startVel().vZ()};
				utils::Vector<double, 3> vel(b);
				int radiuss = i->radiussph();
				double typeS = i->parTypeS();

				Sphere s(centerP, vel, meanV, m, radiuss, mesh, typeS);
				sphereList.push_back(s);
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
		particleList.clear();
		auto_ptr<particles_t> h (particles (filename, xml_schema::flags::dont_validate));
		particles_t::particle_const_iterator i;
	    	for (i = h->particle().begin (); i != h->particle().end(); ++i){
				double a[] = {i->position().x(), i->position().y(), i->position().z()};
				utils::Vector<double, 3> pos(a);
				double b[] = {i->velocity().x(), i->velocity().y(), i->velocity().z()};
				utils::Vector<double, 3> vel(b);
				double m = i->mass();
				double typeP = i->parTypeP();

				Particle p(pos, vel, m, typeP);
				particleList.push_back(p);
	    	}
	
  	}
  	catch (const xml_schema::exception& e)
  	{
	    	cerr << e << endl;
	    	exit(-1);
  	}
}

void ParticleGenerator::extractSetting(double& start_time, double& end_time, 
				double& delta_t, double& EPSILON, double& SIGMA,
				std::list<string>& inputNames, std::list<string>& inputTypes, 
				string& outputMask, int& outputFreq,
				utils::Vector<double, 3>& domainSize, double& r_cutoff,
				std::vector<int>& domainBoundCond, double& g_const, int& inputSize)
{
  	try
  	{
		auto_ptr<pse_t> h (pse ("InputSetting.xml", xml_schema::flags::dont_validate));
		start_time = h->start_time();
		end_time = h->t_end();
		delta_t = h->delta_t();
		inputSize = h->numberOfTypes();
		g_const = h->gconst();

		EPSILON = h->ljf().epsilon();
		SIGMA = h->ljf().sigma();

		inputNames.clear();
		inputTypes.clear();
		pse_t::inputfile_const_iterator it;
		for (it = h->inputfile().begin(); it != h->inputfile().end(); ++it){
			inputNames.push_back(it->name());
			inputTypes.push_back(it->type());
		}
	
		domainBoundCond.resize(6, 1);
		lc_t::condition_const_iterator ct;
		int i = 0;
		// 0 left, 1 right, 2 upper, 3 ground, 4 front, 5 behind
		for (ct = h->lc().condition().begin(); ct != h->lc().condition().end(); ct++){
			domainBoundCond[i] = *ct;
			i++;
		}

		outputMask = h->outputfile().name();
		outputFreq = h->outputfile().freq();

		double d[3] = {h->lc().domainsize().domainX(), h->lc().domainsize().domainY(), h->lc().domainsize().domainZ()};
		domainSize = utils::Vector<double, 3> (d);

		r_cutoff = h->lc().rcutoff();
  	}
  	catch (const xml_schema::exception& e)
  	{
		cerr << e << endl;
		exit(-1);
  	}
}
