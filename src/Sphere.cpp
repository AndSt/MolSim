/*
 * Sphere.cpp
 *
 *  Created on: 09.11.2013
 *      Author: Son
 */

#include "Sphere.h"
#include "MaxwellBoltzmannDistribution.h"

Sphere::Sphere(){}

Sphere::Sphere(utils::Vector<double, 3> center, utils::Vector<double, 3> startV, double meanV, double m, int radius, double meshWidth){
	this->center = center;
	this->startV = startV;
	this->meanV = meanV;
	this->m = m;
	this->radius = radius;
	this->meshWidth = meshWidth;

	// Draw the biggest circle, which center belongs
	listOfCenters.clear();
	listOfRadii.clear();
	sph.clear();
	this->drawCircleArea(center, radius); //the biggest one
	
	// now the lisOfCenters and listOfRadii are fully initialized
	/*std::list<utils::Vector<double, 3> >::iterator itC = listOfCenters.begin();
	for (std::list<int>::iterator itR = listOfRadii.begin(); itR != listOfRadii.end(); ++itR){
		this->drawCircleArea(*itC, *itR);
		++itC;
	}*/
}

void Sphere::plot(utils::Vector<double, 3> tempCenter, double x, double y){
	double a[3] = {tempCenter[0]+x, tempCenter[1]+y, tempCenter[2]};	
	utils::Vector<double, 3> pos(a);

	// Being used in the beginning --> v = startV
	Particle p(pos, startV, m, 0);
	// BROWNIAN as well!
	MaxwellBoltzmannDistribution(p, meanV, 2);
	sph.push_back(p);
}

// tempCenter != center
// all tempCenter lie on Oz axis (the circles are parallel to each other and also to Oxy, distance =  meshWidth)
void Sphere::drawCircleArea(utils::Vector<double, 3> tempCenter, int radius){
	// Implementing Bresenham's Algorithm 1 (see GAD Lecture)
	double x = 0.0;
	double r = radius*meshWidth;
	double y = r;
	//z = tempCenter[2]

	// Plot/Fill VERTICALLY

	//plot(tempCenter, 0, r);
	//plot(tempCenter, 0, (-1)*r);
	// Draw all the points in this vertical line		
	for (double i = (-1)*r; i <= r; i += meshWidth){
		this->plot(tempCenter, 0, i);
	}

	plot(tempCenter, r, 0);
	plot(tempCenter, (-1)*r, 0);

	double F = (1.25*meshWidth - r)*meshWidth;
	
	if (radius == this->getRadius()){
	// The biggest circle
		while (x<y){
			if (F<0){
				F = F + 2*x*meshWidth + meshWidth*meshWidth;
			}
			else{
				F = F + 2*meshWidth*(x - y + meshWidth);
				y = y - meshWidth;
			}
			x = x + meshWidth;

			//plot(tempCenter, x, y);
			//plot(tempCenter, x, (-1)*y);
			// Draw all the points in this vertical line		
			for (double i = (-1)*y; i <= y; i += meshWidth){
				this->plot(tempCenter, x, i);
			}
			utils::Vector<double, 3> savCenter = tempCenter;
			savCenter[2] += x;
			listOfCenters.push_back(savCenter);
			listOfRadii.push_back((int) y/meshWidth);

			//plot(tempCenter, (-1)*x, y);
			//plot(tempCenter, (-1)*x, (-1)*y);
			// Draw all the points in this vertical line		
			for (double i = (-1)*y; i <= y; i += meshWidth){
				this->plot(tempCenter, (-1)*x, i);
			}
			savCenter = tempCenter;
			savCenter[2] += (-1)*x;
			listOfCenters.push_back(savCenter);
			listOfRadii.push_back((int) y/meshWidth);

			//plot(tempCenter, y, x);
			//plot(tempCenter, y, (-1)*x);
			// Draw all the points in this vertical line		
			for (double i = (-1)*x; i <= x; i += meshWidth){
				this->plot(tempCenter, y, i);
			}
			savCenter = tempCenter;
			savCenter[2] += y;
			listOfCenters.push_back(savCenter);
			listOfRadii.push_back((int) x/meshWidth);

			//plot(tempCenter, (-1)*y, x);
			//plot(tempCenter, (-1)*y, (-1)*x);
			// Draw all the points in this vertical line		
			for (double i = (-1)*x; i <= x; i += meshWidth){
				this->plot(tempCenter, (-1)*y, i);
			}
			savCenter = tempCenter;
			savCenter[2] += (-1)*y;
			listOfCenters.push_back(savCenter);
			listOfRadii.push_back((int) x/meshWidth);		
		}
	}
	else
	{
	// Smaller circles
		while (x<y){
			if (F<0){
				F = F + 2*x*meshWidth + meshWidth*meshWidth;
			}
			else{
				F = F + 2*meshWidth*(x - y + meshWidth);
				y = y - meshWidth;
			}
			x = x + meshWidth;

			//plot(tempCenter, x, y);
			//plot(tempCenter, x, (-1)*y);
			// Draw all the points in this vertical line		
			for (double i = (-1)*y; i <= y; i += meshWidth){
				this->plot(tempCenter, x, i);
			}

			//plot(tempCenter, (-1)*x, y);
			//plot(tempCenter, (-1)*x, (-1)*y);
			// Draw all the points in this vertical line		
			for (double i = (-1)*y; i <= y; i += meshWidth){
				this->plot(tempCenter, (-1)*x, i);
			}

			//plot(tempCenter, y, x);
			//plot(tempCenter, y, (-1)*x);
			// Draw all the points in this vertical line		
			for (double i = (-1)*x; i <= x; i += meshWidth){
				this->plot(tempCenter, y, i);
			}

			//plot(tempCenter, (-1)*y, x);
			//plot(tempCenter, (-1)*y, (-1)*x);
			// Draw all the points in this vertical line		
			for (double i = (-1)*x; i <= x; i += meshWidth){
				this->plot(tempCenter, (-1)*y, i);
			}		
		}
	}	
}

std::list<Particle>& Sphere::getSphere(){
	return sph;
}

utils::Vector<double, 3>& Sphere::getCenter(){
	return center;
}

utils::Vector<double, 3>& Sphere::getStartV(){
	return startV;
}

double& Sphere::getMeanV(){
	return meanV;
}

double& Sphere::getM(){
	return m;
}

int& Sphere::getRadius(){
	return radius;
}

double& Sphere::getMeshWidth(){
	return meshWidth;
}

Sphere::~Sphere() {
}
