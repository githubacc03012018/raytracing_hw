#pragma once
#include "Common.h"
#include "Ray.h"
#include "Matrix33.h"

class Camera {
public:
	Camera(Matrix33& rotationMatrix, Point3& origin, double fov) : position(origin), rotationMatrix(rotationMatrix), fov(fov) {}
	void Truck(Vector3& direction);
	Ray GetRay(double pixelX, double pixelY);
	Point3 GetPosition();
	double GetHalfAlfa();

	void pan(const float degrees) {
		const float rad = degrees * (PI / 180.f);
		Matrix33 rotateY = { cos(rad) ,0 , -sin(rad),
							0, 1, 0,
							sin(rad), 0, cos(rad)
		};


		rotationMatrix = rotationMatrix * rotateY;
	}
private:
	double fov;
	Point3& position;
	double halfAlfa;
	Matrix33& rotationMatrix;
};