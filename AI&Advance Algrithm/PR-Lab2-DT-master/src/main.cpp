#include <unistd.h>
#include <iostream>
#include <string>
#include <getopt.h>
#include "utils.h"
#include "data.h"
#include "decision_tree.h"

using namespace std;

static const struct option long_options[] = {
        {"help",      no_argument,       nullptr, 'h'},
        {"version",   no_argument,       nullptr, 'v'},
        {"data",      optional_argument, nullptr, 'd'},
        {"metric", optional_argument, nullptr, 'a'},
        {nullptr,     no_argument,       nullptr, 0}
};

void print_version() {
    cout << "Decision Tree v0.0.0" << endl;
    cout << "Copyright (c) 2023 JustSong." << endl;
    cout << "Compiled on " << __DATE__ << " at " << __TIME__ << "." << endl;
}

void print_help() {
    cout << "Usage: dtree-cpp [options]" << endl;
    cout << "Options:" << endl;
    cout << "  -h, --help     display this help and exit" << endl;
    cout << "  -v, --version  output version information and exit" << endl;
    cout << "  -d, --data     dataset path" << endl;
    cout << "  -m, --metric   metric to use" << endl;
}

vector<string> parse_args(int argc, char *argv[]) {
    string data_path, metric;
    int opt, opt_idx;
    while ((opt = getopt_long(argc, argv, "hvd:m:", long_options, &opt_idx)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
                break;
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
                break;
            case 'd':
                data_path = optarg;
                break;
            case 'm':
                metric = optarg;
                break;
            default:
                print_help();
                exit(EXIT_FAILURE);
        }
    }
    return {data_path, metric};
}

double evaluate(vector<Iris> &dataset, DecisionTree &decisionTree) {
    int correct = 0;
    for (auto &iris: dataset) {
        //print_info("eva",decisionTree.predict(iris));
        if (decisionTree.predict(iris) == iris.variety) {
            correct++;
        }
    }
    return (double) correct / dataset.size();
}

int main(int argc, char *argv[]) {
    auto config = parse_args(argc, argv);
    string data_path = config[0];
    string metric = config[1];
    if (data_path.empty()) {
        data_path = "../data/iris.csv";
    }
    if (metric.empty()) {
        //metric = "info_gain";
        metric = "gini_index";
    }
    print_info("Metric: " + metric, __FUNCTION__);
    print_info("Dataset path: " + data_path, __FUNCTION__);
    print_info("Dataset loading...", __FUNCTION__);
    vector<Iris> dataset = load_iris_dataset(data_path);
    print_info("Dataset loaded, total " + to_string(dataset.size()) + " records.", __FUNCTION__);
    DecisionTree decisionTree(metric);
    decisionTree.train(dataset);
    print_info("Decision tree trained.", __FUNCTION__);
//    decisionTree.print();
    print_info("Predicting...", __FUNCTION__);
    double rate = evaluate(dataset, decisionTree);
    print_info("Prediction accuracy: " + to_string(rate * 100) + "%", __FUNCTION__);
    if (rate > 0.95) {
        print_info("Congratulations! You have passed the test!", __FUNCTION__);
    } else {
        print_info("Sorry, you have failed the test. Please try to improve your model.", __FUNCTION__);
    }
    return 0;
}
