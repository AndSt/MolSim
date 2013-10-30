/*
 * ParticleIterator.cpp
 *
 *  Created on: Oct 29, 2013
 *      Author: andal
 */

#include "ParticleIterator.h"

ParticleIterator::ParticleIterator(){

}

ParticleIterator::ParticleIterator(std::list<Particle>::iterator iterator_arg) {
	// TODO Auto-generated constructor stub
	iterator = iterator_arg;
}

ParticleIterator::~ParticleIterator() {
	// TODO Auto-generated destructor stub
}

Particle& ParticleIterator::operator*() const {
	return *iterator;
}

void ParticleIterator::operator++(){
	++iterator;
}

bool ParticleIterator::operator!=( const ParticleIterator b){
	return iterator != b.iterator;
}

