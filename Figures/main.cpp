#include <fstream>
#include "rectangle.h"
#include "ring.h"
#include "compositeshape.h"
#include "shapevector.h"

void sortShapes(ShapeVector& figures, int size) {
	for (int i = 0; i < size; ++i) {
		bool isSorted = true;
		for (int j = 0; j < size - (i + 1); ++j) {
			if (figures[j] < figures[j + 1]) {
				std::swap(figures[j], figures[j + 1]);
				isSorted = false;
			}
		}
		if (isSorted) {
			break;
		}
	}
}

void move(double dx, double dy, ShapeVector& figures, int size) {
	for (int i = 0; i < size; ++i) {
		figures[i]->move(dx, dy);
	}
}

void scale(double centerX, double centerY, double scaleCoefficient, ShapeVector& figures, int size) {
	if (scaleCoefficient <= 0) {
		throw std::invalid_argument("Scale coefficient should be possitive!\n");
	}
	for (int i = 0; i < size; ++i) {
		rectangle_t tmpRect = figures[i]->getFrameRect();
		point_t a1{ tmpRect.pos.x - tmpRect.width / 2, tmpRect.pos.y - tmpRect.heigth / 2 };
		figures[i]->move(point_t{centerX, centerY}); 
		tmpRect = figures[i]->getFrameRect();
		point_t a2{ tmpRect.pos.x - tmpRect.width / 2, tmpRect.pos.y - tmpRect.heigth / 2 };
		point_t vector{ a1.x - a2.x, a1.y - a2.y };
		figures[i]->scale(scaleCoefficient);
		vector.x = (vector.x * scaleCoefficient) + centerX;
		vector.y = (vector.y * scaleCoefficient) + centerY;
		figures[i]->move(vector);
	}
}

int main() {
	std::fstream fin;
	fin.open("input.txt");
	if (!fin.is_open()) {
		std::cerr << "File is not open!\n";
		fin.close();
		return 1;
	}
	ShapeVector figures;
	int size = 0;
	std::string shapeName;
	fin >> shapeName;
	while (shapeName != "SCALE" && shapeName != "MOVE" && !fin.eof()) {
		if (shapeName == "RECTANGLE") {
			double leftBottomX = .0,
				leftBottomY = .0,
				rightUpperX = .0,
				rightUpperY = .0;
			fin >> leftBottomX >> leftBottomY >> rightUpperX >> rightUpperY;
			try {
				figures.push_back(Rectangle(leftBottomX, leftBottomY, rightUpperX, rightUpperY));
			}
			catch (const std::exception& err) {
				std::cerr << err.what();
				fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				--size;
			}
		}
		else if (shapeName == "RING") {
			double centerX = .0,
				centerY = .0,
				outRadius = .0,
				inRadius = .0;
			fin >> centerX >> centerY >> outRadius >> inRadius;
			try {
				figures.push_back(Ring(centerX, centerY, outRadius, inRadius));
			}
			catch (const std::exception& err) {
				std::cerr << err.what();
				fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				--size;
			}
		}
		else if (shapeName == "COMPLEX") {
			int compositeSize = 0;
			fin >> compositeSize;
			try {
				CompositeShape complex(compositeSize);
				std::string compositePartName;
				fin >> compositePartName;
				while (compositePartName != "COMPLEXEND" && !fin.eof()) {
					if (compositePartName == "RECTANGLE") {
						double leftBottomX = .0,
							leftBottomY = .0,
							rightUpperX = .0,
							rightUpperY = .0;
						fin >> leftBottomX >> leftBottomY >> rightUpperX >> rightUpperY;
						complex.push_back(Rectangle(leftBottomX, leftBottomY, rightUpperX, rightUpperY));

					}
					else if (compositePartName == "RING") {
						double centerX = .0,
							centerY = .0,
							outRadius = .0,
							inRadius = .0;
						fin >> centerX >> centerY >> outRadius >> inRadius;
						complex.push_back(Ring(centerX, centerY, outRadius, inRadius));
					}
					else {
						std::cerr << "Invalid complex part name!\n";
						fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
					fin >> compositePartName;
				}
				figures.push_back(complex);
			}
			catch (const std::exception& err) {
				std::cerr << err.what();
				std::string temp;
				fin >> temp;
				while (temp != "COMPLEXEND" && !fin.eof()) {
					fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					fin >> temp;
				}
				--size;
			}
		}
		else {
			std::cerr << "Invalid figure name!\n";
			fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			--size;
		}
		fin >> shapeName;
		++size;
	}
	sortShapes(figures, size);
	for (int i = 0; i < size; ++i) {
		std::cout << figures[i] << "\n";
	}
	if (!fin.eof()) {
		std::string command;
		if (!(shapeName == "MOVE" || shapeName == "SCALE")) {
			fin >> command;
		}
		else {
			command = shapeName;
		}
		while (!fin.eof()) {
			if (command == "SCALE") {
				double centerX = .0,
					centerY = .0,
					coeff = 1.0;
				fin >> centerX >> centerY >> coeff;
				try {
					scale(centerX, centerY, coeff, figures, size);
				}
				catch (const std::invalid_argument& err) {
					std::cerr << err.what();
				}
			}
			else if (command == "MOVE") {
				double dx = .0,
					dy = .0;
				fin >> dx >> dy;
				move(dx, dy, figures, size);
			}
			else {
				std::cerr << "Invalid command name!\n";
				fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			fin >> command;
		}
	}
	for (int i = 0; i < size; ++i) {
		std::cout << figures[i] << "\n";
	}
	Shape* rect = new Rectangle(0, 0, 1, 1);
	Rectangle rect1(0, 0, 1, 1);
	CompositeShape comp(3);
	comp.push_back(rect);
	comp.push_back(rect1);
	comp.push_back(Rectangle(0, 0, 1, 1));
	CompositeShape comp1(comp);
	CompositeShape comp2(std::move(comp));
	CompositeShape comp3(3);
	comp3 = comp1;
	delete rect;
	fin.close();
	return 0;
}