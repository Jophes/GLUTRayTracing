#pragma once

class Vec2 {
public:
	// Object properties
	double x, y;

	// Constructors
	Vec2();
	Vec2(double x, double y);

	// Operator overloads
	friend Vec2 operator*(Vec2 lhs, const double& rhs) {
		return Vec2(lhs.x * rhs, lhs.y * rhs);
	}
	friend Vec2 operator/(Vec2 lhs, const double& rhs) {
		return Vec2(lhs.x / rhs, lhs.y / rhs);
	}
	friend Vec2 operator+(Vec2 lhs, const Vec2& rhs) {
		return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
	}
	friend Vec2 operator-(Vec2 lhs, const Vec2& rhs) {
		return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	// Object methods
	double Magnitude();
	double Distance(Vec2 other);
	double DotProduct(Vec2 other);
	Vec2 Normalise();
	Vec2 Direction(Vec2 other);
	void Set(Vec2 newVal);
	void Set(double x, double y);
};

