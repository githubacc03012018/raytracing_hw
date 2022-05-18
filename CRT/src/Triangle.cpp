#include "Triangle.h"

namespace CRT {
	CRT::Vertex CRT::Triangle::vv0() {
		return m_VVertices[0];
	}

	Vertex CRT::Triangle::vv1() {
		return m_VVertices[1];
	}

	Vertex CRT::Triangle::vv2() {
		return m_VVertices[2];
	}

	Vector3 CRT::Triangle::GetNormal() {
		return m_Normal;
	}
	 
	double CRT::Triangle::Area() {
		auto edge0 = vv1().GetPosition() - vv0().GetPosition();
		auto edge1 = vv2().GetPosition() - vv1().GetPosition();

		return cross(edge0, edge1).Length() / 2;
	} 

	bool CRT::Triangle::HasRayIntersection(CRT::Ray& r, bool smoothShading, double tMin, double closestT, double& t) {
		constexpr double kEpsilon = 1e-8;
		 
		Vector3 v1v0 = vv1().GetPosition() - vv0().GetPosition();
		Vector3 v2v0 = vv2().GetPosition() - vv0().GetPosition();

		m_Normal = cross(v1v0, v2v0).Normalize();
		auto s = Dot(m_Normal, r.GetDirection());
		if (abs(s) < kEpsilon) {
			return false;
		}

		auto d = -Dot(m_Normal, vv0().GetPosition());
		auto tempT = -(Dot(m_Normal, r.GetOrigin()) + d) / s;
		if (tempT > closestT || tempT < tMin) return false;

		//P(t) = origin + t * rayDirection	
		auto P = r.GetAt(tempT);
		t = tempT;

		m_IntersectionPoint = P;

		//edge 0
		auto edge0 = vv1().GetPosition() - vv0().GetPosition();
		auto vp0 = P - vv0().GetPosition();
		auto C = cross(edge0, vp0);

		if (Dot(m_Normal, C) < 0) {
			return false;
		}

		//edge1
		auto edge1 = vv2().GetPosition() - vv1().GetPosition();
		auto vp1 = P - vv1().GetPosition();
		C = cross(edge1, vp1);

		if (Dot(m_Normal, C) < 0) {

			return false;
		}
		
		//edge 2
		auto edge2 = vv0().GetPosition() - vv2().GetPosition();
		auto vp2 = P - vv2().GetPosition();
		C = cross(edge2, vp2);

		if (Dot(m_Normal, C) < 0) {

			return false;
		}

		if (smoothShading == true) {
			// Calculate the barycentric coordinates
			auto v0p = P - vv0();
			auto v0v1 = vv0().GetPosition() - vv1().GetPosition();
			auto v0v2 = vv0().GetPosition() - vv2().GetPosition();
			auto u = cross(v0p.GetPosition(), v0v2).Length() / cross(v0v1, v0v2).Length();
			auto v = cross(v0v1, v0p.GetPosition()).Length() / cross(v0v1, v0v2).Length();

			m_Normal = (vv1().GetNormal() * u + vv2().GetNormal() * v + vv0().GetNormal() * (1 - u - v)).Normalize();
		}

		return true;
	}

	Point3 CRT::Triangle::GetPointOfIntersection() {
		return m_IntersectionPoint;
	}
}