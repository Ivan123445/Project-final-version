#pragma once

#include "field.h"
#include <limits>

class Sptr {
private:
    vector<point> field_for_search;
    vector<point> final_field;
    vector<point> temp_cluster;
    int label_for_marking = 5;
    void find_cluster(const point& start_point, double EPS);
    void mark_cluster(vector<point>& cluster) const;
public:
    Sptr() = default;

    explicit Sptr(field& field);

    void find(double EPS, size_t cluster_min_size);

    vector<point>& get_final_field();
};

