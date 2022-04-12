#include "World.h"

void World::Add(Triangle triangle) {
	world.push_back(triangle);
}

bool World::HasIntersection(Ray& r, Triangle& hitObject, Point3 cameraPos) {
	bool hasHit = false;
	double closestT = infinity;

	for (Triangle triangle : world) {
		if (triangle.HasRayIntersection(r, closestT, cameraPos)) {
			hasHit = true;
			hitObject = triangle;
			closestT = hitObject.GetT();
		}
	}

	return hasHit;
}