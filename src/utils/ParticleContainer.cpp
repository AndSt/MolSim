/*
 * ParticleContainer.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: andal
 */

#include "ParticleContainer.h"

using namespace utils;

ParticleContainer::ParticleContainer() {
	// TODO Auto-generated constructor stub
}

ParticleContainer::~ParticleContainer() {
	// TODO Auto-generated destructor stub
}

void ParticleContainer::initialize(std::list<Particle>& particles_arg) {
	particles = particles_arg;
}

ParticleIterator ParticleContainer::begin() {
	return ParticleIterator(particles.begin());
}

ParticleIterator ParticleContainer::end() {
	return ParticleIterator(particles.end());
}

std::list<Particle>& ParticleContainer::getList() {
	return particles;
}

int ParticleContainer::size() {
	return particles.size();
}
