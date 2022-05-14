#include "Material.h"

std::shared_ptr<CRT::Color> CRT::Material::GetColor() {
	return m_Albedo;
}

std::shared_ptr<CRT::MaterialType> CRT::Material::GetMaterialType() {
	return m_Type;
}