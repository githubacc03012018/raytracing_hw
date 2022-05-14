#include "Vertex.h"

CRT::Vector3 CRT::Vertex::GetNormal() {
	return m_Normal;
};

void CRT::Vertex::SetNormal(CRT::Vector3 normal) {
	m_Normal = normal;
}