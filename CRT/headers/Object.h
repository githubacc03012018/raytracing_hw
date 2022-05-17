#pragma once
#include "Triangle.h"
#include "Material.h" 
#include "HitInformation.h"
#include "Vertex.h"

namespace CRT {
	class Object {
	public:
		Object(std::vector<CRT::Triangle>& triangles, CRT::Material& mat) : m_Mesh(triangles), m_Material(mat) {}
		Object();
		std::vector<CRT::Triangle> GetMesh();
		bool HasRayIntersection(CRT::Ray& ray, CRT::HitInformation& hitInfo);
		CRT::Material GetMaterial();
	private:
		std::vector<CRT::Triangle> m_Mesh;
		CRT::Material m_Material;
		std::vector<CRT::Point3> m_Vertices;
	};
}