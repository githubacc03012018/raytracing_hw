#include "Object.h"

bool CRT::Object::HasRayIntersection(CRT::Ray& ray, CRT::HitInformation& hitInfo) {
	std::vector<CRT::Triangle> triangles = this->GetMesh();
	bool hasHitAnything = false;
	auto tempT = 0.0;
	
	double maxT = INFINITY;
	double minT = 0.001;
	
	for (auto& tri : triangles) {
		if (tri.HasRayIntersection(ray, this->GetMaterial().GetSmoothShading(), minT, maxT, tempT)) {
			hasHitAnything = true;
			maxT = tempT;

			hitInfo.mat = this->GetMaterial();
			hitInfo.t = tempT;
			hitInfo.point = tri.GetPointOfIntersection();
			hitInfo.normal = tri.GetNormal();
		}
	}

	return hasHitAnything;
}

std::vector<CRT::Triangle> CRT::Object::GetMesh() {
	return m_Mesh;
}

CRT::Material CRT::Object::GetMaterial() {
	return m_Material;
}