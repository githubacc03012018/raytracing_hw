#include "Light.h"

int CRT::Light::GetIntensity() const {
	return m_Intensity;
}

CRT::Point3 CRT::Light::GetPosition() const {
	return m_Position;
}

CRT::Color CRT::Light::GetColor() const {
	return m_Color;
}