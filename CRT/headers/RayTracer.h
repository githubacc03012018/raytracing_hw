#pragma once

#include "Scene.h"
#include "Ray.h"
#include "Triangle.h"

namespace CRT {
	class RayTracer {
	public:
		RayTracer(CRT::Scene& scene);
		void Render();
		CRT::Color CalculateColor(CRT::Ray& ray);
	private:
		CRT::Scene m_Scene;
	};
}