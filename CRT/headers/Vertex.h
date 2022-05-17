#pragma once
#include "Vector3.h"

namespace CRT {
	class Vertex {
	public:
		Vertex() { m_Position = CRT::Point3(0, 0, 0); m_Normal = CRT::Vector3(0, 0, 0); }
		Vertex(CRT::Point3 position, CRT::Vector3 normal) : m_Position(position), m_Normal(normal) {}
		CRT::Vector3 GetNormal();
		void SetNormal(CRT::Vector3 normal);
		CRT::Point3 GetPosition();
		CRT::Vector3 m_Normal; 
		CRT::Point3 m_Position;
	private:
		//CRT::Point3 m_Position;
		//CRT::Vector3 m_Normal;
	};

	inline std::ostream& operator<<(std::ostream& out, const CRT::Vertex& v) {
		return out << "(" << v.m_Position.e[0] << ' ' << v.m_Position.e[1] << ' ' << v.m_Position.e[2] << ")";
	}
	inline Vertex operator-(const Vertex& u, const Vertex& v) {
		return Vertex(CRT::Point3(u.m_Position.e[0] - v.m_Position.e[0], u.m_Position.e[1] - v.m_Position.e[1], u.m_Position.e[2] - v.m_Position.e[2]), 
					CRT::Vector3(u.m_Normal - v.m_Normal)
				);
	}

	inline Vertex operator-(const CRT::Point3& u, const Vertex& v) {
		return Vertex(CRT::Point3(u.e[0] - v.m_Position.e[0], u.e[1] - v.m_Position.e[1], u.e[2] - v.m_Position.e[2]),
			CRT::Vector3(v.m_Normal)
		);
	}

	inline Vertex operator-(const Vertex& v, const CRT::Point3& u) {
		return Vertex(CRT::Point3(u.e[0] - v.m_Position.e[0], u.e[1] - v.m_Position.e[1], u.e[2] - v.m_Position.e[2]),
			CRT::Vector3(v.m_Normal)
		);
	}
}