/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"
#include "utils/Vector.h"
#include "Cuboid.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

FileReader::FileReader() {
}

FileReader::~FileReader() {
}


void FileReader::readFile(std::list<Particle>& particles, char* filename) {
	double x[] = {0,0,0};
	double v[] = {1,1,1};
	double m = 1;
    int num_particles = 0;

    std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {

    	getline(input_file, tmp_string);
    	cout << "Read line: " << tmp_string << endl;

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    		cout << "Read line: " << tmp_string << endl;
    	}

    	istringstream numstream(tmp_string);
    	numstream >> num_particles;
    	cout << "Reading " << num_particles << "." << endl;
    	getline(input_file, tmp_string);
    	cout << "Read line: " << tmp_string << endl;

    	for (int i = 0; i < num_particles; i++) {
    		istringstream datastream(tmp_string);

    		for (int j = 0; j < 3; j++) {
    			datastream >> x[j];

    		}
    		for (int j = 0; j < 3; j++) {
    			datastream >> v[j];
    		}
    		if (datastream.eof()) {
    			cout << "Error reading file: eof reached unexpectedly reading from line " << i << endl;
    			exit(-1);
    		}
    		datastream >> m;
    		Particle p(x, v, m);
    		particles.push_back(p);

    		getline(input_file, tmp_string);
    		cout << "Read line: " << tmp_string << endl;
    	}
    } else {
    	std::cout << "Error: could not open file " << filename << std::endl;
    	exit(-1);
    }

}

// Input file (eingabe-brownian.txt) lies in src folder
void FileReader::readFileCub(std::list<Cuboid>& cuboids, char* filename) {
	double ori[] = {0,0,0};
	double startVelocity[] = {0,0,0};
	double mass = 1;
	double hei = 0; //height
	double w = 0; //width
	double d = 0; //depth
	double distance = 0;
	double meanVelocity = 0;

	int numCub = 0;

    std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {

    	getline(input_file, tmp_string);
    	cout << "Read line: " << tmp_string << endl;

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    		cout << "Read line: " << tmp_string << endl;
    	}

    	istringstream numstream(tmp_string);
    	numstream >> numCub;
    	cout << "Reading " << numCub << "." << endl;
    	getline(input_file, tmp_string);
    	cout << "Read line: " << tmp_string << endl;

    	for (int i = 0; i < numCub; i++) {
    	    istringstream datastream(tmp_string);

    	    for (int j = 0; j < 3; j++) {
    	    	datastream >> ori[j];
    	    }

    	    for (int j = 0; j < 3; j++) {
    	    	datastream >> startVelocity[j];
    	    }

    	    if (datastream.eof()) {
    	    	cout << "Error reading file: eof reached unexpectedly reading from line " << i << endl;
    	    	exit(-1);
    	    }

    	    datastream >> hei;
    	    datastream >> w;
    	    datastream >> d;
    	    datastream >> distance;
    	    datastream >> mass;
    	    datastream >> meanVelocity;

    	    // Create a new cuboid with extracted information from file
    	    Cuboid cub(hei, w, d, distance, mass, ori, startVelocity, meanVelocity);
    	    cuboids.push_back(cub);

    	    getline(input_file, tmp_string);
    	    cout << "Read line: " << tmp_string << endl;
    	}
   } else {
    	std::cout << "Error: could not open file " << filename << std::endl;
    	exit(-1);
   }

}

