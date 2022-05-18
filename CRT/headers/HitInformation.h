#pragma once
#include "Vector3.h"
#include "Material.h"
  
namespace CRT {
	class HitInformation {
	public:
		double t;
		CRT::Vector3 normal;
		CRT::Vector3 point;
		CRT::Material mat;
	};
}