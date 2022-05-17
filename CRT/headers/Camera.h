#pragma once
#include "Matrix33.h"
#include "Ray.h"

namespace CRT {

	class Camera {
	public:
		Camera(CRT::Matrix33 matrix, CRT::Point3 pos) : m_RotationMatrix(matrix), m_Position(pos) {};
		CRT::Matrix33 GetRotationMatrix();
		CRT::Point3 GetPosition();
		double GetHalfAlfa();
		CRT::Ray GenerateRay(double x, double y);
		void Pan(double degrees);
		void Move(CRT::Vector3& moveDirection);
	private:
		 CRT::Matrix33 m_RotationMatrix;
		 CRT::Point3 m_Position;
	};
}