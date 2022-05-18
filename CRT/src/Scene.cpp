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

	CRT::Vector3 vector = CRT::Vector3(arr[0].GetDouble(),
		arr[1].GetDouble(),
		arr[2].GetDouble());

	return vector;
}

inline CRT::Matrix33 LoadCameraMatrix(const rapidjson::Value::ConstArray& arr) {
	double values[9] = { 0 };
	for (int i = 0; i < arr.Size(); i++) {
		values[i] = arr[i].GetDouble();
	}

	CRT::Matrix33 m = CRT::Matrix33(values[0], values[1], values[2],
		values[3], values[4], values[5],
		values[6], values[7], values[8]);

	return m;
}

std::vector<CRT::Light> CRT::Scene::LoadLights(const rapidjson::Document& document) {
	std::vector<CRT::Light> lights;
	auto lightsArray = document.FindMember("lights")->value.GetArray();

	for (int i = 0; i < lightsArray.Size(); i++) {
		int intensity = lightsArray[i].FindMember("intensity")->value.GetInt();
		CRT::Point3 position = LoadVector(lightsArray[i].FindMember("position")->value.GetArray());

		CRT::Light light(intensity, position, Color(1, 1, 1)); //white light
		lights.push_back(light);
	}

	return lights;
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
	std::shared_ptr<CRT::SceneSettings> settings = std::make_shared<CRT::SceneSettings>(w, h, color);

	//Load materials
	auto mats = LoadMaterials(doc);

	// Load objects
	auto objects = LoadObject(doc, mats);

	// Load lights
	std::vector<CRT::Light> lights = LoadLights(doc);

	//Load camera
	const rapidjson::Value& cameraVal = doc.FindMember("camera")->value;
	auto matrixArray = cameraVal.FindMember("matrix")->value.GetArray();
	auto positionArray = cameraVal.FindMember("position")->value.GetArray();

	auto matrix = LoadCameraMatrix(matrixArray);
	auto position = LoadVector(positionArray);

	std::shared_ptr<CRT::Camera> cam = std::make_shared<CRT::Camera>(matrix, position);
	std::shared_ptr<CRT::Scene> scene = std::make_shared<CRT::Scene>(cam, settings, objects, lights);

	return scene;
}

std::shared_ptr<CRT::SceneSettings> CRT::Scene::GetSceneSettings() {
	return m_SceneSettings;
}

std::vector<CRT::Object> CRT::Scene::GetObjects() {
	return m_Objects;
}

std::shared_ptr<CRT::Camera> CRT::Scene::GetCamera() {
	return m_Camera;
}

std::vector<CRT::Light> CRT::Scene::GetLights() {
	return m_Lights;
}

std::vector<CRT::Material> CRT::Scene::LoadMaterials(const rapidjson::Document& document) {
	std::vector<CRT::Material> materials;
	auto materialsArray = document.FindMember("materials")->value.GetArray();
	for (int i = 0; i < materialsArray.Size(); i++) {
		std::string type = materialsArray[i].FindMember("type")->value.GetString();
		CRT::Vector3 color = LoadVector(materialsArray[i].FindMember("albedo")->value.GetArray());
		bool smoothShading = materialsArray[i].FindMember("smooth_shading")->value.GetBool();

		CRT::MaterialType matType = type == "diffuse" ? CRT::MaterialType::Diffuse : CRT::MaterialType::Reflective;
		materials.push_back(CRT::Material(matType, color, smoothShading));
	}

	return materials;

}

std::vector<CRT::Vertex> LoadVertexArray(const rapidjson::Value::ConstArray& arr) {
	std::vector<CRT::Vertex> verts;

	int counter = 0;
	double temp[3];
	while (counter < arr.Size()) {
		for (int i = 0; i < 3; i++) {
			temp[i] = arr[counter].GetDouble();
			counter++;
		}

		CRT::Vertex vert = CRT::Vertex{ CRT::Point3(temp[0], temp[1], temp[2]), CRT::Vector3(0,0,0) };
		verts.push_back(vert);
	}

	return verts;
}

std::vector<CRT::Object> CRT::Scene::LoadObject(const rapidjson::Document& document, const std::vector<CRT::Material>& mats) {
	const auto objectsArray = document.FindMember("objects")->value.GetArray();
	std::vector<CRT::Object> objects;
	 
	for (int i = 0; i < objectsArray.Size(); i++) {
		std::vector<CRT::Triangle> triangles;
		std::vector<std::vector<int>> face;
		const rapidjson::Value& indices = objectsArray[i].FindMember("triangles")->value;
		auto indexArray = indices.GetArray();
		int internalCounter = 0;

		// Load triangle indices as 'faces'
		std::vector<int> tempFaces;
		while (internalCounter < indices.Size()) {
			tempFaces.clear();
			for (int i = 0; i < 3; i++) {
				tempFaces.push_back(indexArray[internalCounter].GetInt());
				internalCounter++;
			}

			face.push_back(tempFaces);
		}

		// Load vertices
		const rapidjson::Value& vertices = objectsArray[i].FindMember("vertices")->value;
		auto vertexArray = LoadVertexArray(vertices.GetArray());

		// For every face calculate it's area and add it to the vertices' normal
		for (auto& f : face) {
			auto ia = f[0];
			auto ib = f[1];
			auto ic = f[2];
			const CRT::Vector3 e1 = vertexArray[ib].GetPosition() - vertexArray[ia].GetPosition();
			const CRT::Vector3 e2 = vertexArray[ic].GetPosition() - vertexArray[ib].GetPosition();
			const CRT::Vector3 no = cross(e1, e2);

			vertexArray[ia].m_Normal += no;
			vertexArray[ib].m_Normal += no;
			vertexArray[ic].m_Normal += no;

			CRT::Triangle t = CRT::Triangle{ vertexArray[ia], vertexArray[ib], vertexArray[ic] };
			triangles.push_back(t);
		} 

		// Normalize the normals
		for (int i = 0; i < vertexArray.size(); i++) {
			vertexArray[i].m_Normal = vertexArray[i].m_Normal.Normalize();
		}
		
		// Add the material to the object
		int materialIndex = objectsArray[i].FindMember("material_index")->value.GetInt();
		auto material = mats[materialIndex];

		CRT::Object obj = CRT::Object(triangles, material);
		objects.push_back(obj);
	}

	return objects;
}