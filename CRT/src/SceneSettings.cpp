#include "SceneSettings.h"
 
int CRT::SceneSettings::GetWidth() {
	return m_Width;
}

int CRT::SceneSettings::GetHeight() {
	return m_Height;
}

CRT::Color CRT::SceneSettings::GetBackgroundColor() {
	return m_BackgroundColor;
}