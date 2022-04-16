#pragma once
#include "Vector3.h"

namespace CRT {
	class SceneSettings {
	public:
		SceneSettings(int width, int height, Vector3 color) : m_Width(width), m_Height(height), m_BackgroundColor(color) {}
		Color GetBackgroundColor();
		int GetHeight();
		int GetWidth();
	private:
		Vector3 m_BackgroundColor;
		int m_Width;
		int m_Height;
	};
}