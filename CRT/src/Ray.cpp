#include "Ray.h"

CRT::Point3 CRT::Ray::GetAt(double t) {
	return m_Origin + m_Direction * t;
}

CRT::Vector3 CRT::Ray::GetDirection() {
	return m_Direction;
}

CRT::Point3 CRT::Ray::GetOrigin() {
	return m_Origin;
}