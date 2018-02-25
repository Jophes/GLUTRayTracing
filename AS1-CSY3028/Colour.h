#pragma once

#include "Vec3.h"

class Colour {
public:
	// Object properties
	double r, g, b, a;

	// Constructor
	Colour(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0);
	Colour(Vec3 rgb, double alpha = 1.0);

	// Operator overloads
	friend Colour operator*(Colour lhs, const double& rhs) {
		return Colour(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);
	}
	friend Colour operator*(Colour lhs, const Colour& rhs) {
		return Colour(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
	}
	friend Colour operator/(Colour lhs, const double& rhs) {
		return Colour(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs);
	}
	friend Colour operator+(Colour lhs, const Colour& rhs) {
		return Colour(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
	}
	friend Colour operator-(Colour lhs, const Colour& rhs) {
		return Colour(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
	}

	// Clamp Recheck
	void Recheck();
	void Set(double red = 0.0, double green = 0.0, double blue = 0.0, double alpha = 1.0);
	void Set(Colour newVals);

	// Static Object Methods
	static Colour FromHSV(double hue, double saturation, double value);
	static Colour FromHSV(Vec3 hsv);
private:
	double Clamp(double value, double min, double max);
};