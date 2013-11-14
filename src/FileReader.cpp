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
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace std;

log4cxx::LoggerPtr filereaderlogger(log4cxx::Logger::getLogger("FileReader"));

FileReader::FileReader() {
	LOG4CXX_TRACE(filereaderlogger,"FileReader constructed.");
}

FileReader::~FileReader() {
	LOG4CXX_TRACE(filereaderlogger,"FileReader destructed.");
}


void FileReader::readFile(std::list<Particle>& particles, char* filename) {
	double x[] = {0,0,0};
	double v[] = {1,1,1};
	double m = 1;
    int num_particles = 0;

    std::ifstream input_file(filename);
    string tmp_string;

    if (input_file.is_open()) {
    	
    	LOG4CXX_WARN(filereaderlogger, "Reading open file.");
    	getline(input_file, tmp_string);
    	LOG4CXX_INFO(filereaderlogger,"Reading " << tmp_string << " line.");

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    		LOG4CXX_INFO(filereaderlogger,"Reading comment line.");
    	}

    	istringstream numstream(tmp_string);
    	numstream >> num_particles;
    	LOG4CXX_INFO(filereaderlogger,"Reading " << num_particles);
    	getline(input_file, tmp_string);
    	LOG4CXX_INFO(filereaderlogger,"Read line: " << tmp_string << ".");

    	for (int i = 0; i < num_particles; i++) {
    		istringstream datastream(tmp_string);

    		for (int j = 0; j < 3; j++) {
    			datastream >> x[j];

    		}
    		for (int j = 0; j < 3; j++) {
    			datastream >> v[j];
    		}
    		if (datastream.eof()) {
    			LOG4CXX_ERROR(filereaderlogger,"Error reading file: eof reached unexpectedly reading from line " << i);
    			exit(-1);
    		}
    		datastream >> m;
    		Particle p(x, v, m);
    		particles.push_back(p);

    		getline(input_file, tmp_string);
    		LOG4CXX_INFO(filereaderlogger,"Read line: " << tmp_string << ".");
    	}
    } else {
    	LOG4CXX_ERROR(filereaderlogger,"Error: could not open file " << filename );
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

    	LOG4CXX_WARN(filereaderlogger, "Reading open file.");
    	getline(input_file, tmp_string);
    	LOG4CXX_INFO(filereaderlogger,"Reading " << tmp_string << " line.");

    	while (tmp_string.size() == 0 || tmp_string[0] == '#') {
    		getline(input_file, tmp_string);
    		LOG4CXX_INFO(filereaderlogger,"Reading comment line.");
    	}

    	istringstream numstream(tmp_string);
    	numstream >> numCub;
    	LOG4CXX_INFO(filereaderlogger,"Reading " << numCub << ".");
    	getline(input_file, tmp_string);
    	LOG4CXX_INFO(filereaderlogger,"Read line: " << tmp_string);

    	for (int i = 0; i < numCub; i++) {
    	    istringstream datastream(tmp_string);

    	    for (int j = 0; j < 3; j++) {
    	    	datastream >> ori[j];
    	    }

    	    for (int j = 0; j < 3; j++) {
    	    	datastream >> startVelocity[j];
    	    }

    	    if (datastream.eof()) {
    	    	LOG4CXX_ERROR(filereaderlogger,"Error reading file: eof reached unexpectedly reading from line " << i);
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
    	    LOG4CXX_INFO(filereaderlogger,"Read line: " << tmp_string);
    	}
   } else {
	   LOG4CXX_ERROR(filereaderlogger,"Error: could not open file " << filename );
    	exit(-1);
   }

}

