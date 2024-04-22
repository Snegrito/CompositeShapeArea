#include "ring.h"

const double PI = 3.1415;

Ring::Ring(double centerX, double centerY, double outRadius, double inRadius) :
	centerX_(centerX),
	centerY_(centerY),
	outRadius_(outRadius),
	inRadius_(inRadius)
{
	if (outRadius <= inRadius) {
		throw std::invalid_argument("Outer radius is less than or equal to inner!\n");
	}
}

double Ring::getArea() const {
	return PI * (outRadius_ * outRadius_ - inRadius_ * inRadius_);
}

rectangle_t Ring::getFrameRect() const {
	rectangle_t rect{ 0 };
	rect.heigth = 2 * outRadius_;
	rect.width = 2 * outRadius_;
	rect.pos = {centerX_, centerY_};
	return rect;
}

void Ring::move(const point_t& aim) {
	centerX_ = aim.x;
	centerY_ = aim.y;
}

void Ring::move(double dx, double dy) {
	centerX_ += dx;
	centerY_ += dy;
}

void Ring::scale(double scaleCoefficient) {
	if (scaleCoefficient <= 0) {
		throw std::invalid_argument("Scale coefficient should be possitive!\n");
	}
	outRadius_ *= scaleCoefficient;
	inRadius_ *= scaleCoefficient;
}

const char* Ring::getName() const {
	return "RING";
}

Shape* Ring::clone() const {
	Shape* newRect = new Ring(*this);
	return newRect;
}