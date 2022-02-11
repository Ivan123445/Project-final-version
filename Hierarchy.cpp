#include "Hierarchy.h"

double Hierarchy::distance(const point& first, const point& second) {  // counts distance between two points
    return sqrt(pow(first.get_x() - second.get_x(), 2) + pow(first.get_y() - second.get_y(), 2));
}

Hierarchy::Hierarchy(field& field) : field_for_search(field.get_cloud_copy()) { // works with copy because algorithm merges objects, so original points disappear
    int label_for_marking = 0;
    for (point& i : field_for_search) {
        i.set_label(label_for_marking);  // at the start of algorithm every point is a cluster
        ++label_for_marking;
    }
}

pair<int, int> Hierarchy::find_closest_objects() {
    double min_distance = -1;  // distance can't be negative
    int first_index, second_index;
    size_t field_size = field_for_search.size();
    for (int i = 0; i < field_size - 1; ++i) {   // simple loops to find the shortest distance
        for (int j = i + 1; j < field_size; ++j) {
            double current_distance = distance(field_for_search[i], field_for_search[j]);
            if (current_distance < min_distance || min_distance < 0) {
                min_distance = current_distance;
                first_index = i;
                second_index = j;
            }
        }
    }
    return make_pair(first_index, second_index);
}

void Hierarchy::unite_points(pair<int, int> closest_objects) {  // unites two objects in a single one
    if (seen_labels.find(field_for_search[closest_objects.first].get_label()) == seen_labels.end()) {     // if a point isn't a merged object                                                                                           // if a first point isn't a merged object,
        final_field.push_back(field_for_search[closest_objects.first]);                                  // it's being pushed to final field
        seen_labels.insert(field_for_search[closest_objects.first].get_label());                        // and its label is marked as merged,
    }

    if (seen_labels.find(field_for_search[closest_objects.second].get_label()) == seen_labels.end()) {               // if a second point isn't a merged object                                                                                                           // if a second point isn't a merged object
        field_for_search[closest_objects.second].set_label(field_for_search[closest_objects.first].get_label());     // it takes label of the first point
        final_field.push_back(field_for_search[closest_objects.second]);                                             // and also is being pushed to final field
    } else {
        for (point& i : final_field) {
            if (i.get_label() == field_for_search[closest_objects.second].get_label()) {
                i.set_label(field_for_search[closest_objects.first].get_label());  // else all points from the merged object take label of the first object
            }
        }
    }

    double new_x = (field_for_search[closest_objects.first].get_x() + field_for_search[closest_objects.second].get_x()) / 2;  // calculating x of the merged object
    double new_y = (field_for_search[closest_objects.first].get_y() + field_for_search[closest_objects.second].get_y()) / 2;  // and y
    field_for_search[closest_objects.first].set_x(new_x);  // setting new coordinates to the first object
    field_for_search[closest_objects.first].set_y(new_y);  // second object is being merged into the first one

    field_for_search.erase(field_for_search.begin() + closest_objects.second);  // the second object is being erased
}

void Hierarchy::find(size_t amount_of_clusters) {
    while (field_for_search.size() != amount_of_clusters) {
        pair<int, int> current_pair = find_closest_objects();  // the closest pair is being found
        unite_points(current_pair);                           // and merged into a single object
    }
}

vector<point>& Hierarchy::get_final_field() {
    return final_field;
}

