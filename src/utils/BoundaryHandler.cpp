/*
 * BoundaryHandler.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: andal
 */

#include "BoundaryHandler.h"

namespace utils {

BoundaryHandler::BoundaryHandler(std::vector<int> boundary_type_arg,
		LCParticleContainer& container_arg, double h_arg,
		void calculate_arg(Particle&, Particle&)) :
		container(container_arg), domain_size(container_arg.getDomainSize()), width(
				container_arg.getWidth()), height(container_arg.getHeight()), depth(
				container_arg.getDepth()) {
	boundary_type = boundary_type_arg;
	h = h_arg;
	calculate = calculate_arg;
}

BoundaryHandler::~BoundaryHandler() {
	// TODO Auto-generated destructor stub
}

void BoundaryHandler::applyPeriodicMoving() {
	LCOuterParticleIterator iterator;
	//links, unten, vorne sind inklusiv Grenze,
	//rechts, oben, hinten sind exklusive Grenze
	if (boundary_type[0] == 3) {
		iterator = container.beginLeftBoundary();
		while (iterator != container.endLeftBoundary()) {
			if (((*iterator).getX())[0] < 0) {
				utils::Vector<double, 3> tempX = (*iterator).getX();
				tempX[0] = tempX[0] + domain_size[0];
				(*iterator).getX() = tempX;
			}
			assert(((*iterator).getX())[0] >= 0);
//			assert(((*iterator).getX())[0] < domain_size[0]);
//			assert(((*iterator).getX())[1] >= 0);
//			assert(((*iterator).getX())[1] < domain_size[1]);

			++iterator;
		}
	}
	if (boundary_type[1] == 3) {
		iterator = container.beginRightBoundary();
		while (iterator != container.endRightBoundary()) {
			if (((*iterator).getX())[0] >= domain_size[0]) {
				utils::Vector<double, 3> tempX = (*iterator).getX();
				tempX[0] = tempX[0] - domain_size[0];
				(*iterator).getX() = tempX;
			}

			assert(((*iterator).getX())[0] >= 0);
			assert(((*iterator).getX())[0] < domain_size[0]);
//			assert((*iterator).getX()[1] >= 0);
//			assert((*iterator).getX()[1] < domain_size[1]);
			++iterator;
		}
	}
	if (boundary_type[2] == 3) {
		iterator = container.beginBottomBoundary();
		while (iterator != container.endBottomBoundary()) {
			if (((*iterator).getX())[1] < 0) {
				utils::Vector<double, 3> tempX = (*iterator).getX();
				tempX[1] = tempX[1] + domain_size[1];
				(*iterator).getX() = tempX;
			}

			assert((*iterator).getX()[0] >= 0);
			assert((*iterator).getX()[0] < domain_size[0]);
			assert((*iterator).getX()[1] >= 0);
//			assert((*iterator).getX()[1] < domain_size[1]);
			++iterator;
		}
	}
	if (boundary_type[3] == 3) {
		iterator = container.beginTopBoundary();
		while (iterator != container.endTopBoundary()) {
			if (((*iterator).getX())[1] >= domain_size[1]) {
				utils::Vector<double, 3> tempX = (*iterator).getX();
				tempX[1] = tempX[1] - domain_size[1];
				(*iterator).getX() = tempX;
			}

			if ((*iterator).getX()[0] < 0) {
				std::cout << iterator.getCellNumber() << " : "
						<< (*iterator).toString() << std::endl;
				LCOuterParticleIterator iiterator =
						container.beginLeftBoundary();
				while (iiterator != container.endLeftBoundary()) {
					if ((*iiterator) == (*iterator)) {
						break;
					}
					++iiterator;
				}
				assert((*iiterator) == (*iterator));
			}
			assert((*iterator).getX()[0] >= 0);
			assert((*iterator).getX()[0] < domain_size[0]);
			assert((*iterator).getX()[1] >= 0);
			assert((*iterator).getX()[1] < domain_size[1]);
			++iterator;
		}
	}
	if (depth > 0) {
		if (boundary_type[4] == 3) {
			iterator = container.beginFrontBoundary();
			while (iterator != container.endFrontBoundary()) {
				if (((*iterator).getX())[2] < 0) {
					utils::Vector<double, 3> tempX = (*iterator).getX();
					tempX[2] = tempX[2] + domain_size[2];
					(*iterator).getX() = tempX;
				}

				assert((*iterator).getX()[0] >= 0);
				assert((*iterator).getX()[0] < domain_size[0]);
				assert((*iterator).getX()[1] >= 0);
				assert((*iterator).getX()[1] < domain_size[1]);
				assert((*iterator).getX()[2] >= 0);

				++iterator;
			}
		}
		if (boundary_type[5] == 3) {
			iterator = container.beginBackBoundary();
			while (iterator != container.endBackBoundary()) {
				if (((*iterator).getX())[2] >= domain_size[2]) {
					utils::Vector<double, 3> tempX = (*iterator).getX();
					tempX[1] = tempX[1] - domain_size[1];
					(*iterator).getX() = tempX;
				}

				assert((*iterator).getX()[0] >= 0);
				assert((*iterator).getX()[0] < domain_size[0]);
				assert((*iterator).getX()[1] >= 0);
				assert((*iterator).getX()[1] < domain_size[1]);
				assert((*iterator).getX()[2] >= 0);
				assert((*iterator).getX()[2] < domain_size[2]);

				++iterator;
			}
		}
	}
}

void BoundaryHandler::applyReflecting() {

	utils::Vector<double, 3> v(0.0);
	LCOuterParticleIterator iterator;

	if (boundary_type[0] == 2) {
		iterator = container.beginLeftBoundary();
		while (iterator != container.endLeftBoundary()) {
			if ((*iterator).getX()[0] <= h) {
				double x_arg[3] = { 0, ((*iterator).getX())[1],
						((*iterator).getX())[2] };
				utils::Vector<double, 3> x(x_arg);
				Particle p(x, v, 0, (*iterator).getType());
				calculate((*iterator), p);
			}
			++iterator;
		}
	}

	if (boundary_type[1] == 2) {
		iterator = container.beginRightBoundary();
		while (iterator != container.endRightBoundary()) {
			if ((*iterator).getX()[0] >= domain_size[0] - h) {
				double x_arg[3] = { domain_size[0], ((*iterator).getX())[1],
						((*iterator).getX())[2] };
				utils::Vector<double, 3> x(x_arg);
				Particle p(x, v, 0, (*iterator).getType());
				calculate((*iterator), p);
			}
			++iterator;
		}
	}

	if (boundary_type[2] == 2) {
		iterator = container.beginBottomBoundary();
		while (iterator != container.endBottomBoundary()) {
			if ((*iterator).getX()[1] <= h) {
				double x_arg[3] = { ((*iterator).getX())[0], 0,
						((*iterator).getX())[2] };
				utils::Vector<double, 3> x(x_arg);
				Particle p(x, v, 0, (*iterator).getType());
				calculate((*iterator), p);
			}
			++iterator;
		}
	}

	if (boundary_type[3] == 2) {
		iterator = container.beginTopBoundary();
		while (iterator != container.endTopBoundary()) {
			if ((*iterator).getX()[1] >= domain_size[1] - h) {
				double x_arg[3] = { ((*iterator).getX())[0], domain_size[1],
						((*iterator).getX())[2] };
				utils::Vector<double, 3> x(x_arg);
				Particle p(x, v, 0, (*iterator).getType());
				calculate((*iterator), p);
			}
			++iterator;
		}
	}

	if (depth > 0) {

		if (boundary_type[4] == 2) {
			iterator = container.beginFrontBoundary();
			while (iterator != container.endFrontBoundary()) {
				if ((*iterator).getX()[2] >= domain_size[2] - h) {
					double x_arg[3] = { (*iterator).getX()[0],
							(*iterator).getX()[1], domain_size[2] };
					utils::Vector<double, 3> x(x_arg);
					Particle p(x, v, (*iterator).getM(), (*iterator).getType());
					calculate((*iterator), p);
				}
				++iterator;
			}
		}

		if (boundary_type[5] == 2) {
			iterator = container.beginBackBoundary();
			while (iterator != container.endBackBoundary()) {
				if ((*iterator).getX()[2] <= h) {
					double x_arg[3] = { (*iterator).getX()[0],
							(*iterator).getX()[1], 0 };
					utils::Vector<double, 3> x(x_arg);
					Particle p(x, v, (*iterator).getM(), (*iterator).getType());
					calculate((*iterator), p);
				}
				++iterator;
			}
		}
	}

}

void BoundaryHandler::applyOutflow() {
	LCOuterParticleIterator iterator;
	if (boundary_type[0] == 1) {
		iterator = container.beginLeftBoundary();
		while (iterator != container.endLeftBoundary()) {
			if ((*iterator).getX()[0] <= 0) {
				(container.getList()).remove(&(*iterator));
			}
			++iterator;
		}
	}
	if (boundary_type[1] == 1) {
		iterator = container.beginRightBoundary();
		while (iterator != container.endRightBoundary()) {
			if ((*iterator).getX()[0] >= domain_size[0]) {
				(container.getList()).remove(&(*iterator));
			}
			++iterator;
		}
	}
	if (boundary_type[2] == 1) {
		iterator = container.beginBottomBoundary();
		while (iterator != container.endBottomBoundary()) {
			if ((*iterator).getX()[1] <= 0) {
				(container.getList()).remove(&(*iterator));
			}
			++iterator;
		}
	}
	if (boundary_type[3] == 1) {
		iterator = container.beginTopBoundary();
		while (iterator != container.endTopBoundary()) {
			if ((*iterator).getX()[1] >= domain_size[1]) {
				(container.getList()).remove(&(*iterator));
			}
			++iterator;
		}
	}
	if (depth > 0) {
		if (boundary_type[4] == 1) {
			iterator = container.beginFrontBoundary();
			while (iterator != container.endFrontBoundary()) {
				if ((*iterator).getX()[2] >= domain_size[2]) {
					(container.getList()).remove(&(*iterator));
				}
				++iterator;
			}
		}
		if (boundary_type[5] == 1) {
			iterator = container.beginBackBoundary();
			while (iterator != container.endBackBoundary()) {
				if ((*iterator).getX()[2] < 0) {
					(container.getList()).remove(&(*iterator));
				}
				++iterator;
			}
		}
	}
}

void BoundaryHandler::applyPeriodic() {
	if (boundary_type[0] == 3) {
		LCOuterParticleIterator iterator = container.beginLeftBoundary();
		int i, z, j;
		if (depth > 2) {
			int k;
			while (iterator != container.endLeftBoundary()) {
				i = iterator.getCellNumber();
				z = i - height - 1;
				for (j = 0; j < 2; j++) {
					for (k = 0; k < 2; k++) {
						if (z >= 0 && z < height * depth
								&& !(container.getLeftHaloCells())[z]->empty()) {
							std::list<Particle *>::iterator it2 =
									(container.getLeftHaloCells())[z]->begin();
							while (it2
									!= (container.getLeftHaloCells())[z]->end()) {

								utils::Vector<double, 3> tempX = (*it2)->getX();
								tempX[0] = tempX[0] - ((double) domain_size[0]);
								(*it2)->getX() = tempX;

								calculate((*(*it2)), *iterator);

								tempX[0] = tempX[0] + ((double) domain_size[0]);
								(*it2)->getX() = tempX;

								++it2;
							}
						}
						++z;
					}
					z = z + height - 2;
				}
				++iterator;
			}
		} else {
			while (iterator != container.endLeftBoundary()) {
				i = iterator.getCellNumber();
				;
				for (z = i - 1; z < i + 2; z++) {
					if (z >= 0 && z < container.getLeftBoundaryCells().size()
							&& !((container.getLeftHaloCells())[z]->empty())) {

						std::list<Particle *>::iterator it2 =
								(container.getLeftHaloCells())[z]->begin();
						while (it2 != ((container.getLeftHaloCells())[z])->end()) {

							utils::Vector<double, 3> tempX = (*it2)->getX();
							tempX[0] = tempX[0] - ((double) domain_size[0]);
							(*it2)->getX() = tempX;

							calculate((*(*it2)), *iterator);

							tempX[0] = tempX[0] + ((double) domain_size[0]);
							(*it2)->getX() = tempX;

							++it2;
						}
					}
				}
				++iterator;
			}
		}
	}
	if (boundary_type[2] == 3) {
		LCOuterParticleIterator iterator = container.beginBottomBoundary();
		int i, z, j;
		if (depth > 2) {
			int k;
			while (iterator != container.endBottomBoundary()) {
				i = iterator.getCellNumber();
				z = i - width - 1;
				for (j = 0; j < 2; j++) {
					for (k = 0; k < 2; k++) {
						if (z >= 0 && z < width * depth
								&& !(container.getBottomHaloCells())[z]->empty()) {
							std::list<Particle *>::iterator it2 =
									(container.getBottomHaloCells())[z]->begin();
							while (it2
									!= (container.getBottomHaloCells())[z]->end()) {
								utils::Vector<double, 3> tempX = (*it2)->getX();
								tempX[1] = tempX[1] - ((double) domain_size[1]);
								(*it2)->getX() = tempX;

								calculate((*(*it2)), *iterator);

								tempX[1] = tempX[1] + ((double) domain_size[1]);
								(*it2)->getX() = tempX;

								++it2;
							}
						}
						++z;
					}
					z = z + width - 2;
				}
				++iterator;
			}
		} else {
			while (iterator != container.endBottomBoundary()) {
				i = iterator.getCellNumber();
				z = i - 1;
				for (j = 0; j < 2; j++) {
					if (z >= 0 && z < width
							&& !(container.getBottomHaloCells())[z]->empty()) {
						std::list<Particle *>::iterator it2 =
								(container.getBottomHaloCells())[z]->begin();
						while (it2 != (container.getBottomHaloCells())[z]->end()) {

							utils::Vector<double, 3> tempX = (*it2)->getX();
							tempX[1] = tempX[1] - ((double) domain_size[1]);
							(*it2)->getX() = tempX;

							calculate((*(*it2)), *iterator);

							tempX[1] = tempX[1] + ((double) domain_size[1]);
							(*it2)->getX() = tempX;

							++it2;
						}
					}
					++z;
				}
				++iterator;
			}
		}
	}
	if (boundary_type[4] == 3) {
		LCOuterParticleIterator iterator = container.beginFrontBoundary();
		if (depth > 2) {
			int i, z, j, k;
			while (iterator != container.endFrontBoundary()) {
				i = iterator.getCellNumber();
				z = i - width - 1;
				for (j = 0; j < 2; j++) {
					for (k = 0; k < 2; k++) {
						if (z >= 0 && z < height * width
								&& !(container.getFrontHaloCells())[z]->empty()) {
							std::list<Particle *>::iterator it2 =
									(container.getFrontHaloCells())[z]->begin();
							while (it2
									!= (container.getFrontHaloCells())[z]->end()) {

								utils::Vector<double, 3> tempX = (*it2)->getX();
								tempX[2] = tempX[2] - ((double) domain_size[1]);
								(*it2)->getX() = tempX;

								calculate((*(*it2)), *iterator);

								tempX[2] = tempX[2] + ((double) domain_size[1]);
								(*it2)->getX() = tempX;

								++it2;
							}
						}
						++z;
					}
					z = z + width - 2;
				}
				++iterator;
			}
		}
	}
}

} /* namespace utils */
