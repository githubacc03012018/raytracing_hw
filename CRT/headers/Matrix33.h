#pragma once
#include "Vector3.h"

namespace CRT {
	auto const PI = 3.14159265359;
	class Matrix33 {
	public:
		Matrix33() {
			data[0][0] = 0;
			data[0][1] = 0;
			data[0][2] = 0;

			data[1][0] = 0;
			data[1][1] = 0;
			data[1][2] = 0;

			data[2][0] = 0;
			data[2][1] = 0;
			data[2][2] = 0;	
		}

		Matrix33(double a, double b, double c, double d, double e, double f, double g, double h, double i) {

			data[0][0] = a;
			data[0][1] = b;
			data[0][2] = c;

			data[1][0] = d;
			data[1][1] = e;
			data[1][2] = f;

			data[2][0] = g;
			data[2][1] = h;
			data[2][2] = i;

		}
		Matrix33 operator*(const Matrix33 other) {
			Matrix33 res;
			for (int i = 0; i <= 2; i++) {
				for (int j = 0; j <= 2; j++) {
					res.data[i][j] = 0;
				}
			}

			for (int i = 0; i <= 2; ++i) {
				for (int j = 0; j <= 2; ++j) {
					for (int k = 0; k <= 2; ++k) {
						res.data[i][j] += data[i][k] * other.data[k][j];
					}
				}
			}

			return res;
		}

	public:
		double data[3][3];
	};


	inline Vector3 operator*(const Matrix33& m, const Vector3& v) {
		Vector3 res = Vector3(0, 0, 0);

		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				res.e[i] += m.data[i][j] * v.e[j];
			}
		}

		return res;
	}
}
