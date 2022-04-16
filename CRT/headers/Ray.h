#pragma once
#include "Vector3.h"

namespace CRT {
	class Ray {
	public :
		Ray(CRT::Point3 origin, CRT::Vector3 direction) : m_Origin(origin), m_Direction(direction) {}
		CRT::Point3 GetAt(double t);
		CRT::Vector3 GetDirection();
		CRT::Vector3 GetOrigin();
	private:
		CRT::Point3 m_Origin;
		CRT::Vector3 m_Direction;
	};
}