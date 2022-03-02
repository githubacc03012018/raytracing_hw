#include <iostream>
#include <fstream>
#include "vector3.h"
#include <cmath>     
#include <stdlib.h> 
#include <random>

using namespace std;

void WriteColor(fstream& file, Color pixel_color) {

	file << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';

}

inline double random_double(double min, double max) {
	static uniform_real_distribution<double> distribution(min, max);
	static mt19937 generator;
	return distribution(generator);
}

void GenerateFirstImage(int width, int height) {
	fstream myfile;
	myfile.open("image1.ppm", ios::out);

	myfile << "P3 \n";
	myfile << width << " " << height << "\n";
	myfile << "255 \n";

	Color c;
	auto r = (double(1) / (4));

	for (int i = height; i > 0; i--) {
		for (int j = 0; j < width; j++) {
			auto x = (double(j - width / 2) / (width));
			auto y = (double(i - height / 2) / (height));

			if (pow(x, 2) + pow(y, 2) < pow(r, 2)) {
				c = Color(0.25, 0.25, random_double(0.5, 1.0));
			}
			else {
				c = Color(0.25, 0.75, 0.25);
			}

			WriteColor(myfile, c);
		}
	}


	myfile.close();
}

void GenerateSecondImage(int width, int height) {
	fstream myfile;
	myfile.open("image2.ppm", ios::out);

	myfile << "P3 \n";
	myfile << width << " " << height << "\n";
	myfile << "255 \n";

	for (int i = height; i > 0; i--) {
		for (int j = 0; j < width; j++) {
			Color c;
			if (i >= 576 && i <= 768) {
				if (j >= 0 && j <= 255) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), 0.0, 0.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 256 && j <= 512) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(0.0, random_double(0.0, 1.0), 0.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 512 && j <= 768) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(0.0, 0.0, random_double(0.0, 1.0)) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 768 && j <= 1024) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), random_double(0.0, 1.0), random_double(0.0, 1.0)) : Color(0.0, 0.0, 0.0);
				}
			}

			if (i >= 384 && i <= 576) {
				if (j >= 0 && j <= 255) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(0.0, random_double(0.0, 1.0), 0.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 256 && j <= 512) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), 0.0, 0.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 512 && j <= 768) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), random_double(0.0, 1.0), 1.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 768 && j <= 1024) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(1.0, random_double(0.0, 1.0), 0.0) : Color(0.0, 0.0, 0.0);
				}
			}

			if (i >= 192 && i <= 384) {
				if (j >= 0 && j <= 255) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(1.0, random_double(0.0, 1.0), 0.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 256 && j <= 512) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), 0.7, 0.25) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 512 && j <= 768) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), 1.0, random_double(0.0, 1.0)) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 768 && j <= 1024) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), random_double(0.0, 1.0), random_double(0.0, 1.0)) : Color(0.0, 0.0, 0.0);
				}
			}

			if (i >= 0 && i <= 192) {
				if (j >= 0 && j <= 255) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(1.0, 0.0, 1.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 256 && j <= 512) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(random_double(0.0, 1.0), random_double(0.0, 1.0), 0.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 512 && j <= 768) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(0.0, random_double(0.0, 1.0), 1.0) : Color(0.0, 0.0, 0.0);
				}
				if (j >= 768 && j <= 1024) {
					c = random_double(0.0, 1.0) >= 0.5 ? Color(1.0, 0.0, random_double(0.0, 1.0)) : Color(0.0, 0.0, 0.0);
				}
			}

			WriteColor(myfile, c);
		}
	}

	myfile.close();
}

int main() {

	GenerateFirstImage(1024, 1024);
	GenerateSecondImage(1024, 768);

	return 0;
}

