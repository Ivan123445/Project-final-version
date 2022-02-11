#include "user_interface.h"

int user_interface::enter_alg_name() {
    string input;
    cin >> input;
    while (input < "1" and input > "7") {
        cout << "Incorrect input, enter valid algorithm number";
        cin >> input;
    }
    return stoi(input);
}

bool user_interface::correct_num_value(string value, bool can_be_negative) {
    if (!can_be_negative) {
        for (auto i : value) {
            if (numbers_set.find(i) == numbers_set.end()) {
                cout << "incorrect value, enter correct positive number\n";
                return false;
            }
        }
        return true;
    }
    for (size_t i = 0; i < value.size(); ++i) {
        if (numbers_set.find(value[i]) == numbers_set.end() && value[0] != '-') {
            cout << "incorrect value, enter correct positive number\n";
            return false;
        }
    }
    return true;
}

void user_interface::cloud_actions(cloud & cloud) {
    const string action_list = "enter number to perform action\n1- fill cloud\n2 - move all cloud points on x value\n3 - move all cloud points on y value\n4 - turn all points around cloud center on angle value\n5 - turn all cloud around coordinates center on angle value\n6 - print action list\n7 - end work with cloud\n";
    string input;
    cout << action_list;
    bool cloud_not_exist = cloud.is_empty();
    int action_num;
    while (true) {
        cout << "enter new action (enter 6 to see action list)\n";
        cin >> input;
        action_num = stoi(input);
        if (action_num < 1 or action_num > 7 or input.size() != 1 or (cloud_not_exist and action_num != 1 and action_num != 7)) {
            cout << "Incorrect input, enter correct value\n";
            continue;
        }
        if (action_num == 7) {
            cout << "end of work with cloud\n";
            break;
        }
        else {
            switch (action_num) {
                case 1: {
                    string points_count_s, x_start_s, x_end_s, y_end_s, y_start_s;
                    double x_start, x_end, y_start, y_end;
                    int points_count;
                    cout << "Enter points' amount\n";
                    bool correct_values = false;
                    while (!correct_values) {
                        cin >> points_count_s;
                        correct_values = correct_num_value(points_count_s, false);
                        if (stoi(points_count_s) < 1 && correct_values) {
                            correct_values = false;
                            cout << "Incorrect input, enter correct value\n";
                        }
                    }
                    points_count = stoi(points_count_s);

                    cout << "Enter x start\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> x_start_s;
                        correct_values = correct_num_value(x_start_s, true);
                    }
                    x_start = stod(x_start_s);

                    cout << "Enter x end\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> x_end_s;
                        correct_values = correct_num_value(x_end_s, true);
                    }
                    x_end = stod(x_end_s);

                    cout << "Enter y start\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> y_start_s;
                        correct_values = correct_num_value(y_start_s, true);
                    }
                    y_start = stod(y_start_s);

                    cout << "Enter y end\n";
                    correct_values = false;
                    while (!correct_values) {
                        cin >> y_end_s;
                        correct_values = correct_num_value(y_end_s, true);
                    }
                    y_end = stod(y_end_s);

                    cloud.fill_cloud(points_count, x_start, x_end, y_start, y_end);
                    cloud_not_exist = false;
                    break;
                }
                case 2: {
                    cout << "Enter x shift\n";
                    bool correct_values = false;
                    string dx_s;
                    double dx;
                    while (!correct_values) {
                        cin >> dx_s;
                        correct_values = correct_num_value(dx_s, true);
                    }
                    dx = stod(dx_s);
                    cloud.move_x(dx);
                    break;
                }
                case 3: {
                    cout << "Enter y shift\n";
                    bool correct_values = false;
                    string dy_s;
                    double dy;
                    while (!correct_values) {
                        cin >> dy_s;
                        correct_values = correct_num_value(dy_s, true);
                    }
                    dy = stod(dy_s);
                    cloud.move_y(dy);
                    break;
                }
                case 4: {
                    cout << "Enter angle value for rotation\n";
                    bool correct_values = false;
                    string angle_s;
                    double angle;
                    while (!correct_values) {
                        cin >> angle_s;
                        correct_values = correct_num_value(angle_s, true);
                    }
                    angle = stod(angle_s);
                    cloud.angle_cloud_center_turn(angle);
                    break;
                }
                case 5: {
                    cout << "Enter angle value for rotation\n";
                    bool correct_values = false;
                    string angle_s;
                    double angle;
                    while (!correct_values) {
                        cin >> angle_s;
                        correct_values = correct_num_value(angle_s, true);
                    }
                    angle = stod(angle_s);
                    cloud.angle_start_point_turn(angle);
                    break;
                }
                case 6: {
                    cout << action_list;
                    break;
                }
                default: {
                    cout << "this shouldn't happen...\n";
                    break;
                }
            }
        }
    }
}

