#include "L6Renderer.h"
#include <string>
#include <iostream>

void Lecture6_Renderer::Render() {
	double aspectRatio = width / height;

	World w;
	w.Add(Triangle(Point3(-0.5, 1, -3), Point3(0.5, 1, -3), Point3(0, 2, -3), Color(0, 0, 1)));

	cam->pan(20);
	Vector3 cameraMoveDirection = Vector3(0.1, 0, 0);
	float rotateStep = 5;
	float initialAngle = 0.0;
	for (int i = 1; i <= 11; i++) {
		std::fstream myfile;
		std::string imageName = std::string("image") + std::to_string(i) + std::string(".ppm");

		myfile.open(imageName, std::ios::out);
		myfile << "P3 \n";
		myfile << width << " " << height << "\n";
		myfile << "255 \n";

		std::cout << "Working..." << std::endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				auto pixelX = (2 * ((j + 0.5) / width) - 1) * cam->GetHalfAlfa() * aspectRatio;
				auto pixelY = (1 - 2 * ((i + 0.5) / height) * aspectRatio);

				Ray ray = cam->GetRay(pixelX, pixelY);
				WriteColor(myfile, CalculateColor(ray, w));
			}
		}

		//initialAngle += rotateStep;*/
		cam->Truck(cameraMoveDirection);

		if (cam->GetPosition().x() >= 0.9888 || cam->GetPosition().x() <= 0.001) {
			cameraMoveDirection *= -1;
		}


	}


	std::cout << "Done..." << std::endl;
}

Color Lecture6_Renderer::CalculateColor(Ray& ray, World& world) {
	Triangle hitObject;
	if (world.HasIntersection(ray, hitObject, cam->GetPosition())) {
		return hitObject.GetColor();
	}

	Vector3 unitDirection = ray.GetDirection().Normalize();

	auto t = 0.5 * (unitDirection.y() + 1.0);
	return Color(0.2, 1.0, 0.5) * t + (1 - t) * Color(0, 0.25, 0.75);
}