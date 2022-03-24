#pragma once
#include "../L2_hw/Vector3.h"

class Triangle
{
public:
	Triangle(Point3 v0, Point3 v1, Point3 v2) : vertices{ v0, v1, v2 } {}

	Point3 v0() {
		return vertices[0];
	}

	Point3 v1() {
		return vertices[1];
	}

	Point3 v2() {
		return vertices[2];
	}

	Vector3 Normal() {
		auto edge0 = v1() - v0();
		auto edge1 = v1() - v2();

		return cross(edge0, edge1).Normalize();
	}

	double Area() {
		auto edge0 = v1() - v0();
		auto edge1 = v1() - v2();

		return cross(edge0, edge1).Length() / 2;
	}

private:
	Point3 vertices[3];
};
