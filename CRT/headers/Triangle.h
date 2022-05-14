#pragma once
#include "Ray.h"
#include "HitInformation.h"

namespace CRT {
	class Triangle {
	public:
		// std::vector<int> triangleVertexIndeces, 
		Triangle(CRT::Point3 v0, CRT::Point3 v1, CRT::Point3 v2, CRT::Color c) : m_Vertices{ v0, v1, v2 }, m_Color{ c } {}
		Triangle() : m_Vertices{
			CRT::Point3{}, CRT::Point3{}, CRT::Point3{}
		} {}
		Point3 v0();
		Point3 v1();
		Point3 v2();
		Point3 GetPointOfIntersection();
		Point3 GetVertex(int i);
		Vector3 GetNormal();
		Color GetColor();
		double Area();
		double GetT();
		//bool HasRayIntersection(CRT::Ray& r, CRT::Point3 cameraPos, double& t);
		bool HasRayIntersection(CRT::Ray& r, double tMin, double closestT, double& t);
		//std::vector<int>  GetIndeces();
	private:
		CRT::Point3 m_Vertices[3];
		CRT::Color m_Color;
		//std::shared_ptr<double> t;
		
		double t;
		CRT::Point3 m_IntersectionPoint;
		CRT::Vector3 m_Normal;
		//std::vector<int> m_triangleVertexIndeces;
	};

}
  
