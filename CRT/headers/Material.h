#pragma once
#include "Vector3.h"

namespace CRT {
	enum class MaterialType {
		Diffuse,
		Reflective
	};
	
	/*class Material {
	public:
		Material() {
			m_Type = MaterialType::Diffuse;
			m_Albedo = CRT::Color(0, 0, 0);

		}
		Material(std::shared_ptr<MaterialType> type, std::shared_ptr<CRT::Color> color, bool smoothShading) : m_Type(type), m_Albedo(color), m_ShouldUseSmoothShading(smoothShading) {}
		std::shared_ptr<CRT::Color> GetColor();
		std::shared_ptr<MaterialType> GetMaterialType();
	private:
		std::shared_ptr<MaterialType> m_Type;
		std::shared_ptr<CRT::Color> m_Albedo;
		bool m_ShouldUseSmoothShading;
	};*/
	class Material {
	public:
		Material() {
			m_Type = MaterialType::Diffuse;
			m_Albedo = CRT::Color(0, 0, 0);
			m_ShouldUseSmoothShading = false;
		}
		Material(MaterialType& type, CRT::Color& color, bool smoothShading) : m_Type(type), m_Albedo(color), m_ShouldUseSmoothShading(smoothShading) {}
		CRT::Color GetColor();
		MaterialType GetMaterialType();
		bool GetSmoothShading();
	private:
		MaterialType m_Type;
		CRT::Color m_Albedo;
		bool m_ShouldUseSmoothShading;
	};

}