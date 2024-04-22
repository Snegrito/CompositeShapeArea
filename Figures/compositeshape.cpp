#include "compositeshape.h"

CompositeShape::CompositeShape(int size) :
	capacity_(size),
	currentMaxIndex_(0),
	figures_(nullptr)
{	
	if (capacity_ <= 0) {
		throw std::invalid_argument("Size of composite shape must be positive!\n");
	}
	figures_ = new Shape * [capacity_];
}

CompositeShape::CompositeShape(const CompositeShape& copy) :
	currentMaxIndex_(copy.currentMaxIndex_),
	capacity_(copy.capacity_),
	figures_(new Shape*[copy.capacity_])
{
	for (int i = 0; i < currentMaxIndex_; ++i) {
		figures_[i] = copy.figures_[i]->clone();
	}
}

CompositeShape& CompositeShape::operator=(const CompositeShape& right)
{
	if (this != &right) {
		Shape** temp = figures_;
		figures_ = new Shape * [right.capacity_];
		for (int i = 0; i < currentMaxIndex_; ++i) {
			delete temp[i];
		}
		delete[] temp;
		currentMaxIndex_ = right.currentMaxIndex_;
		capacity_ = right.capacity_;
		for (int i = 0; i < currentMaxIndex_; ++i) {
			figures_[i] = right.figures_[i]->clone();
		}
	}
	return *this;
}

CompositeShape::CompositeShape(CompositeShape&& move) noexcept{
	figures_ = move.figures_;
	currentMaxIndex_ = move.currentMaxIndex_;
	capacity_ = move.capacity_;
	move.figures_ = nullptr;
	move.currentMaxIndex_ = 0;
	move.capacity_ = 0;
}

CompositeShape& CompositeShape::operator=(CompositeShape&& right) noexcept
{
	if (this != &right) {
		for (int i = 0; i < currentMaxIndex_; ++i) {
			delete figures_[i];
		}
		delete[] figures_;
		figures_ = right.figures_;
		capacity_ = right.capacity_;
		currentMaxIndex_ = right.currentMaxIndex_;
		right.figures_ = nullptr;
		right.currentMaxIndex_ = 0;
		right.capacity_ = 0;
	}
	return *this;
}

CompositeShape::~CompositeShape() {
	for (int i = 0; i < currentMaxIndex_; ++i) {
		delete figures_[i];
	}
	delete[] figures_;
}



double CompositeShape::getArea() const {
	double area = 0;
	for (int i = 0; i < currentMaxIndex_; ++i) {
		area += figures_[i]->getArea();
	}
	return area;
}

rectangle_t CompositeShape::getFrameRect() const {
	rectangle_t rect = figures_[0]->getFrameRect();
	point_t p1 { rect.pos.x + rect.width / 2.0, rect.pos.y + rect.heigth / 2.0 };
	point_t p2 { rect.pos.x - rect.width / 2.0, rect.pos.y - rect.heigth / 2.0 };
	for (int i = 1; i < currentMaxIndex_; ++i) {
		rectangle_t temp = figures_[i]->getFrameRect();
		if (temp.pos.x + temp.width / 2.0 > p1.x) {
			p1.x = temp.pos.x + temp.width / 2.0;
		}
		if (temp.pos.y + temp.heigth / 2.0 > p1.y) {
			p1.y = temp.pos.y + temp.heigth / 2.0;
		}
		if (temp.pos.x - temp.width / 2.0 < p2.x) {
			p2.x = temp.pos.x - temp.width / 2.0;
		}
		if (temp.pos.y - temp.heigth / 2.0 < p2.y) {
			p2.y = temp.pos.y + temp.heigth / 2.0;
		}
	}
	rect.pos.x = (p1.x + p2.x) / 2.0;
	rect.pos.y = (p1.y + p2.y) / 2.0;
	rect.heigth = (p1.y - p2.y);
	rect.width = (p1.x - p2.x);
	return rect;
}

void CompositeShape::move(const point_t &aim) {
	rectangle_t buffRect = this->getFrameRect();
	double dx = aim.x - buffRect.pos.x;
	double dy = aim.y - buffRect.pos.y;
	for (int i = 0; i < currentMaxIndex_; ++i) {
		figures_[i]->move(dx, dy);
	}
}

void CompositeShape::move(double dx, double dy) {
	for (int i = 0; i < currentMaxIndex_; ++i) {
		figures_[i]->move(dx, dy);
	}
}

void CompositeShape::scale(double scaleCoefficient) {
	if (scaleCoefficient <= 0) {
		throw std::invalid_argument("Scale coefficient should be possitive!\n");
	}
	rectangle_t frRect = this->getFrameRect();
	point_t center = { frRect.pos.x, frRect.pos.y };
	for (int i = 0; i < currentMaxIndex_; ++i) {
		rectangle_t tmpRect = figures_[i]->getFrameRect();
		point_t a1{ tmpRect.pos.x - tmpRect.width / 2, tmpRect.pos.y - tmpRect.heigth / 2};
		figures_[i]->move(center);
		tmpRect = figures_[i]->getFrameRect();
		point_t a2{ tmpRect.pos.x - tmpRect.width / 2, tmpRect.pos.y - tmpRect.heigth / 2};
		point_t vector{ a1.x - a2.x, a1.y - a2.y };
		figures_[i]->scale(scaleCoefficient);
		vector.x = (vector.x * scaleCoefficient) + center.x;
		vector.y = (vector.y * scaleCoefficient) + center.y;
		figures_[i]->move(vector);
	}
}

const char* CompositeShape::getName() const {
	return "COMPLEX";
}

Shape* CompositeShape::clone() const {
	Shape* newCompositeShape = new CompositeShape(*this);
	return newCompositeShape;
}

void CompositeShape::push_back(Shape* shape){
	if (currentMaxIndex_ >= capacity_) {
		currentMaxIndex_ = capacity_ - 1;
		throw std::out_of_range("Composite shape should include less figures!\n");
	}
	figures_[currentMaxIndex_] = shape->clone();
	++currentMaxIndex_;
}

void CompositeShape::push_back(const Shape& shape) {
	if (currentMaxIndex_ >= capacity_) {
		currentMaxIndex_ = capacity_ - 1;
		throw std::out_of_range("Composite shape should include less figures!\n");
	}
	figures_[currentMaxIndex_] = shape.clone();
	++currentMaxIndex_;
}