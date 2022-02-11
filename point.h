#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <corecrt_math_defines.h>

using namespace std;

class point {
private:
    double x_coord, y_coord;
    int label;
public:
    explicit point();

    explicit point(double x, double y);

    explicit point(double x, double y, int lb);

    point(const point &other);

    double get_x() const;

    double get_y() const;

    int get_label() const;

    void set_x(double x);

    void set_y(double y);

    void set_label(int l);

    void add_x(double x);

    void add_y(double y);

    bool operator==(point point);

    bool operator!=(point point);
};