void user_interface::create_field_manually() {
    int action_num;
    string input;
    const string action_input = "Enter 1 to create new cloud\nEnter 2 to end finishing clouds and create field\n";
    while (true) {
        cout << action_input;
        cin >> input;
        action_num = stoi(input);
        if (action_num < 1 or action_num > 2 or input.size() != 1) {
            cout << "Incorrect input, enter correct value\n";
            continue;
        }
        if (action_num == 2) {
            cout << "end of cloud input\n";
            break;
        }
        cloud new_cloud;
        cloud_actions(new_cloud);
        main_field.add_cloud(new_cloud);
        cout << "enter new action\n";
    }
}

void user_interface::write_down_main_field() {  // writing all points to file
    cout << "Enter file's name\n";
    string output_file;
    cin >> output_file;
    ofstream fs(output_file);
    fs.exceptions(std::ifstream::failbit);
    main_field.write_to_file(fs);
    cout << "field successfully wrote to file\n";
    fs.close();
}

void user_interface::create_field(const string& filename) {  // main function to create a field
    if (!filename.empty()) {
        try {
            ifstream fs(filename);
            fs.exceptions(std::ifstream::failbit);
            cout << "*beginning of a work with field*\n";
            main_field.read_from_file(fs);
            fs.close();
        }
        catch (ifstream::failure&) {
            throw ifstream::failure("problem while opening or reading file");
        }
    } else {
        create_field_manually();
    }
    cout << "field created\n";
    const string instruction = "Enter 1 to show field\nEnter 2 to write field to file\nEnter 3 to see the instruction\nEnter -1 to end work with field\n";
    cout << instruction;
    string output_choice;
    while (output_choice != "-1") {
        cin >> output_choice;
        if (output_choice == "1") {
            main_field.show_field();
        }
        else if (output_choice == "2") {
            write_down_main_field();
        }
        else if (output_choice == "3") {
            cout << instruction;
        }
        else if (output_choice == "-1") {
            cout << "*work with field finished*\n";
            break;
        }
        else {
            cout << "incorrect input\n";
        }
        cout << "enter new action (enter 3 to see the instruction)\n";
    }
}

double user_interface::enter_double() {  // entering double variable for algorithm
    string string_var;
    double double_var;
    bool valid_input = false;
    while (!valid_input) {
        valid_input = true;
        cin >> string_var;
        try {
            double_var = stod(string_var);
        }
        catch (invalid_argument&) {
            cout << "invalid argument, try again\n";
            valid_input = false;
        }
    }
    return double_var;
}

size_t user_interface::enter_size_t() {  // entering size_t variable for algorithm
    bool valid_input = false;
    string string_var;
    size_t size_t_var;
    while (!valid_input) {
        valid_input = true;
        cin >> string_var;
        try {
            size_t_var = stoi(string_var);
        }
        catch (invalid_argument&) {
            cout << "invalid argument, try again\n";
            valid_input = false;
        }
    }
    return size_t_var;
}

