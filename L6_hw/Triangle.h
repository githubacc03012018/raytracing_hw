#pragma once
#include "Vector3.h"
#include "Ray.h"

class Material;

class Triangle {
public:
	Triangle(Point3 v0, Point3 v1, Point3 v2, Color c) : vertices{ v0, v1, v2 }, color{ c } {}


	Triangle() {}
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
		auto edge1 = v2() - v1();

		return cross(edge0, edge1).Normalize();
	}

	double Area() {
		auto edge0 = v1() - v0();
		auto edge1 = v2() - v1();

		return cross(edge0, edge1).Length() / 2;
	}

	bool HasRayIntersection(Ray& r, double closestT, Point3 cameraPos) {
		constexpr float kEpsilon = 1e-8;
		Vector3 v0v1 = v1() - v0();
		Vector3 v0v2 = v2() - v0();

		auto normal = cross(v0v1, v0v2).Normalize();
		this->normal = normal;
		auto s = Dot(normal, r.GetDirection());
		if (abs(s) < kEpsilon) {
			return false;
		}

		auto d = -Dot(normal, v0());
		auto t = -(Dot(normal, cameraPos) + d) / s;

		if (t < 0) {
			return false;
		}

		//P(t) = origin + t * rayDirection	
		auto P = r.GetAt(t);
		intersectionPoint = P;
		if (t > closestT) return false;

		//Save the point itself
		this->t = t;

		//edge 0
		auto edge0 = v1() - v0();
		auto vp0 = P - v0();
		auto C = cross(edge0, vp0);
		if (Dot(normal, C) < 0) {
			return false;
		}

		//edge1
		auto edge1 = v2() - v1();
		auto vp1 = P - v1();
		C = cross(edge1, vp1);
		if (Dot(normal, C) < 0) {
			return false;
		}

		//edge 2
		auto edge2 = v0() - v2();
		auto vp2 = P - v2();
		C = cross(edge2, vp2);
		if (Dot(normal, C) < 0) {
			return false;
		}

		return true;
	}

	Point3 GetPointOfIntersection() {
		return intersectionPoint;
	}

	double GetT() {
		return t;
	}

	Vector3 GetNormal() {
		return normal;
	}

	Color GetColor() {
		return color;
	}
private:
	Point3 vertices[3];
	Color color;
	double t;
	Point3 intersectionPoint;
	Vector3 normal;
};