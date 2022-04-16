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
		 return m_Normal;
	}

	double CRT::Triangle::Area() {
		auto edge0 = v1() - v0();
		auto edge1 = v2() - v1();

		return cross(edge0, edge1).Length() / 2;
	}

	bool CRT::Triangle::HasRayIntersection(CRT::Ray& r, double tMin, double closestT, double& t) {
		constexpr double kEpsilon = 1e-8;
		Vector3 v1v0 = v1() - v0();
		Vector3 v2v0 = v2() - v0();

		m_Normal = cross(v1v0, v2v0).Normalize();
		
		auto s = Dot(m_Normal, r.GetDirection());
		if (abs(s) < kEpsilon) {
			return false;
		}

		auto d = -Dot(m_Normal, v0());
		//TODO: t = -(N.dotProduct(orig) + d) / NdotRayDirection; 
		auto tempT = -(Dot(m_Normal, r.GetOrigin()) + d) / s;
 
		if (tempT > closestT || tempT < tMin) return false;

		//P(t) = origin + t * rayDirection	
		auto P = r.GetAt(tempT);
		t = tempT;
		m_IntersectionPoint = P;
 
		//edge 0
		auto edge0 = v1() - v0();
		auto vp0 = P - v0();
		auto C = cross(edge0, vp0);
		if (Dot(m_Normal, C) < 0) {
			return false;
		}

		//edge1
		auto edge1 = v2() - v1();
		auto vp1 = P - v1();
		C = cross(edge1, vp1);
		if (Dot(m_Normal, C) < 0) {
			return false;
		}

		//edge 2
		auto edge2 = v0() - v2();
		auto vp2 = P - v2();
		C = cross(edge2, vp2);
		if (Dot(m_Normal, C) < 0) {
			return false;
		}

		return true;
	}

	Point3 CRT::Triangle::GetPointOfIntersection() {
		return m_IntersectionPoint;
	}
 
	Color CRT::Triangle::GetColor() {
		return m_Color;
	}
}