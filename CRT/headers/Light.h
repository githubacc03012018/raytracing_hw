#pragma once
#include "Vector3.h"

namespace CRT {
	class Light {
	public:
		Light(int intensity, CRT::Point3 position, CRT::Color color) : m_Position(position), m_Intensity(intensity), m_Color(color) {}
		int GetIntensity() const;
		CRT::Point3 GetPosition() const;
		CRT::Color GetColor() const;
	private:
		int m_Intensity;
		CRT::Point3 m_Position;
		CRT::Color m_Color;
	};
}