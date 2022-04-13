#pragma once
#include "Ray.h"

namespace CRT {
	class Triangle {
	public:
		Triangle(CRT::Point3 v0, CRT::Point3 v1, CRT::Point3 v2, CRT::Color c) : m_Vertices{ v0, v1, v2 }, m_Color{ c } {}
		Triangle() : m_Vertices {
			CRT::Point3{}, CRT::Point3{}, CRT::Point3{}
		}{}
		Point3 v0();
		Point3 v1();
		Point3 v2();
		Point3 GetPointOfIntersection();
		double GetT();
		Vector3 GetNormal();
		Color GetColor();
		double Area();
		bool HasRayIntersection(CRT::Ray& r, double tMin, double closestT, CRT::Point3 cameraPos);
	private:
		CRT::Point3 m_Vertices[3];
		CRT::Color m_Color;
		double t = 0.0;
		CRT::Point3 m_IntersectionPoint;
		CRT::Vector3 m_Normal;
	};

}
  
