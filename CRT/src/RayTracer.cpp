#include "RayTracer.h"
#include <string>
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

	auto world = m_Scene.get()->GetTriangles();
	for (std::vector<CRT::Triangle>::iterator it = world.begin(); it != world.end(); ++it) {
		if (it->HasRayIntersection(ray, 0.001, closestT, m_Scene.get()->GetCamera().get()->GetPosition())) {
			closestT = it->GetT();
			hitObject = *it;
			hasHitAnything = true;
		}
	}

	if (hasHitAnything) {
		return hitObject.GetColor();
	}

	return m_Scene.get()->GetSceneSettings().get()->GetBackgroundColor();

}

void CRT::RayTracer::Render() {
	std::shared_ptr<CRT::SceneSettings> settings = m_Scene.get()->GetSceneSettings();

	int width = settings.get()->GetWidth();
	int height = settings.get()->GetHeight();
	double aspectRatio = width / height;

	auto fov = 90.0;
	auto halfA = tan(fov / 2 * PI / 180);

	std::cout << "Working.." << std::endl;

	std::fstream myfile;
	std::string imageName = std::string("image.ppm");

	myfile.open(imageName, std::ios::out);
	myfile << "P3 \n";
	myfile << width << " " << height << "\n";
	myfile << "255 \n";

	CRT::Scene scene = *m_Scene.get();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			auto pixelX = (2 * ((j + 0.5) / width) - 1) * halfA * aspectRatio;
			auto pixelY = (1 - 2 * ((i + 0.5) / height) * aspectRatio);
			CRT::Ray ray = scene.GetCamera().get()->GetRay(pixelX, pixelY);
			WriteColor(myfile, CalculateColor(ray));
		}

		std::cout << "Scanlines remaining..." << height - i << std::endl;
	}

	std::cout << "Done!" << std::endl;
}