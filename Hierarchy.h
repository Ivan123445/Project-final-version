#pragma once

#include "field.h"

class Hierarchy {
private:
    vector<point> field_for_search;
    vector<point> final_field;
    set<int> seen_labels;

    static double distance(const point& first, const point& second);
    pair<int, int> find_closest_objects();
    void unite_points(pair<int, int>);

public:
    Hierarchy() = default;

    explicit Hierarchy(field& field);

    void find(size_t amount_of_clusters);

    vector<point>& get_final_field();
};


