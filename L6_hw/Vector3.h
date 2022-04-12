#pragma once
#include <fstream>

double RandomDouble(double min, double max);

class Vector3 {
public:
	Vector3() : e{ 0,0,0 } {}
	Vector3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	Vector3& Normalize() {
		auto len = Length();
		e[0] * 1 / len;
		e[1] * 1 / len;
		e[2] * 1/  len;

		return *this;
	}

	double Length() {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}

	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }
	Vector3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;

		return *this;
	}

	Vector3& operator-=(const Vector3 otherVector) {
		e[0] -= otherVector.e[0];
		e[1] -= otherVector.e[1];
		e[2] -= otherVector.e[2];

		return *this;
	}

	Vector3& operator += (const Vector3 otherVector) {
		e[0] += otherVector.e[0];
		e[1] += otherVector.e[1];
		e[2] += otherVector.e[2];

		return *this;
	}

public:
	double e[3];
};

using Point3 = Vector3;   // 3D point
using Color = Vector3;    // RGB color

inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
	return out << "(" << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ")";
}

inline Vector3 cross(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline double Dot(const Vector3& u, const Vector3& v) {
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vector3 operator*(double t, const Vector3& v) {
	return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator*(const Vector3& v, double t) {
	return t * v;
}

inline Vector3 operator+(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3 Random() {
	return Vector3(RandomDouble(-1, 1), RandomDouble(-1, 1), RandomDouble(-1, 1));
}

inline Vector3 RandomInUnitSphere() {
	while (true) {
		auto p = Random();
		if (std::sqrt(p.Length()) >= 1) continue;
		return p;
	}
}
inline Vector3 RandomInHemisphere(const Vector3& normal) {
	auto in_unit_sphere = RandomInUnitSphere();
	if (Dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return in_unit_sphere * -1;
}
inline Vector3 RandomInUnitVector() {
	return RandomInUnitSphere().Normalize();
}
