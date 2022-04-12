#include "Triangle.h"

namespace CRT {
	Point3 CRT::Triangle::v0() {
		return m_Vertices[0];
	}

	Point3 CRT::Triangle::v1() {
		return m_Vertices[1];
	}

	Point3 CRT::Triangle::v2() {
		return m_Vertices[2];
	}

	Vector3 CRT::Triangle::GetNormal() {
		auto edge0 = v1() - v0();
		auto edge1 = v2() - v1();

		m_Normal = cross(edge0, edge1).Normalize();
		return m_Normal;
	}

	double CRT::Triangle::Area() {
		auto edge0 = v1() - v0();
		auto edge1 = v2() - v1();

		return cross(edge0, edge1).Length() / 2;
	}

	bool CRT::Triangle::HasRayIntersection(CRT::Ray& r, double closestT, Point3 cameraPos) {
		constexpr float kEpsilon = 1e-8;
		Vector3 v0v1 = v1() - v0();
		Vector3 v0v2 = v2() - v0();

		auto normal = cross(v0v1, v0v2).Normalize();
		m_Normal = normal;
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
		m_IntersectionPoint = P;
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

	Point3 CRT::Triangle::GetPointOfIntersection() {
		return m_IntersectionPoint;
	}

	double CRT::Triangle::GetT() {
		return t;
	}

	Color CRT::Triangle::GetColor() {
		return m_Color;
	}
}