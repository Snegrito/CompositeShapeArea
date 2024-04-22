#ifndef SHAPE_H
#define SHAPE_H
#include "base-types.h"
#include <iostream>
#include <string>
#include <iomanip> 

class Shape {
public:
	virtual ~Shape() = default;
	virtual double getArea() const = 0;
	virtual rectangle_t getFrameRect() const = 0;
	virtual void move(const point_t& aim) = 0;
	virtual void move(double dx, double dy) = 0;
	virtual void scale(double scaleCoefficient) = 0;
	virtual const char* getName() const = 0;
	virtual Shape* clone() const = 0;
	bool operator<(const Shape& obj) {
		return this->getArea() < obj.getArea();
	}
    friend std::ostream& operator<<(std::ostream& out, const Shape * obj) {
		rectangle_t temp = obj->getFrameRect();
		double leftX = temp.pos.x - temp.width / 2;
		double leftY = temp.pos.y - temp.heigth / 2;
		double rightX = temp.pos.x + temp.width / 2;
		double rightY = temp.pos.y + temp.heigth / 2;
		return out << std::fixed << std::setprecision(2) << obj->getName() << ", Area: " << obj->getArea() << ", Rectangle coor: ("
			<< leftX << " ; " << leftY << ") (" << rightX << " ; " << rightY << ")";
	}
};

#endif 
