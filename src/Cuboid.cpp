/*
 * Cub.cpp
 *
 *  Created on: 10.11.2013
 *      Author: son
 */

#include "Cuboid.h"
#include <vector>
#include <Particle.h>
#include "utils/Vector.h"
#include "MaxwellBoltzmannDistribution.h"

Cuboid::Cuboid(){

}

Cuboid::Cuboid(int height, int width, int depth, double distance, double mass,
		utils::Vector<double, 3> ori, utils::Vector<double, 3> startVelocity,
		double meanVelocity) {
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
	cub.clear();

	// Initialize particles in cub
	for (int hei = 0; hei < height; hei++) {
		for (int w = 0; w < width; w++) {
			for (int d = 0; d < depth; d++) {
				// Must set each particle with its own coordinate
				// Ox along width, Oy along height, Oz along depth
				double addTemp[] = { w * h, hei * h, d * h };
				utils::Vector<double, 3> addVector(addTemp);
				utils::Vector<double, 3> vel(ori + addVector);

				Particle p(vel, startVelocity, mass, 1);

				// Movement of each particle superposed by Brownian Motion
				MaxwellBoltzmannDistribution(p, meanVelocity, 3);

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

Cuboid::~Cuboid() {
}
