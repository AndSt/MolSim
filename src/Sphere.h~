/*
 * Sphere.h
 *
 *  Created on: 30.11.2013
 *      Author: Son
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "utils/Vector.h"
#include "Particle.h"
#include <list>
#include <vector>



/** \class Sphere
 *  \brief This is a class representing a 3D cuboid of particles.
 * 
 *  One cuboid can save a 3D set of particles, which are located next to each other.
 *  There is no isolated particle in one cuboid.
 */
class Sphere {
private:

	utils::Vector<double, 3> center; 		/*!< A 3D vector indicating the location of the lower left corner of a cuboid. */
	utils::Vector<double, 3> startV;
	double meanV;

	double m;

	// number of particles	
	int radius;

	double meshWidth;

	std::list<Particle> sph;

	// List of (2*radius + 1) centers used to draw the circles
	std::vector<utils::Vector<double, 3> > listOfCenters;

	// List of (2*radius + 1) radii used to draw the circles
	// INT !!!
	std::vector<int> listOfRadii;

	// Prepare before calling drawBiggestCircleArea();
	void initListOfCenters();
	void initListOfRadii();
	
	// Draw a point/particle in position (x, y) WITH ORIGIN tempCenter (not (0,0,0) !!!)
	// In each circle, we need only x and y (z = tempCenter[2] and will not be changed in this circle)
	// x and y are not int; x = k*meshWidth with k int for example
	void plot(utils::Vector<double, 3> tempCenter, int x, int y);

	void drawVerticalLine(utils::Vector<double, 3> tempCenter, int upperHeight);

	void drawCircleArea(utils::Vector<double, 3> tempCenter, int rad);

	void drawBiggestCircleArea();

public:
	/** Default constructor.
	 */
	Sphere();

	// Constructor: Height first, then width and depth
	// Height --> Width --> Depth
	/** /brief The main constructor.
	 * 
	 * Constructs a new cuboid with all information needed.
	 * @param[in] height Cuboid's height in particles.
	 * @param[in] width Cuboid's width in particles.
	 * @param[in] depth Cuboid's depth in particles.
	 * @param[in] distance Cuboid's mesh width.
	 * @param[in] mass Mass of each particle in cuboid.
	 * @param[in] ori Cuboid's lower left corner's 3D coordinate.
	 * @param[in] startVelocity Velocity at the beginning of each particle in cuboid.
	 * @param[in] meanVelocity Mean velocity (aka. brownian factor) of each partcile in cuboid.
	 */
	Sphere(utils::Vector<double, 3> center, utils::Vector<double, 3> startV, double meanV, double m, int radius, double meshWidth);

	/** \returns Cuboid's lower left corner's location.
	 */
	utils::Vector<double, 3>& getCenter();

	/** \returns Velocity at the beginning of each particle in cuboid.
	 */
	utils::Vector<double, 3>& getStartV();

	double& getMeanV();

	double& getM();

	int& getRadius();

	double& getMeshWidth();

	std::list<Particle>& getSphere();

	virtual ~Sphere();
};

#endif /* SPHERE_H_ */
