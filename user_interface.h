#pragma once

#include "field.h"
#include "Sptr.h"
#include "Wave.h"
#include "Hierarchy.h"

#define OPEN_ERR (-2)

class user_interface
{
private:
    field main_field;
    vector <point> found_clusters;
    const set <int> numbers_set = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 46 };
    static int enter_alg_name();
    static double enter_double();
    static size_t enter_size_t();
    bool correct_num_value(string value, bool can_be_negative);
    void cloud_actions(cloud & cloud);
    void create_field_manually();
    void make_plot_file();
    void write_down_main_field();
    void recount_labels();
    static bool comp(const point& first, const point& second);
public:
    user_interface() = default;
    void create_field(const string& filename = "");
    void find();
};

