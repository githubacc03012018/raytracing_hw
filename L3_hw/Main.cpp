#include "../L2_hw/Common.h"

void GenerateImage() {
	auto aspectRatio = 16.0 / 9.0;
	int width = 1024;
	int height = width / aspectRatio;

	std::fstream myfile;
	myfile.open("image1.ppm", std::ios::out);
	myfile << "P3 \n";
	myfile << width << " " << height << "\n";
	myfile << "255 \n";

	std::cout << "Working..." << std::endl;

	Vector3 origin(0, 0, 0);
	auto fov = 90.0;
	auto const PI = 3.14159265359;
	auto halfAlfa = tan(fov / 2 * PI / 180);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			float Px = (2 * ((j + 0.5) / width) - 1) * halfAlfa * aspectRatio;
			float Py = (1 - 2 * ((i + 0.5) / height) * halfAlfa);

			Ray ray = Ray(origin, Point3(Px, Py, -1) - origin);
			WriteColor(myfile, CalculateColor(ray));
		}
	}

	myfile.close();
}

int main() {

	auto start = std::chrono::high_resolution_clock::now();
	GenerateImage();
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Done. It took " << duration.count() * 1 / 1000 << " milliseconds" << std::endl;
	std::cin.get();
}