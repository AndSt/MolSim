/*
 * Cub.cpp
 *
 *  Created on: 10.11.2013
 *      Author: son
 */

#include <vector>
#include <Particle.h>

#include "Cuboid.h"
#include "utils/Vector.h"
#include "MaxwellBoltzmannDistribution.h"

Cuboid::Cuboid(){

}

Cuboid::Cuboid(int height, int width, int depth, double distance, double mass,
		utils::Vector<double, 3> ori, utils::Vector<double, 3> startVelocity,
		double meanVelocity, int parType, double EPSILON, double SIGMA) {
	// Initialize first variables
	cHeight = height;
	cWidth = width;
	cDepth = depth;
	origin = ori;
	h = distance;
	m = mass;
	startV = startVelocity;
	meanV = meanVelocity;
	this->parType = parType;
	this->EPSILON = EPSILON;
	this->SIGMA = SIGMA;

	// Initialize cub
	cub.clear();

	// Initialize particles in cub
	// Fills along Oz first, then Ox and Oy
	for (int hei = 0; hei < height; hei++) {
		for (int w = 0; w < width; w++) {
			for (int d = 0; d < depth; d++) {
				// Must set each particle with its own coordinate
				// Ox along width, Oy along height, Oz along depth
				double addTemp[] = { w * h, hei * h, d * h };
				utils::Vector<double, 3> addVector(addTemp);
				utils::Vector<double, 3> vel(ori + addVector);

				Particle p(vel, startVelocity, mass, parType, w + hei*width);

				// Movement of each particle superposed by Brownian Motion
				MaxwellBoltzmannDistribution(p, meanVelocity, 2);

				cub.push_back(p);
			}
		}
	}
}

/*
 Cuboid::Cuboid(int height, int width, int depth, double distance, double mass, utils::Vector<double, 3> ori, utils::Vector<double, 3> startVelocity, double meanVelocity){
 // Initialize first variables
 cHeight = height;
 cWidth = width;
 cDepth = depth;
 origin = ori;
 h = distance;
 m = mass;
 startV = startVelocity;
 meanV = meanVelocity;

 // Initialize cub
 cub.resize(height);
 for (int i = 0; i < height; i++) {
 cub[i].resize(width);

 for (int j = 0; j < width; j++)
 cub[i][j].resize(depth);
 }

 // Initialize particles in cub
 for (int hei = 0; hei < height; hei++){
 for (int w = 0; w < width; w++){
 for (int d = 0; d < depth; d++){
 cub[hei][w][d] = Particle();
 cub[hei][w][d].setM(mass);
 cub[hei][w][d].getV() = startVelocity;

 // Must set each particle with its own coordinate
 // Ox along width, Oy along height, Oz along depth
 double addTemp[] = {w*h, hei*h, d*h};
 utils::Vector<double, 3> addVector(addTemp);
 cub[hei][w][d].getX() = ori + addVector;

 // Movement of each particle superposed by Brownian Motion
 MaxwellBoltzmannDistribution(cub[hei][w][d], meanVelocity, 3);
 }
 }
 }
 }
 */

Particle& Cuboid::getParticleAtID(Particle& pNull, int id){
	//id starts from 0
	if ((id < 0) || (id >= cub.size()))
		return pNull;

	for (std::list<Particle>::iterator it = cub.begin();
			it != cub.end(); it++){
		if ((*it).getID() == id)
			return *it;
	}

	return pNull;
}

