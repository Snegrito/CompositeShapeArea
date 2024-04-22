#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H
#include "shape.h"

class CompositeShape : public Shape {
public:
	CompositeShape(int size);

	CompositeShape(const CompositeShape& copy);
	CompositeShape& operator=(const CompositeShape& right);
	CompositeShape(CompositeShape&& move) noexcept;
	CompositeShape& operator=(CompositeShape&& right) noexcept;
	~CompositeShape() override;
	
	double getArea() const override;
	rectangle_t getFrameRect() const override;
	void move(const point_t& aim) override;
	void move(double dx, double dy) override;
	void scale(double scaleCoefficient) override;
	const char* getName() const override;
	Shape* clone() const override;

	void push_back(Shape* shape);
	void push_back(const Shape& shape);

private:
	int currentMaxIndex_;
	int capacity_;
	Shape** figures_;
};

#endif