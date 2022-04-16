#pragma once

#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"

namespace CRT {
	class RayTracer {
	public:
		RayTracer(std::shared_ptr<CRT::Scene> scene) : m_Scene(scene) {}
		void Render();
		CRT::Color CalculateColor(CRT::Ray& ray);
		bool HasRayIntersection(CRT::Ray& ray, CRT::Triangle& hitObject);
	private:
		std::shared_ptr<CRT::Scene> m_Scene;
	};
}