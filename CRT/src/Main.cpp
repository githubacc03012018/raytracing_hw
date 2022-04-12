#include "RayTracer.h" 
 
int main() { 
	CRT::Scene scene;
	scene.LoadScene("scene3.crtscene");

	CRT::RayTracer tracer(scene);
	tracer.Render();

	std::cin.get();
}