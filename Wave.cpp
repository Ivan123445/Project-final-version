#include "Wave.h"

Wave::Wave(field& field) : field_for_search(field.get_cloud_arr()), unchecked_points_count(field_for_search.size()) { }

void Wave::find(const double EPS) {
    while (unchecked_points_count) {
        for (point& i : field_for_search) {
            if (i.get_label() == 0) {
                find_neighbours(i, EPS);  // finding neighbours for point
                while (!points_queue.empty()) {
                    point temp = points_queue.front();  // first point in queue
                    points_queue.pop();  // removing point from the queue
                    find_neighbours(temp, EPS);  // finding neighbours for every neighbour :)
                }
                write_to_final_field();
            }
        }
    }
}

void Wave::write_to_final_field() {  // marking found cluster
    for (point& i : field_for_search) {
        if (i.get_label() == 2) {
            i.set_label(label_for_marking);
            final_field.push_back(i);
        }
    }
    ++label_for_marking;
}

void Wave::find_neighbours(point& start_point, const double EPS) {
    for (point& i : field_for_search) {
        if (i.get_label() < 2) {  // if a point is not in cluster
            double distance = sqrt(pow(i.get_x() - start_point.get_x(), 2) + pow(i.get_y() - start_point.get_y(), 2));
            if (distance < EPS) {  // if point belongs to a start point's cluster
                if (distance == 0) {  // if it is a start point
                    i.set_label(2);  // it is marked as a part of new cluster
                    --unchecked_points_count;
                }
                if (i.get_label() == 0) {
                    i.set_label(1);  // all points that could be in cluster
                    points_queue.push(i);  // are being pushed into queue
                }
            }
        }
    }
}

vector<point>& Wave::get_final_field() {
    return final_field;
}