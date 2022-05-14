#pragma once
#include "Vector3.h"

namespace CRT {
	class Vertex {
	public:
		Vertex(CRT::Point3 position, CRT::Vector3 normal) : m_Position(position), m_Normal(normal) {}
		CRT::Vector3 GetNormal();
		void SetNormal(CRT::Vector3 normal);
	private:
		CRT::Point3 m_Position;
		CRT::Vector3 m_Normal;
	};
}