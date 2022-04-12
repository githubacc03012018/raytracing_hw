#pragma once
#include <fstream>
#include <chrono>
#include <random>
#include <cmath>
#include "Vector3.h"

auto const PI = 3.14159265359;
class Camera;

inline double Clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline void WriteColor(std::fstream& file, Color pixelColor) {
	file << static_cast<int>(255.999 * Clamp(pixelColor.x(), 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.y(), 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * Clamp(pixelColor.z(), 0.0, 0.999)) << '\n';
}
 
inline double RandomDouble(double min, double max) {
	static std::uniform_real_distribution<double> distribution(min, max);
	static std::mt19937 generator;
	return distribution(generator);
}

class Renderer {
public:
	virtual void Render() = 0;
private:
	Camera* cam;
};