#pragma once

#include "field.h"

class Wave {
private:
    vector<point> field_for_search;
    vector<point> final_field;
    queue<point> points_queue;
    int label_for_marking = 5;
    size_t unchecked_points_count;
    void find_neighbours(point& start_point, const double EPS);
    void write_to_final_field();
public:
    Wave() = default;

    explicit Wave(field& field);

    void find(double EPS);

    vector<point>& get_final_field();
};

