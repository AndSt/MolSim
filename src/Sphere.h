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
 *  \brief This is a class representing a 3D sphere of particles.
 * 
 *  One sphere can save a 3D set of particles, which are located next to each other.
 *  There is no isolated particle in one sphere.
 */
class Sphere {
private:
	/** A 3D vector indicating the location of the center.*/
	utils::Vector<double, 3> center;
	
	/** A 3D vector indicating the start velocity.*/
	utils::Vector<double, 3> startV;

	/** Mean velocity. Used for brownian motion (aka. Brownian Factor).*/
	double meanV;

	/** Mass of each particle in the sphere.*/
	double m;

	/** The sphere's radius in particles (an int number!).
	 * The real double radius is radius*meshWidth.
	 */	
	int radius;

	/** The mesh distance between 2 particles.*/
	double meshWidth;

	/** Type of particles in sphere.*/
	int parType;

	/** The list of particles stored in this sphere.*/
	std::list<Particle> sph;

	/** A list of centers of parallel circles along the Oz axis.
	 * The distance between 2 nearest circles is meshWidth.
	 * There are (2*radius + 1) elements in this list.
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).	 
	 */
	std::vector<utils::Vector<double, 3> > listOfCenters;

	/** A list of radii of parallel circles along the Oz axis,
	 * whose centers are stored in listOfCenters.
	 * Both listOfCenters and listOfRadii synchronize with eachother.
	 * For example: The circle with listOfCenters[i] has radius listOfRadii[i]. 
	 * There are (2*radius + 1) elements in this list.
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).	 
	 */
	std::vector<int> listOfRadii;

	/** Initializes listOfCenters:
	 * listOfCenters[radius] = center (the biggest circle)
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).
	 * Must be called before drawBiggestCircleArea().	 
	 */
	void initListOfCenters();

	/** Initializes listOfRadii:
	 * listOfRadii[radius] = radius (the biggest circle)
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).
	 * Must be called before drawBiggestCircleArea().	 
	 */
	void initListOfRadii();
	
	// Draw a point/particle in position (x, y) WITH ORIGIN tempCenter (not (0,0,0) !!!)
	// In each circle, we need only x and y (z = tempCenter[2] and will not be changed in this circle)
	// x and y are not int; x = k*meshWidth with k int for example
	/** Push a single particle with the given coordinates into sph:
	 * Its coordinates are: (x*meshWidth, y*meshWidth, tempCenter[2])
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).
	 * Is elementary function for building the sphere.
	 *
	 * @param tempCenter: the coordinates of the center of the CURRENT circle.
	 * @param x: the horizontal value in the current circle.
	 * @param y: the vertical value in the current circle.	 
	 */
	void plot(utils::Vector<double, 3> tempCenter, int x, int y);

	/** Draw a single vertical line in the current circle.
	 * Length = 2*upperHeight + 1
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).
	 *
	 * @param[in] tempCenter: the coordinates of the center of the CURRENT vertical line.
	 * @param[in] upperHeight: Since every line is symmetric, only the upper length is needed.
	 * @param[out] sph: the new particle will be stored here.
	 */
	void drawVerticalLine(utils::Vector<double, 3> tempCenter, int upperHeight);

	/** Draw a circle with given radius and center.
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).
	 * To build a sphere we have to make (2*radius + 1) circles.
	 *
	 * @param[in] tempCenter: the coordinates of the center of the CURRENT circle.
	 * @param[in] rad: radius of the current circle.
	 */
	void drawCircleArea(utils::Vector<double, 3> tempCenter, int rad);

	/** Draw the biggest circle of the sphere.
	 * Also fills listOfCenters and listOfRadii 
	 * Is private and needed for building the sphere (Alternative 2: Bresenham).
	 */
	void drawBiggestCircleArea();

public:
	/** Default constructor.
	 */
	Sphere();

	// Constructor: Height first, then width and depth
	// Height --> Width --> Depth
	/** The main constructor.
	 * 
	 * Constructs a new sphere with all information needed.
	 * @param[in] center Sphere's center's location.
	 * @param[in] startV Start velocity of all particles in the beginning.
	 * @param[in] meanV Mean velocity (aka. brownian factor) of each partcile in sphere.
	 * @param[in] m Mass of each particle in sphere.	 
	 * @param[in] radius Radius of the sphere in particles (int not double!).
	 * @param[in] meshWidth The mesh distance between every 2 nearest particles of sphere.
	 */
	Sphere(utils::Vector<double, 3> center, utils::Vector<double, 3> startV,
			double meanV, double m, int radius, double meshWidth, int parType);

	/** \returns Sphere's center's location.
	 */
	utils::Vector<double, 3>& getCenter();

	/** \returns Velocity at the beginning of each particle in sphere.
	 */
	utils::Vector<double, 3>& getStartV();

	/** \returns Mean velocity of particles.
	 */
	double& getMeanV();

	/** \returns Mass of each particle.
	 */
	double& getM();

	/** \returns Radius of the sphere.
	 */
	int& getRadius();

	/** \returns Mesh distance between every 2 nearest particles.
	 */
	double& getMeshWidth();

	/** \returns List of stored particles in the sphere.
	 */
	std::list<Particle>& getSphere();

	/** \returns particle type of the sphere.
	 */
	int& getType();

	virtual ~Sphere();
};

#endif /* SPHERE_H_ */
