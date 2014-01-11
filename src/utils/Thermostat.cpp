/*
 * Thermostat.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: son
 */

#include "Thermostat.h"
#include "InputSetting.h"
#include "MaxwellBoltzmannDistribution.h"

#include <memory>
#include <iostream>

using namespace std;

Thermostat::~Thermostat() {}

Thermostat::Thermostat(){}

Thermostat::Thermostat(const std::string filename){
	try
	  	{
			auto_ptr<pse_t> h (pse (filename, xml_schema::flags::dont_validate));
			this->enabled = h->thermo().enabled();
			this->T_init = h->thermo().initT();
			this->T_target = h->thermo().targetT();
			this->delta_T = h->thermo().deltaT();
			this->n_thermo = h->thermo().nThermo();
			this->n_delta = h->thermo().nDelta();
			this->brownian_flag = h->thermo().brownianFlag();
	  	}
	  	catch (const xml_schema::exception& e)
	  	{
			cerr << e;
			exit(-1);
	  	}
}

Thermostat::Thermostat(double T_init, double T_target, double delta_T,
						int n_thermo, int n_delta, bool brownian_flag, bool enabled){
	this->enabled = enabled;
	this->T_init = T_init;
	this->T_target = T_target;
	this->delta_T = delta_T;
	this->n_thermo = n_thermo;
	this->n_delta = n_delta;
	this->brownian_flag = brownian_flag;
}

double Thermostat::getEKin(std::list<Particle *>& parList){
	double eKinTimes2 = 0;
	double v = 0;
	for (std::list<Particle *>::iterator it = parList.begin(); it != parList.end(); it++){
		v = pow((*it)->getV()[0], 2) + pow((*it)->getV()[1], 2) + pow((*it)->getV()[2], 2);
		eKinTimes2 += (*it)->getM()*v;
	}
	return eKinTimes2/2;
}

double Thermostat::getMeanV(std::list<Particle *>& parList, int dim, double mass){
	return sqrt(2*getEKin(parList)/(dim*parList.size()*mass));
}

void Thermostat::setThermo(std::list<Particle *>& parList, int dim, double temperature){
	double newEKin = dim*parList.size()*temperature/2;
	double beta = sqrt(newEKin/getEKin(parList));
	if ((beta==1)/*&&(brownian_flag==false)*/) return;

	//beta!=1 or brownian_flag==true
	for (std::list<Particle *>::iterator it = parList.begin();
						it != parList.end(); it++){
			(*it)->getV() = beta*((*it)->getV());
			//if (brownian_flag==true)
				//Hardcode mass=1
				//MaxwellBoltzmannDistribution(*(*it), this->getMeanV(parList, dim, 1), 2);
	}
}

bool& Thermostat::getEnabled(){
	return enabled;
}

double& Thermostat::getT_init(){
		return T_init;
	}

double& Thermostat::getT_target(){
	return T_target;
}

double& Thermostat::getDelta_T(){
	return delta_T;
}

int& Thermostat::getn_thermo(){
	return n_thermo;
}

int& Thermostat::getn_delta(){
	return n_delta;
}

bool& Thermostat::getBrownian_flag(){
	return brownian_flag;
}
