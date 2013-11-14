/*
 * ParticleGenerator.cpp
 *
 *  Created on: 13.11.2013
 *      Author: Son
 */

#include "ParticleGenerator.h"
#include "FileReader.h"
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace utils;

log4cxx::LoggerPtr particlegeneratorlogger(log4cxx::Logger::getLogger("ParticleGenerator"));

ParticleGenerator::ParticleGenerator() {
	LOG4CXX_INFO(particlegeneratorlogger,"Constructed.");
}

ParticleGenerator::ParticleGenerator(std::list<Cuboid> cubList){
	LOG4CXX_INFO(particlegeneratorlogger,"Constructed with ParticleList.");
		cuboids = cubList;
}

ParticleGenerator::~ParticleGenerator() {
	LOG4CXX_INFO(particlegeneratorlogger,"Destructed.");
}

void ParticleGenerator::readCuboids(char* filename){
	FileReader fileReader;
	LOG4CXX_INFO(particlegeneratorlogger,"Reading Cuboids.");
	fileReader.readFileCub(cuboids, filename);
}

void ParticleGenerator::cuboidsToList(std::list<Particle>& list) {
	std::list<Cuboid>::iterator iterator;
	LOG4CXX_INFO(particlegeneratorlogger,"Doing cuboidsToList.");
	for (iterator = cuboids.begin(); iterator != cuboids.end(); iterator++) {
		Cuboid& temp = *iterator;
		std::list<Particle>::iterator iterator1;
		for (iterator1 = temp.getCuboid().begin();
				iterator1 != temp.getCuboid().end(); iterator1++) {
			Particle& tempP = *iterator1;
			list.push_back(tempP);
		}
	}
}

std::list<Cuboid>& ParticleGenerator::getCuboids(){
	LOG4CXX_INFO(particlegeneratorlogger,"Returning cuboids.");
	return cuboids;
}
