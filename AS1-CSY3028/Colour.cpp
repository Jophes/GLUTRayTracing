#include "Colour.h"

// Constructor
Colour::Colour(double red, double green, double blue, double alpha) {
	/*r = Clamp(red, 0, 1);
	g = Clamp(green, 0, 1);
	b = Clamp(blue, 0, 1);
	a = Clamp(alpha, 0, 1);*/
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

Colour::Colour(Vec3 rgb, double alpha) {
	/*r = Clamp(rgb.x, 0, 1);
	g = Clamp(rgb.y, 0, 1);
	b = Clamp(rgb.z, 0, 1);
	a = Clamp(alpha, 0, 1);*/
	r = rgb.x;
	g = rgb.y;
	b = rgb.z;
	a = alpha;
}

// Object methods
double Colour::Clamp(double value, double min, double max)  {
	return (value < min ? min : (value > max ? max : value));
}

void Colour::Recheck() {
	r = Clamp(r, 0, 1);
	g = Clamp(g, 0, 1);
	b = Clamp(b, 0, 1);
	a = Clamp(a, 0, 1);
}

void Colour::Set(double red, double green, double blue, double alpha) {
	r = Clamp(red, 0, 1);
	g = Clamp(green, 0, 1);
	b = Clamp(blue, 0, 1);
	a = Clamp(alpha, 0, 1);
}

void Colour::Set(Colour newVals) {
	r = Clamp(newVals.r, 0, 1);
	g = Clamp(newVals.g, 0, 1);
	b = Clamp(newVals.b, 0, 1);
	a = Clamp(newVals.a, 0, 1);
}

// Static Object methods
Colour Colour::FromHSV(double hue, double saturation, double value) {
	if (saturation <= 0.0) 
		return Colour(value, value, value);
	double hh = (hue >= 360.0 ? 0 : hue) / 60.0;
	long i = (long)hh;
	double ff = hh - i, p = value * (1.0 - saturation), q = value * (1.0 - (saturation * ff)), t = value * (1.0 - (saturation * (1.0 - ff)));
	switch (i) {
		case 0:
			return Colour(value, t, p);
		case 1:
			return Colour(q, value, p);
		case 2:
			return Colour(p, value, t);
		case 3:
			return Colour(p, q, value);
		case 4:
			return Colour(t, p, value);
		case 5:
		default:
			return Colour(value, p, q);
	}
	return Colour();
}

Colour Colour::FromHSV(Vec3 hsv) {
	return FromHSV(hsv.x, hsv.y, hsv.z);
}