void user_interface::find() {  // main function to find with algorithm
    const string instruction = "Enter algorithm number:\n1 for Wave\n2 for SPtr\n3 for Hierarchy\nAnother actions:\nEnter 4 to see the instruction\nEnter 5 to show final field\nEnter 6 to write field to plot file\nEnter 7 to finish finding clusters\n";
    cout << instruction;
    int choice = enter_alg_name();

    while (choice != 7) {
        switch (choice) {
            case 1: {
                main_field.set_label(0);
                cout << "Enter EPS\n";
                double EPS = enter_double();

                Wave wave_find(main_field);
                wave_find.find(EPS);
                found_clusters = wave_find.get_final_field();

                if (!found_clusters.empty()) {
                    recount_labels();
                    cout << "clusters found!\n";
                }
                else {
                    cout << "there are no clusters found with given values\n";
                }
                break;
            }
            case 2: {
                cout << "Enter EPS\n";
                double EPS = enter_double();
                cout << "enter minimum points' amount in cluster\n";
                size_t cluster_min_size = enter_size_t();
                main_field.set_label(0);

                Sptr sptr_find(main_field);
                sptr_find.find(EPS, cluster_min_size);
                found_clusters = sptr_find.get_final_field();

                if (!found_clusters.empty()) {
                    recount_labels();
                    cout << "clusters found!\n";
                } else {
                    cout << "there are no clusters found with given values\n";
                }
                break;
            }
            case 3: {
                cout << "Enter clusters' amount\n";
                size_t clusters_amount = enter_size_t();
                main_field.set_label(0);
                Hierarchy hierarchy_find(main_field);
                hierarchy_find.find(clusters_amount);
                found_clusters = hierarchy_find.get_final_field();
                if (!found_clusters.empty()) {
                    recount_labels();
                    cout << "clusters found!\n";
                } else {
                    cout << "there are no clusters found with given values\n";
                }
                break;

            }
            case 4: {
                cout << instruction;
                break;
            }
            case 5: {
                for (const point& i : found_clusters) {
                    cout << i.get_x() << "\t" << i.get_y() << "\t" << i.get_label() << endl;
                }
                break;
            }
            case 6 : {
                make_plot_file();
                break;
            }
            default: {
                cout << "incorrect value\n";
                break;
            }
        }
        cout << "Enter new action (enter 4 to see the instructions) \n";
        choice = enter_alg_name();
    }
}

bool user_interface::comp(const point& first, const point& second) {  // compare function to sort by labels
    return first.get_label() < second.get_label();
}

void user_interface::recount_labels() {   // make all labels from number 1 with step 1
    sort(found_clusters.begin(), found_clusters.end(), comp);  // sorting all found clusters with custom compare fuction(by labels)

    int new_number = 0;
    int current_number = -1;

    for (point& i : found_clusters) {
        if (current_number != i.get_label()) {
            current_number = i.get_label();
            ++new_number;
        }
        i.set_label(new_number);
    }
}

void user_interface::make_plot_file() {  // making plot file that can be a data for gnuplot
    if (found_clusters.empty()) {
        cout << "clusters haven't been found yet or there are no clusters found with given values\n";
        return;
    }
    size_t color_count = found_clusters[found_clusters.size() - 1].get_label();  // this can be done because of sort

    vector<int> colors(color_count);
    srand(time(nullptr));
    for (int& i : colors) {
        i = abs(65536 * rand() + 256 * rand() + rand());  // random color for every different cluster
    }

    cout << "enter file's name to write points with colors\n";
    string filename;
    cin >> filename;
    ofstream fs(filename);
    fs.exceptions(std::ifstream::failbit);

    for (const point& i : found_clusters) {
        fs << i.get_x() << " " << i.get_y() << " " << colors[(size_t)i.get_label() - 1] << endl;
    }
    fs.close();
}

// gnuplot script: 
// plot 'data.txt' u 1:2:3 with points lc variable title ''
// for gnuplot online http://gnuplot.respawned.com/#
