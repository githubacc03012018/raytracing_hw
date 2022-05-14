#pragma once
#include "Vector3.h"

namespace CRT {
	enum class MaterialType {
		Diffuse,
		Reflective
	};
	
	class Material {
	public:
		Material(std::shared_ptr<MaterialType> type, std::shared_ptr<CRT::Color> color, bool smoothShading) : m_Type(type), m_Albedo(color), m_ShouldUseSmoothShading(smoothShading) {}
		std::shared_ptr<CRT::Color> GetColor();
		std::shared_ptr<MaterialType> GetMaterialType();
	private:
		std::shared_ptr<MaterialType> m_Type;
		std::shared_ptr<CRT::Color> m_Albedo;
		bool m_ShouldUseSmoothShading;
	};
}