#include "Vec2.h"
#include <cmath>

// Constructors
Vec2::Vec2() {
	x = 0;
	y = 0;
}

Vec2::Vec2(double _x, double _y) {
	x = _x;
	y = _y;
}

// Object methods
double Vec2::Magnitude() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

double Vec2::Distance(Vec2 other) {
	return ((*this) - other).Magnitude();
}

double Vec2::DotProduct(Vec2 other) {
	return x * other.x + y * other.y;
}

Vec2 Vec2::Normalise()  {
	return (*this) / Magnitude();
}

Vec2 Vec2::Direction(Vec2 other) {
	return (other - (*this)).Normalise();
}

void Vec2::Set(Vec2 newVal) {
	x = newVal.x;
	y = newVal.y;
}

void Vec2::Set(double _x, double _y) {
	x = _x;
	y = _y;
}