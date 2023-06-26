#ifndef CPP_TEMPLATE_DECISIONTREE_H
#define CPP_TEMPLATE_DECISIONTREE_H

#include "data.h"

class DecisionTree {
public:
    explicit DecisionTree(std::string metric);

    void train(const std::vector<Iris> &dataset);

    std::string predict(const Iris &iris) const;

    void print() const;

private:
    struct Node {
        std::string label; // empty for internal nodes, non-empty for leaf nodes
        std::string feature;
        double threshold;
        Node *left_child;
        Node *right_child;
    };

    void build_tree(const std::vector<Iris> &dataset);

    Node *build_tree_helper(const std::vector<Iris> &dataset, const std::vector<std::string> &features);

    static double information_gain(const std::vector<Iris> &dataset, const std::string &feature, double &threshold) ;

    static double gini_index(const std::vector<Iris> &dataset, const std::string &feature, double &threshold) ;

    static double entropy(const std::vector<Iris> &dataset);

    static double gini(const std::vector<Iris> &dataset);

    static std::vector<double> generate_thresholds(const std::vector<Iris> &dataset, const std::string &feature);

    static void split_dataset_by_feature(const std::vector<Iris> &dataset, const std::string &feature, double threshold,
                                         std::vector<Iris> &left_dataset, std::vector<Iris> &right_dataset);

    static std::vector<std::string>
    remove_feature(const std::vector<std::string> &features, const std::string &feature);

    void print_helper(const Node *node, int indent) const;

    Node *root_ = nullptr;
    std::string metric_;
};


#endif //CPP_TEMPLATE_DECISIONTREE_H
