#include "Camera.h"
#include "Matrix33.h"
 
Ray Camera::GetRay(double pixelX, double pixelY) {
	auto dir = Point3(pixelX, pixelY, -1) - this->GetPosition();
	Ray ray = Ray(this->GetPosition(), rotationMatrix * dir);
	return ray;
}

void Camera::Truck(Vector3& direction) {
	position = rotationMatrix * position + direction;
}
Vector3 Camera::GetPosition() {
	return position;
}

double Camera::GetHalfAlfa() {
	halfAlfa = tan(fov / 2 * PI / 180);
	return halfAlfa;
}