#ifndef CPP_TEMPLATE_DATA_H
#define CPP_TEMPLATE_DATA_H

#include <string>
#include <vector>

struct Iris {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    std::string variety;
};

std::vector<Iris> load_iris_dataset(const std::string &filename);
double iris_feature(const Iris& iris, const std::string& feature);

#endif //CPP_TEMPLATE_DATA_H
