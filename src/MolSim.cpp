#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include "FileReader.h"
#include "utils/Vector.h"

#include <list>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

/**** forward declaration of the calculation functions ****/

/**
* calculate the force for all particles
*/
void calculateF();

/**
* calculate the position for all particles
*/
void calculateX();

/**
* calculate the position for all particles
*/
void calculateV();

/**
* plot the particles to a xyz-file
*/
void plotParticles(int iteration);

// plot the particles to VTKWriter-File
void plotVTK(int iteration);


double start_time = 0;
double end_time = 1000;
double delta_t = 0.014;

std::list<Particle> particles;


int main(int argc, char* argsv[]) {

        cout << "Hello from MolSim for PSE!" << endl;
        cout << "[1]. Koordinaten; [2]. end_time; [3]. delta_t." << endl;
        if (argc != 4) {
                cout << "Errounous programme call! " << endl;
                cout << "./molsym filename" << endl;
        }

        FileReader fileReader;
        fileReader.readFile(particles, argsv[1]);
        // the forces are needed to calculate x, but are not given in the input file.
        calculateF();

        double current_time = start_time;

        int iteration = 0;

        // end_time und delta_t eingegeben via command line
        end_time = (double) atof(argsv[2]);
        delta_t = (double) atof(argsv[3]);

         // for this loop, we assume: current x, current f and current v are known
        while (current_time < end_time) {
                // calculate new x
                calculateX();

                // calculate new f
                calculateF();
                // calculate new v
                calculateV();

                iteration++;
                if (iteration % 10 == 0) {
                        //plotParticles(iteration);
                        plotVTK(iteration);
                }
                cout << "Iteration " << iteration << " finished." << endl;

                current_time += delta_t;
        }

        cout << "output written. Terminating..." << endl;
        return 0;
}


void calculateF() {
        list<Particle>::iterator iterator;
        iterator = particles.begin();

        while (iterator != particles.end()) {
                list<Particle>::iterator innerIterator = particles.begin();

                //sum von Fij fuer alle j (i fest)
                utils::Vector<double, 3> sumFi((double) 0);
                while (innerIterator != particles.end()) {
                        if (innerIterator != iterator) {

                                Particle& p1 = *iterator; //i
                                Particle& p2 = *innerIterator; //j

                                // insert calculation of force here!
                                utils::Vector<double, 3> tempD = p1.getX() - p2.getX();
                                utils::Vector<double, 3> tempF = (p1.getM()*p2.getM()/(pow((tempD.L2Norm()),3)))*(-1)*tempD;
                                sumFi += tempF;
                        }
                        ++innerIterator;
                }
                (*iterator).setF(sumFi);
                ++iterator;
        }
}

void calculateX() {
        list<Particle>::iterator iterator = particles.begin();
        while (iterator != particles.end()) {

                Particle& p = *iterator;

                // insert calculation of X here!
                utils::Vector<double, 3> tempX = p.getX() + delta_t*p.getV() + ((delta_t)*(delta_t)/(2*p.getM()))*p.getOldF();
                p.setX(tempX);

                ++iterator;
        }
}


void calculateV() {
        list<Particle>::iterator iterator = particles.begin();
        while (iterator != particles.end()) {

                Particle& p = *iterator;

                // insert calculation of velocity here!
                utils::Vector<double, 3> tempV = p.getV() + (delta_t/(2*p.getM()))*(p.getF()+p.getOldF());
                p.setV(tempV);
                ++iterator;
        }
}


void plotParticles(int iteration) {

        string out_name("MD_vtk");

        outputWriter::XYZWriter writer;
        writer.plotParticles(particles, out_name, iteration);


}

void plotVTK(int iteration){
        outputWriter::VTKWriter writer;
        list<Particle>::iterator iterator = particles.begin();
        writer.initializeOutput(particles.size());
                while (iterator != particles.end()) {
                        Particle& p = *iterator;

                        writer.plotParticle(p);
                        ++iterator;
                }
                string out_name("MD1_vtk");
        writer.writeFile(out_name,iteration);
}
