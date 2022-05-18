#pragma once
#include "Ray.h"
#include "HitInformation.h"
#include "Vertex.h"

namespace CRT {
	class Triangle {
	public:
		Triangle(CRT::Vertex v0, CRT::Vertex v1, CRT::Vertex v2) : m_VVertices{ v0, v1, v2 } {}
		Vertex vv0();
		Vertex vv1();
		Vertex vv2();
		Point3 GetPointOfIntersection();
		Vector3 GetNormal();
		double Area();
		bool HasRayIntersection(CRT::Ray& r, bool smoothShading, double tMin, double closestT, double& t);
	private: 
		double t;
		CRT::Point3 m_IntersectionPoint;
		CRT::Vertex m_VVertices[3];
		CRT::Vector3 m_Normal;
	};
}
  
