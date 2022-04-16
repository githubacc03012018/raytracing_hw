#include "Camera.h"
CRT::Matrix33 CRT::Camera::GetRotationMatrix() {
	return m_RotationMatrix;
}

double CRT::Camera::GetHalfAlfa() {
	auto fov = 90.0;
	return tan((fov / 2) * CRT::PI / 180);
}

CRT::Point3 CRT::Camera::GetPosition() {
	return m_Position;
}

CRT::Ray CRT::Camera::GenerateRay(double x, double y, CRT::Vector3 origin) {
	auto rayDirection = (m_RotationMatrix * CRT::Point3(x, y, -1)).Normalize();
	CRT::Ray r = CRT::Ray(origin, rayDirection);

	return r;
}

void CRT::Camera::Pan(double degrees) {
	const float rad = degrees * (PI / 180.f);
	Matrix33 rotateY = { cos(rad) ,0 , -sin(rad),
						0, 1, 0,
						sin(rad), 0, cos(rad)
	};

	m_RotationMatrix = m_RotationMatrix * rotateY;
}