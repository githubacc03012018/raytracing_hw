#pragma once
#include "../L2_hw/Triangle.h"
#include <vector>
class World {
private:
	//std::vector<std::shared_ptr<Triangle>> world;

	std::vector<Triangle> world;
public:
	void Add(Triangle t);
	bool HasRayIntersection(Ray& r, Triangle& hitObject);
};
