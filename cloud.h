#pragma once

#include "point.h"

class cloud {
private:
    vector <point> cloud_data;
    double x_center;
    double y_center;
    static vector <double> create_norm(int number_of_points, double minval, double maxval);
public:
    explicit cloud();

    void fill_cloud(int points_count, double x_start, double x_end, double y_start, double y_end);

    void move_x(double delta_x);

    void move_y(double delta_y);

    void angle_cloud_center_turn(double angle);

    void angle_start_point_turn(double angle);

    vector <point> get_cloud();

    bool is_empty();
};

