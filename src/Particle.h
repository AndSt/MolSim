/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <list>

#include "utils/Vector.h"

class Particle {

private:

	/** the position of the particle */
	utils::Vector<double, 3> x;

	/** the velocity of the particle */
	utils::Vector<double, 3> v;

	/** the force effective on this particle */
	utils::Vector<double, 3> f;


	utils::Vector<double, 3> temp_f;

	/** the force which WAS effective on this particle */
	utils::Vector<double, 3> old_f;

	/** the mass of this particle */
	double m;

	/** type of the particle. Use it for whatever you want (e.g. to seperate
	 * molecules belonging to different bodies, matters, and so on)
	 */
	int type;

	/**
	 * list of direct neighbors (needed for membranes)
	 */
	std::list<Particle> directNeighbors;

	/**
	 * list of diagonal neighbors (needed for membranes)
	 */
	std::list<Particle> diagNeighbors;

	/**
	 * the particles in a body have the same type
	 * but each particle has its own ID.
	 * The IDs should be done within the initialization of the body.
	 */
	int ID;

public:
	Particle(int type = 0);

	Particle(const Particle& other);

	Particle(
			// for visualization, we need always 3 coordinates
			// -> in case of 2d, we use only the first and the second
			utils::Vector<double, 3> x_arg, utils::Vector<double, 3> v_arg,
	        double m_arg, int type);

	virtual ~Particle();

	utils::Vector<double, 3>& getX();

	utils::Vector<double, 3>& getF();

	utils::Vector<double, 3>& getOldF();

	utils::Vector<double, 3>& getV();

	utils::Vector<double, 3> getTempF();

	double& getM();

	int& getType();

	bool operator==(Particle& other);

	std::string toString();

	void setF(utils::Vector<double, 3> newF);

	void deleteTempF();

	void updateTempF(utils::Vector<double, 3> newF);

	std::list<Particle>& getDirectNeighbors();

	std::list<Particle>& getDiagNeighbors();

	int& getID();

	bool isDirectNeighborTo(Particle p);

	bool isDiagNeighborTo(Particle p);
};

std::ostream& operator<<(std::ostream& stream, Particle& p);

#endif /* PARTICLE_H_ */
