#pragma once

#include "cloud.h"

class field
{
private:
    vector <point> cloud_arr;
public:
    explicit field();

    void set_label(int label);

    void add_cloud(cloud& to_add);

    void read_from_file(ifstream& fs);

    void write_to_file(ofstream& fs);

    void show_field();

    vector<point>& get_cloud_arr();

    vector<point> get_cloud_copy();
};

