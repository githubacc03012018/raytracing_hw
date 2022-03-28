#include "L5Renderer.h"

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	 
	Renderer* r = new Lecture5_Renderer(1024, 768);
	r->Render();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Done. It took " << duration.count() * 1 / 1000 << " milliseconds" << std::endl;
	
	delete r;
	std::cin.get();
}