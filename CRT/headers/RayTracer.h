#pragma once

#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"
#include "HitInformation.h"

namespace CRT {
	class RayTracer {
	public:
		RayTracer(std::shared_ptr<CRT::Scene> scene) : m_Scene(scene) {}
		void Render();
		CRT::Color CalculateColor(CRT::Ray& ray, int depth);
		bool HasRayIntersection(CRT::Ray& ray, CRT::HitInformation& hitInfo);
	private:
		std::shared_ptr<CRT::Scene> m_Scene;
	};
}