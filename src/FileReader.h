/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_

#include "Particle.h"
#include <list>
#include <Cuboid.h>

class FileReader {

public:
	FileReader();
	virtual ~FileReader();

	void readFile(std::list<Particle>& particles, char* filename);

	void readFileCub(std::list<Cuboid>& cuboids, char* filename);

	void readStatus(std::list<Particle>& particles,
					double& eps, double& sig, char* filename);
};

#endif /* FILE_READER_H_ */
