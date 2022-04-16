#include "RayTracer.h"
#include <string>
#include <algorithm> 

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

bool CRT::RayTracer::HasRayIntersection(CRT::Ray& ray, CRT::Triangle& hitObject) {
	bool hasHitAnything = false;
	auto world = m_Scene.get()->GetTriangles();
	double closestT = INFINITY;
	auto tempT = 0.0;

	for (auto& triangle : world) {
		if (triangle.HasRayIntersection(ray, 0.001, closestT, tempT)) {
			hasHitAnything = true;
			closestT = tempT;
			hitObject = triangle;
		}
	}

	return hasHitAnything;
}

CRT::Color CRT::RayTracer::CalculateColor(CRT::Ray& ray) {
	CRT::Triangle hitObject;
	CRT::Color finalColor;
	auto lights = m_Scene.get()->GetLights();

	if (HasRayIntersection(ray, hitObject)) {
		for (const auto& light : lights) {

			auto lightDirection = m_Scene.get()->GetCamera()->GetRotationMatrix() * light.GetPosition() - hitObject.GetPointOfIntersection();
			auto lightDistance = lightDirection.Length();
			// Normalize light distance
			lightDirection.Normalize();

			// Calculate cos law and sphere area
			auto cosLaw = std::max<double>(0.0, Dot(lightDirection, hitObject.GetNormal()));
			auto areaOfLightSphere = 4 * PI * lightDistance * lightDistance;

			CRT::Ray shadowRay = CRT::Ray(hitObject.GetPointOfIntersection() + hitObject.GetNormal() * 0.00001, lightDirection);
			CRT::Triangle tempHit;

			// If shadow ray hits an object, then the original point is in shadow, else calculate the color of the light
			finalColor += HasRayIntersection(shadowRay, tempHit) ? Color(0, 0, 0) : Color(light.GetIntensity() * light.GetColor() * cosLaw / areaOfLightSphere) + hitObject.GetColor();	 
		}
		return finalColor;
	}

	return m_Scene.get()->GetSceneSettings().get()->GetBackgroundColor();
}

void CRT::RayTracer::Render() {
	std::shared_ptr<CRT::SceneSettings> settings = m_Scene.get()->GetSceneSettings();

	int width = settings.get()->GetWidth();
	int height = settings.get()->GetHeight();
	double aspectRatio = (double)width / height;

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
	CRT::Camera cam = *scene.GetCamera().get();

	auto transformedOrigin = cam.GetRotationMatrix() * cam.GetPosition();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			auto pixelX = (2 * (j + 0.5) / (double)width - 1) * aspectRatio * halfA;
			auto pixelY = (1 - 2 * (i + 0.5) / (double)height) * halfA;
			CRT::Ray ray = scene.GetCamera().get()->GenerateRay(pixelX, pixelY, transformedOrigin);
			WriteColor(myfile, CalculateColor(ray));
		}

		std::cout << "Scanlines remaining..." << height - i << std::endl;
	}

	std::cout << "Done!" << std::endl;
}