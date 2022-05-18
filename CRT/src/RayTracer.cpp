#include "RayTracer.h"
#include <string>
#include <chrono>

inline double Clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline void WriteColor(std::fstream& file, CRT::Color pixelColor, int samplesPerPixel) {
	auto scale = 1.0 / samplesPerPixel;

	file << static_cast<int>(255.999 * Clamp(pixelColor.x() * scale, 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.y() * scale, 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.z() * scale, 0.0, 0.999)) << '\n';
}

bool CRT::RayTracer::HasRayIntersection(CRT::Ray& ray, CRT::HitInformation& hitInfo) {
	bool hasHitAnything = false;
	auto world = m_Scene.get()->GetObjects();
	CRT::HitInformation temp;

	for (auto& object : world) {
		if (object.HasRayIntersection(ray, temp)) {
			hasHitAnything = true;
			hitInfo = temp;
		}
	}

	return hasHitAnything;
}

CRT::Vector3 ReflectRayDirection(const CRT::Vector3& I, const CRT::Vector3& N)
{
	return I - 2 * Dot(I, N) * N;
}

CRT::Color CRT::RayTracer::CalculateColor(CRT::Ray& ray, int depth) {
	CRT::Color finalColor;
	CRT::HitInformation hitInfo;

	auto lights = m_Scene.get()->GetLights();

	if (depth <= 0) {
		return Color(0, 0, 0);
	}

	if (HasRayIntersection(ray, hitInfo)) {
		auto matType = hitInfo.mat.GetMaterialType();

		if (matType == MaterialType::Diffuse) {
			for (const auto& light : lights) {
				// Calculate the direction of the light
				auto lightDirection = light.GetPosition() - hitInfo.point;
				auto lightDistance = lightDirection.Length();
				// Normalize light distance
				lightDirection.Normalize();

				// Calculate cos law and sphere area
				auto cosLaw = std::max<double>(0.0, Dot(lightDirection, hitInfo.normal));
				auto areaOfLightSphere = 4 * PI * lightDistance * lightDistance;

				// Add small portion of the triangle's normal as offset to fix shadow acne
				CRT::Ray shadowRay = CRT::Ray(hitInfo.point + hitInfo.normal * 0.00001, lightDirection);
				CRT::HitInformation tempHit;

				// If shadow ray hits an object, then the original point is in shadow, else calculate the color of the light
				finalColor += HasRayIntersection(shadowRay, tempHit) ? Color(0, 0, 0) : light.GetIntensity() * light.GetColor() * cosLaw / areaOfLightSphere * hitInfo.mat.GetColor();//(*hitInfo.mat->GetColor()); //Color(0, 0.2, 0.2)
			}
		}
		else {
			CRT::Vector3 reflectedDirection = ReflectRayDirection(ray.GetDirection(), hitInfo.normal);
			CRT::Ray reflectedRay = CRT::Ray(hitInfo.point, reflectedDirection.Normalize());
			finalColor += CalculateColor(reflectedRay, depth - 1) + hitInfo.mat.GetColor();
		}

		return finalColor;
	}

	// If nothing is hit return the scene's background color
	return m_Scene.get()->GetSceneSettings().get()->GetBackgroundColor();
}

void CRT::RayTracer::Render() {
	std::shared_ptr<CRT::SceneSettings> settings = m_Scene.get()->GetSceneSettings();

	int width = settings.get()->GetWidth();
	int height = settings.get()->GetHeight();
	int samplesPerPixel = 10;
	int maxDepth = 10;
	double aspectRatio = (double)width / height;

	// Angle of the camera's fov
	auto fov = 90.0;
	auto halfA = tan(fov / 2 * PI / 180);
	auto moveDir = CRT::Vector3(-0.2, 0, 0);
	double spinAmount = 5; //5 degrees spin

	auto start = std::chrono::high_resolution_clock::now();
	CRT::Scene scene = *m_Scene.get();

	for (int i = 0; i < 1; i++) {

		std::cout << "Working.." << std::endl;
		std::fstream myfile;
		std::string imageName = std::string("image_") + std::to_string(i) + std::string(".ppm");

		myfile.open(imageName, std::ios::out);
		myfile << "P3 \n";
		myfile << width << " " << height << "\n";
		myfile << "255 \n";

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				CRT::Color color;
				for (int s = 0; s < samplesPerPixel; s++) {
					auto pixelX = (2 * (j + RandomDouble(0,1) + 0.5) / (double)width - 1) * aspectRatio * halfA;
					auto pixelY = (1 - 2 * (i + RandomDouble(0,1) + 0.5) / (double)height) * halfA;
					CRT::Ray ray = scene.GetCamera().get()->GenerateRay(pixelX, pixelY);
					color += CalculateColor(ray, maxDepth);
				}

				WriteColor(myfile, color, samplesPerPixel);
			}

			std::cout << "Scanlines remaining..." << height - i << std::endl;
		}

		// Rotation by first panning the camera around the Y axis and then moving it in a constant direction.
		// Can be implemented as a single transformation matrix containing both transformations at once.

		/*scene.GetCamera().get()->Pan(spinAmount);
		scene.GetCamera().get()->Move(moveDir);*/
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Done. It took " << duration.count() * 1 / 1000 << " milliseconds" << std::endl;
}