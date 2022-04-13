#include "Scene.h"
#include "Triangle.h"

inline rapidjson::Document LoadDocument(const std::string& filename) {
	std::ifstream ifs(filename);
	assert(ifs.is_open());

	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.HasParseError()) {
		std::cout << "Error : " << doc.GetParseError() << '\n';
		std::cout << "Offset : " << doc.GetErrorOffset() << '\n';
	}
	assert(doc.IsObject());
	return doc;
}

inline CRT::Vector3 LoadVector(const rapidjson::Value::ConstArray& arr) {
	assert(arr.Size() == 3);

	CRT::Vector3 vector(arr[0].GetDouble(),
		arr[1].GetDouble(),
		arr[2].GetDouble());

	return vector;
}

inline std::shared_ptr<CRT::Matrix33> LoadCameraMatrix(const rapidjson::Value::ConstArray& arr) {
	double values[9] = { 0 };
	for (int i = 0; i < arr.Size(); i++) {
		values[i] = arr[i].GetDouble();
	}

	std::shared_ptr<CRT::Matrix33> m = std::make_shared<CRT::Matrix33>(values[0], values[1], values[2],
																		values[3], values[4], values[5],
																		values[6], values[7], values[8]);
	
	return m;
}

std::vector<CRT::Triangle> CRT::Scene::LoadObjects(const rapidjson::Value::ConstArray& arr, const rapidjson::Value::ConstArray& indeces) {
	std::vector<CRT::Vector3> vertices;
	std::vector<CRT::Triangle> objects;

	int vertexCounter = 0;
	int internalCounter = 0;

	// Load vertex points
	while (internalCounter < arr.Size()) {
		double vertexCoordinates[3];
		for (int i = 0; i < 3; i++) {
			auto vertex = arr[internalCounter].GetDouble();
			vertexCoordinates[i] = vertex;
			internalCounter++;
		}


		CRT::Point3 point = CRT::Point3(vertexCoordinates[0], vertexCoordinates[1], vertexCoordinates[2]);
		vertices.push_back(point);
	}

	//Load triangles
	internalCounter = 0;
	while (internalCounter < indeces.Size()) {
		CRT::Point3 points[3];
		for (int i = 0; i < 3; i++) {
			int index = indeces[internalCounter].GetInt();
			auto v = vertices[index];
			points[i] = v;
			internalCounter++;
		}

		CRT::Triangle t = CRT::Triangle(points[0], points[1], points[2], CRT::Color(RandomDouble(0, 1), RandomDouble(0, 1), RandomDouble(0, 1)));
		objects.push_back(t);
	}

	return objects;
}
 

std::shared_ptr<CRT::Scene> CRT::Scene::LoadScene(const std::string& sceneName) {
	rapidjson::Document doc = LoadDocument(sceneName);

	// Load settings
	const rapidjson::Value& settingsVal = doc.FindMember("settings")->value;
	const rapidjson::Value& backgroundColor = settingsVal.FindMember("background_color")->value;

	const rapidjson::Value& widhtHeight = settingsVal.FindMember("image_settings")->value;
	auto w = widhtHeight.FindMember("width")->value.GetInt();
	auto h = widhtHeight.FindMember("height")->value.GetInt();

	auto color = LoadVector(backgroundColor.GetArray());
	std::shared_ptr<CRT::SceneSettings> settings = std::make_shared<CRT::SceneSettings>(w,h,color);
	
	//Load objects
	auto objects = doc.FindMember("objects")->value.GetArray();

	const rapidjson::Value& vertices = objects[0].FindMember("vertices")->value;
	const rapidjson::Value& indeces = objects[0].FindMember("triangles")->value;
	std::vector<CRT::Triangle> triangles = LoadObjects(vertices.GetArray(), indeces.GetArray());

	//Load camera
	const rapidjson::Value& cameraVal = doc.FindMember("camera")->value;
	auto matrixArray = cameraVal.FindMember("matrix")->value.GetArray();
	auto positionArray = cameraVal.FindMember("position")->value.GetArray();

	auto matrix = LoadCameraMatrix(matrixArray);
	auto position = LoadVector(positionArray);
	 
	std::shared_ptr<CRT::Camera> cam = std::make_shared<CRT::Camera>(matrix, position);
	std::shared_ptr<CRT::Scene> scene = std::make_shared<CRT::Scene>(cam, settings, triangles);

	return scene;
}

std::shared_ptr<CRT::SceneSettings> CRT::Scene::GetSceneSettings() {
	return m_SceneSettings;
}

std::vector<CRT::Triangle> CRT::Scene::GetTriangles() {
	return m_Objects;
}

std::shared_ptr<CRT::Camera> CRT::Scene::GetCamera() {
	return m_Camera;
}