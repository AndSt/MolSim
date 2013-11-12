/*
 * List.cpp
 *
 *  Created on: 12.11.2013
 *      Author: Son
 */

#include "List.h"
#include "FileReader.h"
#include "ParticleIterator.h"

#include<list>

List::List() {
}

List::List(const std::list<Particle>& particles_arg){
	particles = particles_arg;
}

List::~List() {
}

ParticleIterator List::begin(){
	return particles.begin();
}

ParticleIterator List::end(){
	return particles.end();
}

std::list<Particle>& List::getList(){
	return particles;
}


int List::size(){
	return particles.size();
}
