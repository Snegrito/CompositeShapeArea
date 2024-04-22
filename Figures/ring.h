#ifndef RING_H
#define RING_H
#include "shape.h"

class Ring : public Shape {
public:
	Ring(double centerX, double centerY, double outRadius, double inRadius);

	double getArea() const override;
	rectangle_t getFrameRect() const override;
	void move(const point_t& aim) override;
	void move(double dx, double dy) override;
	void scale(double scaleCoefficient) override;
	const char* getName() const override;
	Shape* clone() const override;
private:
	double centerX_;
	double centerY_;
	double outRadius_;
	double inRadius_;
};

#endif
