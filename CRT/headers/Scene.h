#pragma once
#include <rapidjson/document.h>
#include "SceneSettings.h"
#include "Camera.h"
#include <fstream>
#include "iostream"
#include <rapidjson/istreamwrapper.h>
#include "Triangle.h"

namespace CRT {
	class Scene {
	public:
		void LoadScene(const std::string& sceneName);
		void LoadObjects(const rapidjson::Value::ConstArray& arr, const rapidjson::Value::ConstArray& indeces);
		void SetSceneSettings(CRT::SceneSettings& settings);
		CRT::SceneSettings GetSceneSettings();
		std::vector<CRT::Triangle> GetTriangles();
		CRT::Camera GetCamera();
		void SetCamera(CRT::Camera& cam);
	private:
		CRT::SceneSettings m_SceneSettings = {};
		CRT::Camera m_Camera = {};
		std::vector<CRT::Triangle> m_Objects;
	};
}