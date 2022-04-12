#include "RayTracer.h"

CRT::RayTracer::RayTracer(CRT::Scene& scene) {
	m_Scene = scene;
}

inline double Clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}


inline void WriteColor(std::fstream& file, CRT::Color pixelColor) {
	file << static_cast<int>(255.999 * Clamp(pixelColor.x(), 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.y(), 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.z(), 0.0, 0.999)) << '\n';
}


CRT::Color CRT::RayTracer::CalculateColor(CRT::Ray& ray) {
	double closestT = INFINITY;
	CRT::Triangle hitObject;
	bool hasHitAnything = false;
	auto world = m_Scene.GetTriangles();
	for (std::vector<CRT::Triangle>::iterator it = world.begin(); it != world.end(); ++it) {
		if (it->HasRayIntersection(ray, closestT, m_Scene.GetCamera().GetPosition())) {
			closestT = it->GetT();
			hitObject = *it;
			hasHitAnything = true;
		}
	}

	if (hasHitAnything) {
		return hitObject.GetColor();
	}

	return m_Scene.GetSceneSettings().GetBackgroundColor();
	 
}

void CRT::RayTracer::Render() {
	CRT::SceneSettings settings = m_Scene.GetSceneSettings();

	int width = settings.GetWidth();
	int height = settings.GetHeight();
	double aspectRatio = width / height;
	
	std::fstream myfile;
	std::string imageName = "image.ppm";

	myfile.open(imageName, std::ios::out);
	myfile << "P3 \n";
	myfile << width << " " << height << "\n";
	myfile << "255 \n";

	std::cout << "Working.." << std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			 
			auto pixelX = (2 * ((j + 0.5) / width) - 1) * m_Scene.GetCamera().GetHalfAlfa() * aspectRatio;
			auto pixelY = (1 - 2 * ((i + 0.5) / height) * aspectRatio);
			CRT::Ray ray = m_Scene.GetCamera().GetRay(pixelX, pixelY);
			WriteColor(myfile, CalculateColor(ray));
		}

		std::cout << "Scanlines remaining..." << height - i << std::endl;
	}


	std::cout << "Done!" << std::endl;
}