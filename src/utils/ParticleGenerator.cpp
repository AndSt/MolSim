/*
 * ParticleGenerator.cpp
 *
 *  Created on: 13.11.2013
 *      Author: Son
 */

#include "ParticleGenerator.h"
#include "FileReader.h"

ParticleGenerator::ParticleGenerator() {
}

ParticleGenerator::ParticleGenerator(std::list<Cuboid> cubList){
		cuboids = cubList;
}

ParticleGenerator::~ParticleGenerator() {
}

void ParticleGenerator::readCuboids(char* filename){
	FileReader fileReader;
	fileReader.readFileCub(cuboids, filename);
}

void ParticleGenerator::cuboidsToList(std::list<Particle>& list) {
	std::list<Cuboid>::iterator iterator;
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
	return cuboids;
}
