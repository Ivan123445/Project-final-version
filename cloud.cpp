#include "cloud.h"

cloud::cloud() : x_center(0), y_center(0)  {//default constructor
    cloud_data.resize(0);
}

vector <double> cloud::create_norm(int number_of_points, double minval, double maxval) {//norm gisto
    vector <double> normal_array(number_of_points); // Create a vector of predefined size
    if (minval > maxval) {
        swap(minval, maxval);
    }
    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    default_random_engine e(seed);
    normal_distribution<> rng_machine((maxval + minval) / 2, abs((maxval - minval) / 12));
    for (int i = 0; i < number_of_points; ++i) {
        normal_array[i] = rng_machine(e);
    }
    return normal_array;
}

void cloud::fill_cloud(int points_count, double x_start, double x_end, double y_start, double y_end) {  // cloud is filled in fixed range
    cloud_data.resize(points_count);
    vector <double> x_arr = create_norm(points_count, x_start, x_end);  // with normal distribution
    vector <double> y_arr = create_norm(points_count, y_start, y_end);
    for (int i = 0; i < points_count; ++i) {
        cloud_data[i].set_x(x_arr[i]);
        cloud_data[i].set_y(y_arr[i]);
        cloud_data[i].set_label(0);
        x_center += x_arr[i];
        y_center += y_arr[i];
    }
    x_center /= points_count;
    y_center /= points_count;
}

void cloud::move_x(const double delta_x) {
    for (point& i : cloud_data) {
        i.add_x(delta_x);
    }
}

void cloud::move_y(const double delta_y) {
    for (point& i : cloud_data) {
        i.add_y(delta_y);
    }
}

void cloud::angle_cloud_center_turn(double angle) {  // turn every point around cloud center on fixed angle
    angle *= M_PI / 180;  // transforms degrees into radians
    double calc_cos = cos(angle);
    double calc_sin = sin(angle);
    for (point& i : cloud_data) {
        double new_x = x_center + calc_cos * (i.get_x() - x_center) - calc_sin * (i.get_y() - y_center);
        double new_y = y_center + calc_sin * (i.get_x() - x_center) + calc_cos * (i.get_y() - y_center);
        i.set_x(new_x);
        i.set_y(new_y);
    }
}

void cloud::angle_start_point_turn(double angle) {  // turn every point around coordinates center (0, 0) on fixed angle
    angle *= M_PI / 180;
    double calc_cos = cos(angle);
    double calc_sin = sin(angle);
    for (point& i : cloud_data) {
        double new_y = calc_cos * (i.get_x()) - calc_sin * (i.get_y());
        double new_x = calc_sin * (i.get_x()) + calc_cos * (i.get_y());
        i.set_x(new_x);
        i.set_y(new_y);
    }
    double new_x = calc_cos * x_center - calc_sin * y_center;
    double new_y = calc_sin * x_center + calc_cos * y_center;
    x_center = new_x;
    y_center = new_y;
}

vector <point> cloud::get_cloud() {
    return cloud_data;
}

bool cloud::is_empty() {
    if (cloud_data.empty()) {
        return true;
    }
    return false;
}
