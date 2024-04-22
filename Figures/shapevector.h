#ifndef SHAPE_VECTOR_T
#define SHAPE_VECTOR_T
#include <cstdlib>
#include "shape.h"

class ShapeVector{
public:
	ShapeVector() :
		arr_(nullptr),
		size_(0)
	{}
	
	Shape*& operator[](size_t index) {
		return arr_[index];
	}

	const Shape* operator[](size_t index) const {
		return arr_[index];
	}

	~ShapeVector() {
		for (int i = 0; i < size_; ++i) {
			delete arr_[i];
		}
		delete[] arr_;
	}

	void push_back(Shape * elem) {
		resize();
		arr_[size_ - 1] = elem->clone();
	}

	void push_back(const Shape& elem) {
		resize();
		arr_[size_ - 1] = elem.clone();
	}

	bool isEmpty() const {
		if (size_ == 0) {
			return true;
		}
		return false;
	}


private:
	Shape ** arr_;
	std::size_t size_;

	void resize() {
		Shape** tmp = arr_;
		arr_ = new Shape * [size_ + 1];
		std::copy(tmp, tmp + size_, arr_);
		++size_;
		delete[] tmp;
	}
};

#endif