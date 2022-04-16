#pragma once
#include <rapidjson/document.h>
#include "SceneSettings.h"
#include "Camera.h"
#include <fstream>
#include "iostream"
#include <rapidjson/istreamwrapper.h>
#include "Triangle.h"
#include "Light.h"

namespace CRT {
	class Scene {
	public:
		Scene(std::shared_ptr<CRT::Camera> camera, std::shared_ptr<CRT::SceneSettings> settings, 
						std::vector<CRT::Triangle> objects, std::vector<CRT::Light> lights) : 
			m_Lights(lights),
			m_Camera(camera), 
			m_SceneSettings(settings), m_Objects(objects) {}
		Scene() {}
		std::vector<CRT::Triangle> LoadObjects(const rapidjson::Document& doc);
		std::shared_ptr<CRT::Scene> LoadScene(const std::string& sceneName);
		std::vector<CRT::Triangle> LoadTriangles(const rapidjson::Value::ConstArray& arr, const rapidjson::Value::ConstArray& indeces);
		std::vector<CRT::Triangle> GetTriangles();
		std::shared_ptr<CRT::SceneSettings> GetSceneSettings();
		std::shared_ptr<CRT::Camera> GetCamera();
		std::vector<CRT::Light> GetLights();
		std::vector<CRT::Light> LoadLights(const rapidjson::Document& doc);
	private:
		std::shared_ptr<CRT::SceneSettings> m_SceneSettings;
		std::shared_ptr<CRT::Camera> m_Camera;
		std::vector<CRT::Triangle> m_Objects;
		std::vector<CRT::Light> m_Lights;
	};
}