#pragma once
#include <vector>
#include "Triangle.h"
double const infinity = std::numeric_limits<double>::infinity();

class World {
public:
	void Add(Triangle triangle);
	bool HasIntersection(Ray& r, Triangle& hitObject, Point3 cameraPos);
private:
	std::vector<Triangle> world;
};