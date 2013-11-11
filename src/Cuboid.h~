/*
 * Cuboid.h
 *
 *  Created on: 09.11.2013
 *      Author: Son
 */

#ifndef CUBOID_H_
#define CUBOID_H_
#include <vector>
#include <Particle.h>
#include "utils/Vector.h"
#include <list>

class Cuboid {
private:
	// The coordinate of the lower left front-side corner
	utils::Vector<double, 3> origin;

	// The 3D-Vector of Particles of Cuboid
	std::list<Particle> cub;

	// Dimensions
	int cHeight, cWidth, cDepth;

	// Mesh width between 2 particles
	double h;

	// Particles' mass
	double m;

	// Initial velocity of the particles
	utils::Vector<double, 3> startV;

	// Mean velocity (is a double, NOT A VECTOR!)
	double meanV;

public:
	Cuboid();

	// Constructor: Height first, then width and depth
	// Height --> Width --> Depth
	Cuboid(int height, int width, int depth, double distance, double mass, utils::Vector<double, 3> ori, utils::Vector<double, 3> startVelocity, double meanVelocity);

	utils::Vector<double, 3>& getOrigin();

	utils::Vector<double, 3>& getStartV();

	std::list<Particle>& getCuboid();

	int getHeight();
	void setHeight(double newH);

	int getWidth();
	void setWidth(double newW);

	int getDepth();
	void setDepth(double newD);

	double getDistance();
	void setDistance(double newD);

	double getMass();
	void setMass(double newM);

	double getMeanV();
	void setMeanV(double newV);

	int getSize();

	virtual ~Cuboid();
};

#endif /* CUBOID_H_ */
