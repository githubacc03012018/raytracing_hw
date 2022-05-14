#include "RayTracer.h" 

int main() {
	CRT::Scene scene;
	std::shared_ptr<CRT::Scene> loadedScene = scene.LoadScene("scene1.crtscene");

	CRT::RayTracer tracer(loadedScene);
	tracer.Render();

	std::cin.get();
}