void Cuboid::initNeighbors(){
	//works for 2D membranes
	for (std::list<Particle>::iterator it = cub.begin();
			it != cub.end(); it++){
		Particle& p = *it;
		int id = p.getID();
		bool isFirst = ((id % cWidth) == 0);
		bool isLast = (((id + 1) % cWidth) == 0);
		p.getDirectNeighbors().clear();
		p.getDiagNeighbors().clear();

		utils::Vector<double, 3> xi((double) 0);
		utils::Vector<double, 3> vi((double) 0);
		Particle pNull(xi, vi, 0.0, 0, -1);

		//direct under
		if (this->getParticleAtID(pNull, id - cWidth).getID() != -1)
			p.getDirectNeighbors().push_back(this->getParticleAtID(pNull, id - cWidth));

		//direct left
		if (this->getParticleAtID(pNull, isFirst ? (-1) : (id - 1)).getID() != -1)
			p.getDirectNeighbors().push_back(this->getParticleAtID(pNull,
					isFirst ? (-1) : (id - 1))); //cares for the first of each line

		//direct right
		if (this->getParticleAtID(pNull, isLast ? (-1) : (id + 1)).getID() != -1)
			p.getDirectNeighbors().push_back(this->getParticleAtID(pNull,
					isLast ? (-1) : (id + 1))); //cares for the last of each line

		//direct above
		if (this->getParticleAtID(pNull, id + cWidth).getID() != -1)
			p.getDirectNeighbors().push_back(this->getParticleAtID(pNull, id + cWidth));

		/*
		//delete all the pNulls
		for (std::list<Particle>::iterator it = p.getDirectNeighbors().begin();
				it != p.getDirectNeighbors().end(); it++){
			if ((*it).getID() == -1)
				it = p.getDirectNeighbors().erase(it);
		}
		*/

		//diagonal lower left
		if (this->getParticleAtID(pNull, isFirst ? (-1) : (id - 1 - cWidth)).getID() != -1)
			p.getDiagNeighbors().push_back(this->getParticleAtID(pNull,
					isFirst ? (-1) : (id - 1 - cWidth))); //cares for the first of each line

		//diagonal lower right
		if (this->getParticleAtID(pNull, isLast ? (-1) : (id + 1 - cWidth)).getID() != -1)
			p.getDiagNeighbors().push_back(this->getParticleAtID(pNull,
					isLast ? (-1) : (id + 1 - cWidth))); //cares for the last of each line

		//diagonal upper left
		if (this->getParticleAtID(pNull, isFirst ? (-1) : (id - 1 + cWidth)).getID() != -1)
			p.getDiagNeighbors().push_back(this->getParticleAtID(pNull,
					isFirst ? (-1) : (id - 1 + cWidth))); //cares for the first of each line

		//diagonal upper right
		if (this->getParticleAtID(pNull, isLast ? (-1) : (id + 1 + cWidth)).getID() != -1)
			p.getDiagNeighbors().push_back(this->getParticleAtID(pNull,
					isLast ? (-1) : (id + 1 + cWidth))); //cares for the last of each line

		/*
		//delete all the pNulls
		for (std::list<Particle>::iterator it = p.getDiagNeighbors().begin();
				it != p.getDiagNeighbors().end(); it++){
			if ((*it).getID() == -1)
				it = p.getDiagNeighbors().erase(it);
		}
		*/
	}
}

utils::Vector<double, 3>& Cuboid::getOrigin() {
	return origin;
}

utils::Vector<double, 3>& Cuboid::getStartV() {
	return startV;
}

std::list<Particle>& Cuboid::getCuboid() {
	return cub;
}

int Cuboid::getHeight() {
	return cHeight;
}

void Cuboid::setHeight(double newH) {
	cHeight = newH;
}

int Cuboid::getWidth() {
	return cWidth;
}

void Cuboid::setWidth(double newW) {
	cWidth = newW;
}

int Cuboid::getDepth() {
	return cDepth;
}

void Cuboid::setDepth(double newD) {
	cDepth = newD;
}

double Cuboid::getDistance() {
	return h;
}

void Cuboid::setDistance(double newD) {
	h = newD;
}

double Cuboid::getMass() {
	return m;
}

void Cuboid::setMass(double newM) {
	m = newM;
}

double Cuboid::getMeanV() {
	return meanV;
}

void Cuboid::setMeanV(double newV) {
	meanV = newV;
}

int Cuboid::getSize() {
	return cHeight * cWidth * cDepth;
}

int& Cuboid::getType(){
	return parType;
}

double& Cuboid::getEpsilon(){
	return EPSILON;
}

double& Cuboid::getSigma(){
	return SIGMA;
}

Cuboid::~Cuboid() {
}
