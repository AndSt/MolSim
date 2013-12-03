/*
 * Sphere.cpp
 *
 *  Created on: 09.11.2013
 *      Author: Son
 */

#include "Sphere.h"
#include "Cuboid.h"
#include "utils/Vector.h"
#include "MaxwellBoltzmannDistribution.h"
#include <iostream>

Sphere::Sphere(){}

Sphere::Sphere(utils::Vector<double, 3> center1, utils::Vector<double, 3> startV1, 
					double meanV1, double m1, int radius1, double meshWidth1){
	center = center1;
	startV = startV1;
	meanV = meanV1;
	m = m1;
	radius = radius1;
	meshWidth = meshWidth1;
	
	// ALTERNATIVE 1 =================================
	int l = 2*radius + 1;
	double o[] = {center[0] - radius*meshWidth, center[1] - radius*meshWidth, center[2] - radius*meshWidth};
	utils::Vector<double, 3> ori(o);	
	Cuboid c(l, l, l, meshWidth, m,	ori, startV, meanV);
	
	sph.clear();
	std::list<Particle>::iterator it;
	for (it = c.getCuboid().begin(); it != c.getCuboid().end(); it++){
		double x = pow((*it).getX()[0] - center[0],2);
		double y = pow((*it).getX()[1] - center[1],2);
		double z = pow((*it).getX()[2] - center[2],2);

		//double diag = meshWidth/sqrt(2);
		
		if (x + y + z <= pow(radius*meshWidth,2))
			sph.push_back(*it);
	}
	// ================================= ALTERNATIVE 1
	
	/*
	// ALTERNATIVE 2 =================================	
	// Draw the biggest circle, which center belongs
	sph.clear();
	
	drawBiggestCircleArea();

	// now the lisOfCenters and listOfRadii are fully initialized
	for (int i = 0; i<= 2*radius; i++){
		drawCircleArea(listOfCenters[i], listOfRadii[i]);
	}
	
	// ================================= ALTERNATIVE 2
	*/
}

void Sphere::initListOfCenters(){
	listOfCenters = std::vector<utils::Vector<double, 3> > (2*radius + 1, center);
	listOfCenters[radius] = center;
	for (int i = 1; i <= radius; i++){
		double front[] = {center[0], center[1], center[2] + i*meshWidth};
		double behind[] = {center[0], center[1], center[2] - i*meshWidth};
		listOfCenters[radius + i] = utils::Vector<double, 3> (front);
		listOfCenters[radius - i] = utils::Vector<double, 3> (behind);
	}
}

// Default value = 0
void Sphere::initListOfRadii(){
	listOfRadii = std::vector<int> (2*radius + 1, 0);
	listOfRadii[radius] = radius;
}

void Sphere::plot(utils::Vector<double, 3> tempCenter, int x, int y){
	double a[] = {tempCenter[0]+x*meshWidth, tempCenter[1]+y*meshWidth, tempCenter[0]};	
	utils::Vector<double, 3> pos(a);

	// Being used in the beginning --> v = startV
	Particle p(pos, startV, m, 0);
	// BROWNIAN as well!
	MaxwellBoltzmannDistribution(p, meanV, 2);
	sph.push_back(p);
}

void Sphere::drawVerticalLine(utils::Vector<double, 3> tempCenter, int upperHeight){
	// Must avoid the case where plot 2 particles at the same place
	plot(tempCenter, 0, 0);
	for(int i= 1; i <= upperHeight; i++){
		plot(tempCenter, 0, i);
		plot(tempCenter, 0, (-1)*i);
	}
}

// tempCenter != center
// all tempCenter lie on Oz axis (the circles are parallel to each other and also to Oxy, distance =  meshWidth)
void Sphere::drawBiggestCircleArea(){
	// Implementing Bresenham's Algorithm 1 (see GAD Lecture)
	double x = 0.0;
	int xx = 0;
	double y = radius*meshWidth;
	int yy = radius;
	//z = center[2]

	drawVerticalLine(center, radius);		// from (0,R) to (0,-R)

	//plot(center, radius, 0);
	//plot(center, (-1)*radius, 0);

	double dToPointR[] = {meshWidth, radius*meshWidth - meshWidth/2, 0};
	double F = dToPointR[0]*dToPointR[0] + dToPointR[1]*dToPointR[1] - pow(radius*meshWidth, 2);

		utils::Vector<double, 3> tempCenter1(center);
		utils::Vector<double, 3> tempCenter2(center);
		//utils::Vector<double, 3> tempCenter3(center);
		//utils::Vector<double, 3> tempCenter4(center);

		initListOfRadii();
		initListOfCenters();
		// listOfCenters and listOfRadii must have been initialized before
		
		while (x<=radius*meshWidth){
			if (F<0){
				F = F + 2*x*meshWidth + meshWidth*meshWidth;
			}
			else{
				F = F + 2*meshWidth*(x - y + meshWidth);
				y = y - meshWidth;
				yy--;
			}
			x = x + meshWidth;
			xx++;
			//listOfRadii[radius] = radius already in init
			listOfRadii[radius+xx] = yy;
			listOfRadii[radius-xx] = yy;
			//listOfRadii[radius+yy] = xx;
			//listOfRadii[radius-yy] = xx;

			tempCenter1[0] += meshWidth; 	// from (x,y) to (x,-y)
			tempCenter2[0] -= meshWidth;	// from (-x,y) to (-x,-y)
			//tempCenter3[0] = y;	 	// from (y,x) to (y,-x)
			//tempCenter4[0] = -y; 		// from (-y,x) to (-y,-x)

			drawVerticalLine(tempCenter1, yy);
			drawVerticalLine(tempCenter2, yy);
			//drawVerticalLine(tempCenter3, xx);
			//drawVerticalLine(tempCenter4, xx);
		}
}


void Sphere::drawCircleArea(utils::Vector<double, 3> tempCenter, int rad){
	// Implementing Bresenham's Algorithm 1 (see GAD Lecture)
	int x = 0;
	int y = rad;
	//z = center[2]

	drawVerticalLine(tempCenter, rad);		// from (0,R) to (0,-R)

	plot(tempCenter, rad, 0);
	plot(tempCenter, (-1)*rad, 0);

	double F = 1.25 - rad;
		utils::Vector<double, 3> tempCenter1(tempCenter);
		utils::Vector<double, 3> tempCenter2(tempCenter);
		utils::Vector<double, 3> tempCenter3(tempCenter);
		utils::Vector<double, 3> tempCenter4(tempCenter);

		while (x<y){
			if (F<0){
				F = F + 2*x + 1;
			}
			else{
				F = F + 2*(x - y + 1);
				y = y - 1;
			}
			x = x + 1;

			tempCenter1[0] += meshWidth; 	// from (x,y) to (x,-y)
			tempCenter2[0] -= meshWidth;	// from (-x,y) to (-x,-y)
			tempCenter3[0] = y*meshWidth; 	// from (y,x) to (y,-x)
			tempCenter4[0] = -y*meshWidth; 	// from (-y,x) to (-y,-x)

			drawVerticalLine(tempCenter1, y);
			drawVerticalLine(tempCenter2, y);
			drawVerticalLine(tempCenter3, x);
			drawVerticalLine(tempCenter4, x);
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
