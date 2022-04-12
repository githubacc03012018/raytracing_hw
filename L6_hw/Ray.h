#pragma once
class Ray {
public:
	Ray() {}
	Ray(const Point3& o, const Vector3& dir)
		: origin(o), direction(dir)
	{}

	Point3 GetAt(double t) {
		return origin + direction * t;
	}

	Point3 GetOrigin() {
		return origin;
	}

	Vector3 GetDirection() {
		return direction;
	}

private:
	Vector3 direction;
	Point3 origin;
};