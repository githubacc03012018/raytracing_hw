#pragma once
#include "Vector3.h"

namespace CRT {
	class SceneSettings {
	public:
		SceneSettings();
		void SetBackgroundColor(Vector3& color);
		Color GetBackgroundColor();
		void SetWidthHeight(const int& width, const int& height);
		int GetHeight();
		int GetWidth();
	private:
		Vector3 m_BackgroundColor;
		int m_Width;
		int m_Height;
	};
}