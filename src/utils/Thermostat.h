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
#include <string>

class Thermostat {
private:
	/**
	 * True if thermostat is switched on, false if switched off.
	 */
	bool enabled;

	/**
	 * Init temperature of thermostat.
	 */
	double T_init;

	/**
	 * Target temperature of thermostat.
	 */
	double T_target;

	/**
	 * Temperature difference between two nearest n_delta timesteps.
	 */
	double delta_T;

	/**
	 * Timesteps, after which the thermostat will be applied.
	 */
	int n_thermo;

	/**
	 * Timesteps, after which the temperature will be updated.
	 */
	int n_delta;

	/**
	 * True if Brownian Motion is needed, false if not.
	 */
	bool brownian_flag;

public:
	/**
	 * Default constructor.
	 */
	Thermostat();

	/**
	 * Main constructor, which will read information from filename
	 * and extract all needed information for thermostat.
	 */
	Thermostat(const std::string filename);

	virtual ~Thermostat();

	/**
	 * Secondary constructor, which will initialize a thermostat
	 * with given parameters.
	 *
	 * @param[in] T_init init temperature
	 * @param[in] T_target target temperature
	 * @param[in] delta_T temperature difference
	 * @param[in] n_thermo timesteps, after which thermostat will be applied
	 * @param[in] n_delta timesteps, after which temperature will be updated
	 * @param[in] brownian_flag option for Brownian Motion
	 * @param[in] enabled option for switching thermostat on/off
	 */
	Thermostat(double T_init, double T_target, double delta_T,
				int n_thermo, int n_delta, bool brownian_flag, bool enabled);

	/**
	 * \return kinetic energy of the system.
	 *
	 * @param[in] parList a list of pointers of particles
	 */
	double getEKin(std::list<Particle *>& parList);

	/**
	 * \return mean velocity of the system for Brownian Motion.
	 *
	 * @param[in] parList a list of pointers of particles
	 * @param[in] dim number of dimensions (2 or 3)
	 * @param[in] mass mass of each particle in the system
	 */
	double getMeanV(std::list<Particle *>& parList, int dim, double mass);

	/**
	 * Setter.
	 *
	 * @param[in] parList a list of pointers of particles
	 * @param[in] dim number of dimensions (2 or 3)
	 * @param[in] temperature desired temperature, which will be reached after the thermostat was set.
	 */
	void setThermo(std::list<Particle *>& parList, int dim, double temperature);

	/**
	 * \return init temperature of the system.
	 */
	double& getT_init();

	/**
	 * \return target temperature of the system.
	 */
	double& getT_target();

	/**
	 * \return temperature difference, which will be added every n_delta timesteps.
	 */
	double& getDelta_T();

	/**
	 * \return timesteps, after which thermostat will be applied.
	 */
	int& getn_thermo();

	/**
	 * \return timesteps, after which the temperature will be updated.
	 */
	int& getn_delta();

	/**
	 * \return option for Brownian Motion.
	 */
	bool& getBrownian_flag();

	/**
	 * \return option for switching thermostat on/off.
	 */
	bool& getEnabled();
};

#endif /* THERMOSTAT_H_ */
