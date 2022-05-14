#pragma once
#include "Triangle.h"
#include "Material.h" 
#include "HitInformation.h"
#include "Vertex.h"
 
namespace CRT {
	class Object {
	public:
		//Object(std::vector<CRT::Triangle>& triangles, CRT::Material& mat) : m_Mesh(triangles), m_Material(mat) {}
		Object(std::vector<CRT::Triangle>& triangles, std::shared_ptr<CRT::Material> mat) : m_Mesh(triangles), m_Material(mat) {
			/*for (int i = 0; i < triangles.size(); i++) {
				for (int j = 0; j < 3; j++) {
					auto pos = triangles[i].GetVertex(j);

					CRT::Vertex v(pos, CRT::Vector3(0,0,0));
					m_Vertices.push_back(v);
				}
			}*/
		}
		Object();
		std::vector<CRT::Triangle> GetMesh();
		bool HasRayIntersection(CRT::Ray& ray, CRT::HitInformation& hitInfo);
		std::shared_ptr<CRT::Material> GetMaterial();
		//std::vector<CRT::Vertex> GetAllVerticesForMesh();
	private:
		std::vector<CRT::Triangle> m_Mesh;
		std::shared_ptr<CRT::Material> m_Material;
		//std::vector<CRT::Vertex> m_Vertices;
	};
}