#include "functions.h"
#include <cmath>
#include <cassert>

using namespace std;

double cross_entropy(const vector<double> &y, const vector<double> &y_hat) {
    double loss = 0;
    for (int i = 0; i < y.size(); i++) {
        loss += -y[i] * log(y_hat[i]);
    }
    return loss;
}

vector<double> sigmoid(vector<double> x) {
    for (auto &i: x) {
        i = 1 / (1 + exp(-i));
    }
    return x;
}

vector<double> d_sigmoid(const vector<double> &x) {
    auto sigmoid_x = sigmoid(x);
    auto d = vector<double>(sigmoid_x.size(), 0);
    for (int i = 0; i < sigmoid_x.size(); i++) {
        d[i] = sigmoid_x[i] * (1 - sigmoid_x[i]);
    }
    return d;
}

vector<double> softmax(const vector<double> &x) {
    auto ex = vector<double>(x.size(), 0);
    double sum = 0;
    for (int i = 0; i < x.size(); i++) {
        ex[i] = exp(x[i]);
        sum += ex[i];
    }
    for (int i = 0; i < x.size(); i++) {
        ex[i] /= sum;
    }
    return ex;
}

vector<double> d_softmax_cross_entropy(const vector<double> &y, const vector<double> &y_hat) {
    // https://blog.csdn.net/jasonleesjtu/article/details/89426465
    auto d = vector<double>(y.size(), 0);
    for (int i = 0; i < y.size(); i++) {
        d[i] = y_hat[i] - y[i];
    }
    return d;
}

vector<vector<double>> outer_product(const vector<double> &x, const vector<double> &y) {
    auto result = vector<vector<double>>(x.size(), vector<double>(y.size(), 0));
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < y.size(); j++) {
            result[i][j] = x[i] * y[j];
        }
    }
    return result;
}

void matrix_add(vector<vector<double>> &x, const vector<vector<double>> &y) {
    assert(x.size() == y.size());
    assert(x[0].size() == y[0].size());
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            x[i][j] += y[i][j];
        }
    }
}

void vector_add(vector<double> &x, const vector<double> &y) {
    assert(x.size() == y.size());
    for (int i = 0; i < x.size(); i++) {
        x[i] += y[i];
    }
}

void matrix_multiply(std::vector<std::vector<double>> &x, double y) {
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[0].size(); j++) {
            x[i][j] *= y;
        }
    }
}
void vector_multiply(std::vector<double> &x, double y) {
    for (double & i : x) {
        i *= y;
    }
}

double random(double min, double max) {
    return min + (max - min) * rand() / (RAND_MAX + 1.0);
}