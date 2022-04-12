#pragma once
#include "Common.h"
#include "World.h"
#include "Camera.h"

class Ray;
class Material;

class Lecture6_Renderer : public Renderer {
public:
	Lecture6_Renderer(int width, int height, Camera* camera) : width{ width }, height{ height }, cam{camera} {};
	void Render() override;
	Color CalculateColor(Ray& ray, World& world);
private:
	int width;
	int height;
	Camera* cam;
};