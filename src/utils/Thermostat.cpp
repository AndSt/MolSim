/*
 * Thermostat.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: son
 */

#include "Thermostat.h"
#include "InputSetting.h"

#include <memory>
#include <iostream>

using namespace std;

Thermostat::~Thermostat() {}

Thermostat::Thermostat(){
	try
	  	{
			auto_ptr<pse_t> h (pse ("InputSetting.xml", xml_schema::flags::dont_validate));

			this->T_init = h->thermo().initT();
			this->T_target = h->thermo().targetT();
			this->delta_T = h->thermo().deltaT();
			this->n_thermo = h->thermo().nThermo();
			this->n_delta = h->thermo().nDelta();
			this->brownian_flag = h->thermo().brownianFlag();
	  	}
	  	catch (const xml_schema::exception& e)
	  	{
			cerr << e << endl;
			exit(-1);
	  	}
}

Thermostat::Thermostat(double T_init, double T_target, double delta_T,
						int n_thermo, int n_delta, bool brownian_flag){
	this->T_init = T_init;
	this->T_target = T_target;
	this->delta_T = delta_T;
	this->n_thermo = n_thermo;
	this->n_delta = n_delta;
	this->brownian_flag = brownian_flag;
}

double Thermostat::getEKin(std::list<Particle> parList){
	double eKinTimes2 = 0;
	double v = 0;
	for (std::list<Particle>::iterator it = parList.begin(); it != parList.end(); it++){
		v = pow((*it).getV()[0], 2) + pow((*it).getV()[1], 2) + pow((*it).getV()[2], 2);
		eKinTimes2 += (*it).getM()*v;
	}
	return eKinTimes2/2;
}

double Thermostat::getMeanV(int dim, std::list<Particle> parList, double mass){
	return sqrt(2*getEKin(parList)/(dim*parList.size()*mass));
}

void Thermostat::setThermo(std::list<Particle>& parList, int dim, double temperature){
	double newEKin = dim*parList.size()*temperature/2;
	double beta = sqrt(newEKin/getEKin(parList));
	if (beta == 1) return;
	//beta != 1
	for (std::list<Particle>::iterator it = parList.begin(); it != parList.end(); it++){
			(*it).getV() = (*it).getV()*beta;
	}
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
