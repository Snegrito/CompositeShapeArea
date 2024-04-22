#include "rectangle.h"

Rectangle::Rectangle(double leftBottomX, double leftBottomY, double rightUpperX, double rightUpperY) :
	leftBottomX_(leftBottomX),
	leftBottomY_(leftBottomY),
	rightUpperX_(rightUpperX),
	rightUpperY_(rightUpperY)
{
	if (rightUpperX_ <= leftBottomX_ || rightUpperY_ <= leftBottomY_) {
		throw std::invalid_argument("Invalid coordinates!\n");
	}
}

point_t Rectangle::getCenter() const {
	point_t center{0};
	center.x = (rightUpperX_ + leftBottomX_) / 2.0;
	center.y = (rightUpperY_ + leftBottomY_) / 2.0;
	return center;
}

double Rectangle::getArea() const {
	return (rightUpperX_ - leftBottomX_) * (rightUpperY_ - leftBottomY_);
}

rectangle_t Rectangle::getFrameRect() const {
	rectangle_t rect{0};
	rect.heigth = rightUpperY_ - leftBottomY_;
	rect.width = rightUpperX_ - leftBottomX_;
	rect.pos = getCenter();
	return rect;
}

void Rectangle::move(const point_t& aim) {
	point_t center = getCenter();
	rightUpperX_ += (aim.x - center.x);
	rightUpperY_ += (aim.y - center.y);
	leftBottomX_ += (aim.x - center.x);
	leftBottomY_ += (aim.y - center.y);
}

void Rectangle::move(double dx, double dy) {
	rightUpperX_ += dx;
	rightUpperY_ += dy;
	leftBottomX_ += dx;
	leftBottomY_ += dy;
}

void Rectangle::scale(double scaleCoefficient) {
	if (scaleCoefficient <= 0) {
		throw std::invalid_argument("Scale coefficient should be possitive!\n");
	}
	point_t center = getCenter();
	rightUpperX_ = center.x + (rightUpperX_ - center.x) * scaleCoefficient;
	rightUpperY_ = center.y + (rightUpperY_ - center.y) * scaleCoefficient;
	leftBottomX_ = center.x + (leftBottomX_ - center.x) * scaleCoefficient;
	leftBottomY_ = center.y + (leftBottomY_ - center.y) * scaleCoefficient;

}

const char* Rectangle::getName() const {
	return "RECTANGLE";
}

Shape* Rectangle::clone() const {
	Shape* newRect = new Rectangle(*this);
	return newRect;
}
