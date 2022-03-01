#include <format>
#include <iostream>
#include <fstream>
#include "vector3.h"
#include <cmath>

using namespace std;

void WriteColor(fstream& file, Color pixel_color) {

	file << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
	 
}

int main() {
	int width = 256;
	int height = 256;

	fstream myfile;
	myfile.open("image1.ppm", ios::out);
	 
	myfile << "P3 \n";
	myfile << width << " " << height << "\n";
	myfile << "255 \n";

	Color c;
	auto r = (double(1) / (2));
	//auto r = 1;
	for (int i = height; i > 0; i--) {
		for (int j = 0; j < width; j++) {
			auto x = (double(j - 128) / (width));
			auto y = (double(i - 128) / (height));
			 
			if (pow(x, 2) + pow(y, 2) < pow(r, 2) ) {
				c = Color(0.2, 0.5, 0.25);
			}
			else {
				c = Color(0.1, 0.1, 0.25);
			}
			
			WriteColor(myfile, c);
		}
	}


	myfile.close(); 

	return 0;
}

