#include "point.h"

point::point() : x_coord(0), y_coord(0), label(0) {} // default contructor

point::point(double x, double y) : x_coord(x), y_coord(y), label(0) {	} // Initialize fields with passed parameters

point::point(double x, double y, int label) : x_coord(x), y_coord(y), label(label) {	}

point::point(const point &other) {// Copy constructor
    this->x_coord = other.x_coord;
    this->y_coord = other.y_coord;
    this->label = other.label;
}

double point::get_x() const {//get X
    return this->x_coord;
}

double point::get_y() const {//get Y
    return this->y_coord;
}

int point::get_label() const {//get label
    return this->label;
}

void point::set_x(double x) {//set X coordinate
    this->x_coord = x;
}

void point::set_y(double y) {//set Y coordinate
    this->y_coord = y;
}

void point::set_label(int l) {//set label
    this->label = l;
}

void point::add_x(double x) {//move X coordinate
    this->x_coord += x;
}

void point::add_y(double y) {//move Y coordinate
    this->y_coord += y;
}

bool point::operator==(point point) {
    return this->x_coord == point.x_coord && this->y_coord == point.y_coord && this->label == point.label;
}

bool point::operator!=(point point) {
    return !(*this == point);
}
