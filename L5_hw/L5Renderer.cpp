#include "L5Renderer.h"
#include <vector>
#include "../L2_hw/Triangle.h"
#include "World.h" 
 
Color CalculateColor(Ray& r, World& w) {
	Triangle hitObject;
	if (w.HasRayIntersection(r, hitObject)) {
		return hitObject.GetColor();
	}
	else {
		Vector3 unitDirection = r.GetDirection().Normalize();

		auto t = 0.5 * (unitDirection.y() + 1.0);
		return Color(0.2, 1.0, 0.5) * t + (1 - t) * Color(0, 0.25, 0.75); //interpolate between the two colors
	}
}
Lecture5_Renderer::Lecture5_Renderer(int width, int height) : width(width), height(height) { }

void Lecture5_Renderer::Render() {
 
	double aspectRatio = width / height;
	std::fstream myfile;
	myfile.open("image1.ppm", std::ios::out);
	myfile << "P3 \n";
	myfile << width << " " << height << "\n";
	myfile << "255 \n";

	std::cout << "Working..." << std::endl;

	Vector3 origin(0, 0, 0);
	auto const fov = 90.0;
	auto const PI = 3.14159265359;
	auto halfAlfa = tan(fov / 2 * PI / 180);
	  
	World w;
	/*w.Add(Triangle(Point3(-1.75, -1.75, -3), Point3(1.75, -1.75, -3), Point3(0, 1.75, -3), Color(0.5, 0.2, 0)));*/
	//white
	w.Add(Triangle(Point3(-0.5, 1, -3), Point3(0.5, 1, -3), Point3(0, 2, -3), Color(1, 1, 1)));
	w.Add(Triangle(Point3(0.5, 1, -3), Point3(1, 2, -3), Point3(0, 2, -3), Color(1, 1, 1)));
	w.Add(Triangle(Point3(0.5, 1, -3), Point3(1.5, 1, -3), Point3(1, 2, -3), Color(1, 1, 1)));
	w.Add(Triangle(Point3(1.5, 1, -3), Point3(2, 2, -3), Point3(1, 2, -3), Color(1, 1, 1)));
	//green
	w.Add(Triangle(Point3(0,0, -3), Point3(1, 0, -3), Point3(0.5,1, -3), Color(0, 1, 0)));
	w.Add(Triangle(Point3(1, 0, -3), Point3(1.5, 1, -3), Point3(0.5, 1, -3), Color(0, 1, 0)));
	w.Add(Triangle(Point3(0, 0, -3), Point3(0.5, 1, -3), Point3(-0.5, 1, -3), Color(0, 1, 0)));
	w.Add(Triangle(Point3(-1, 0, -3), Point3(0, 0, -3), Point3(-0.5, 1, -3), Color(0, 1, 0)));
	//red
	w.Add(Triangle(Point3(-0.5, -1, -3), Point3(0.5, -1, -3), Point3(0, 0, -3), Color(1, 0, 0)));
	w.Add(Triangle(Point3(0.5, -1, -3), Point3(1, 0, -3), Point3(0, 0, -3), Color(1, 0, 0)));
	w.Add(Triangle(Point3(-0.5, -1, -3), Point3(0, 0, -3), Point3(-1, 0, -3), Color(1, 0, 0)));
	w.Add(Triangle(Point3(-1.5, -1, -3), Point3(-0.5, -1, -3), Point3(-1, 0, -3), Color(1, 0, 0)));
	 
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {	
			auto pixelX = (2 * ((j + 0.5) / width) - 1) * halfAlfa * aspectRatio;
			auto pixelY = (1 - 2 * ((i + 0.5) / height) * aspectRatio);
			Ray ray = Ray(origin, Point3(pixelX, pixelY, -1) - origin);

			WriteColor(myfile, CalculateColor(ray, w));
		}
	}

	std::cout << "Done..." << std::endl;
}