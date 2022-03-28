#pragma once
#include "../L2_hw/Common.h"

class Lecture5_Renderer : public Renderer {
public:
	Lecture5_Renderer(int width, int height);
	void Render() override;

private:
	int width;
	int height;
};