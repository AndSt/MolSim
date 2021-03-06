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

Particle * Cuboid::getParticleAtID(int id){
	//id starts from 0
	if ((id < 0) || (id >= cub.size()))
		return NULL;

	for (std::list<Particle>::iterator it = cub.begin();
			it != cub.end(); it++){
		if ((*it).getID() == id)
			return &(*it);
	}

	return NULL;
}

void Cuboid::initNeighbors(){
	//works for 2D membranes
	Particle * pp = NULL;
	for (std::list<Particle>::iterator it = cub.begin();
			it != cub.end(); it++){
		Particle& p = *it;
		int id = p.getID();
		bool isFirst = ((id % cWidth) == 0);
		bool isLast = (((id + 1) % cWidth) == 0);
		p.getDirectNeighbors().clear();
		p.getDiagNeighbors().clear();

		//direct under
		pp = this->getParticleAtID(id - cWidth);
		if (pp != NULL)
			p.getDirectNeighbors().push_back(pp);

		//direct left
		pp = this->getParticleAtID(isFirst ? (-1) : (id - 1));
		if (pp != NULL)
			p.getDirectNeighbors().push_back(pp); //cares for the first of each line

		//direct right
		pp = this->getParticleAtID(isLast ? (-1) : (id + 1));
		if (pp != NULL)
			p.getDirectNeighbors().push_back(pp); //cares for the last of each line

		//direct above
		pp = this->getParticleAtID(id + cWidth);
		if (pp != NULL)
			p.getDirectNeighbors().push_back(pp);

		std::cout << "Particle " << (*it).getID() << ": (size=" << (*it).getDirectNeighbors().size() <<") ";
		for (std::list<Particle *>::iterator j = (*it).getDirectNeighbors().begin();
			j != (*it).getDirectNeighbors().end(); j++){
			std::cout << (*(*j)).getID() << ", " ;
		}
		std::cout << std::endl;

		//diagonal lower left
		pp = this->getParticleAtID(isFirst ? (-1) : (id - 1 - cWidth));
		if (pp != NULL)
			p.getDiagNeighbors().push_back(pp); //cares for the first of each line

		//diagonal lower right
		pp = this->getParticleAtID(isLast ? (-1) : (id + 1 - cWidth));
		if (pp != NULL)
			p.getDiagNeighbors().push_back(pp); //cares for the last of each line

		//diagonal upper left
		pp = this->getParticleAtID(isFirst ? (-1) : (id - 1 + cWidth));
		if (pp != NULL)
			p.getDiagNeighbors().push_back(pp); //cares for the first of each line

		//diagonal upper right
		pp = this->getParticleAtID(isLast ? (-1) : (id + 1 + cWidth));
		if (pp != NULL)
			p.getDiagNeighbors().push_back(pp); //cares for the last of each line

		/*
		std::cout << "Particle " << (*it).getID() << ": (size=" << (*it).getDiagNeighbors().size() <<") ";
		for (std::list<Particle *>::iterator j = (*it).getDiagNeighbors().begin();
			j != (*it).getDiagNeighbors().end(); j++){
			std::cout << (*(*j)).getID() << ", " ;
		}
		std::cout << std::endl;
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
