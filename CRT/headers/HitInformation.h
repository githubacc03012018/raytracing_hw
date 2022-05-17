#pragma once
#include "Vector3.h"
#include "Material.h"
  
namespace CRT {
	class HitInformation {
	public:
		double t;
		CRT::Vector3 normal;
		//CRT::Object* object;
		CRT::Vector3 point;
		//std::shared_ptr<CRT::Material> mat;
		CRT::Material mat;
	};
}