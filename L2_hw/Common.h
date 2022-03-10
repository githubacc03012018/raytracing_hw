#pragma once
#include "vector3.h"
#include <fstream>
#include <chrono>
#include <iostream>

double Clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

void WriteColor(std::fstream& file, Color pixelColor) {
	file << static_cast<int>(255.999 * Clamp(pixelColor.x(), 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.y(), 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.z(), 0.0, 0.999)) << '\n';
}
 
class Ray {
private:
	Vector3 direction;
	Point3 origin;
public:
	Ray(const Point3& o, const Vector3& dir)
		: origin(o), direction(dir)
	{}

	Point3 GetAt(double t) {
		return origin + direction*t;
	}

	Vector3 GetDirection() {
		return this->direction;
	}
};

inline Color CalculateColor(Ray& r) {
	Vector3 unitDirection = r.GetDirection().Normalize();

	auto t = 0.5 * (unitDirection.y() + 1.0);
	return Color(0.2, 1.0, 0.5) * t + (1-t) * Color(0, 0.25, 0.75); //interpolate between the two colors
}