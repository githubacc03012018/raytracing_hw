#include "SceneSettings.h"

//CRT::SceneSettings::SceneSettings() : m_Width(0), m_Height(0) {}
void CRT::SceneSettings::SetBackgroundColor(Vector3& color) {
	m_BackgroundColor = color;
}
void CRT::SceneSettings::SetWidthHeight(const int& width, const int& height) {
	m_Width = width;
	m_Height = height;
}

int CRT::SceneSettings::GetWidth() {
	return m_Width;
}

int CRT::SceneSettings::GetHeight() {
	return m_Height;
}

CRT::Color CRT::SceneSettings::GetBackgroundColor() {
	return m_BackgroundColor;
}