#include <iostream>
#include "Common.h"
#include "Camera.h"
#include "L6Renderer.h"
#include "Matrix33.h"

int main() {
	Vector3 origin = Vector3(0, 0, 0);
	Matrix33 m = { 1, 0, 0,
					0, 1, 0,
					0, 0, 1 };


	Camera cam = Camera(m, origin, 90.0);
	Renderer* r = new Lecture6_Renderer(1024, 768, &cam);
	r->Render();

	delete r;
	std::cin.get();
}
