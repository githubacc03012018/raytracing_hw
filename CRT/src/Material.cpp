#include "Material.h"

//std::shared_ptr<CRT::Color> CRT::Material::GetColor() {
//	return m_Albedo;
//}
//
//std::shared_ptr<CRT::MaterialType> CRT::Material::GetMaterialType() {
//	return m_Type;
//}

CRT::Color CRT::Material::GetColor() {
	return m_Albedo;
}

CRT::MaterialType CRT::Material::GetMaterialType() {
	return m_Type;
}

bool CRT::Material::GetSmoothShading() {
	return m_ShouldUseSmoothShading;
}