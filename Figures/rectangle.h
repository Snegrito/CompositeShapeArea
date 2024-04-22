#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape {
public:
	Rectangle(double leftBottomX, double leftBottomY, double rightUpperX, double rightUpperY);

	double getArea() const override;
	rectangle_t getFrameRect() const override;
	void move(const point_t& aim) override;
	void move(double dx, double dy) override;
	void scale(double scaleCoefficient) override;
	const char* getName() const override;
	Shape* clone() const override;
private:
	double leftBottomX_;
	double leftBottomY_;
	double rightUpperX_;
	double rightUpperY_;

	point_t getCenter() const;
};

#endif
