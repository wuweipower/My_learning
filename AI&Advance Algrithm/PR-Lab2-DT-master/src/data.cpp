#include "data.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<Iris> load_iris_dataset(const string &filename) {
    vector<Iris> dataset;
    ifstream input(filename);
    if (!input) {
        print_error("Could not open file " + filename + ", make sure your working dir is correct.", __FUNCTION__);
        print_info("Contact TA if you cannot solve this problem.", __FUNCTION__);
        exit(EXIT_FAILURE);
    }
    string line;
    getline(input, line); // skip header line
    while (getline(input, line)) {
        stringstream ss(line);
        string field;
        Iris iris;
        getline(ss, field, ',');
        iris.sepal_length = stod(field);
        getline(ss, field, ',');
        iris.sepal_width = stod(field);
        getline(ss, field, ',');
        iris.petal_length = stod(field);
        getline(ss, field, ',');
        iris.petal_width = stod(field);
        getline(ss, field, ',');
        iris.variety = field.substr(1, field.length() - 2); // remove quotes
        dataset.push_back(iris);
    }
    input.close();
    return dataset;
}

double iris_feature(const Iris &iris, const string &feature) {
    if (feature == "sepal_length") {
        return iris.sepal_length;
    } else if (feature == "sepal_width") {
        return iris.sepal_width;
    } else if (feature == "petal_length") {
        return iris.petal_length;
    } else if (feature == "petal_width") {
        return iris.petal_width;
    } else {
        print_error("Unknown feature: " + feature, __FUNCTION__);
        return 0;
    }
}