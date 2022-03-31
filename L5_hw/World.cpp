#include "World.h"
#include "../L2_hw/Triangle.h"
#include "../L2_hw/Common.h"

void World::Add(Triangle t) {
	world.push_back(t);
}

bool World::HasRayIntersection(Ray& r, Triangle& hitObject) {
	bool hasHit = false;
	double closestT = std::numeric_limits<double>::infinity();
	for (auto object : world) {
		if (object.HasRayIntersection(r, closestT)) {
			hitObject = object;
			closestT = hitObject.GetT();
			hasHit = true;
		}
	}

	return hasHit;
}