/*
 * Thermostat.h
 *
 *  Created on: Dec 9, 2013
 *      Author: son
 */

#ifndef THERMOSTAT_H_
#define THERMOSTAT_H_

#include "Particle.h"

#include <list>

class Thermostat {
private:
	double T_init;

	double T_target;

	double delta_T;

	int n_thermo;

	int n_delta;

	bool brownian_flag;

public:
	Thermostat();
	virtual ~Thermostat();

	Thermostat(double T_init, double T_target, double delta_T,
				int n_thermo, int n_delta, bool brownian_flag);

	double getEKin(std::list<Particle> parList);

	double getMeanV(int dim, std::list<Particle> parList, double mass);

	void setThermo(std::list<Particle>& parList, int dim, double temperature);

	double& getT_init();

	double& getT_target();

	double& getDelta_T();

	int& getn_thermo();

	int& getn_delta();

	bool& getBrownian_flag();
};

#endif /* THERMOSTAT_H_ */
