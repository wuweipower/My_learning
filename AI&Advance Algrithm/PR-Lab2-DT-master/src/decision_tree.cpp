#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
#include <climits>
#include "decision_tree.h"
#include "utils.h"

using namespace std;


DecisionTree::DecisionTree(string metric) : metric_(std::move(metric)) {
}

void DecisionTree::train(const vector<Iris> &dataset) {
    build_tree(dataset);
    //print();
}

string DecisionTree::predict(const Iris &iris) const {
    // TODO: implement this function
    //use a temporary varible to store the root so that we do not change the root
    //which can avoid effecting the next prediction
    Node* temp = root_;
    double val = iris_feature(iris,temp->feature);
    while(temp->label.empty())
    {
        if(val <= temp->threshold) 
        {
            temp = temp->left_child;
        }         
        else 
        {
            temp = temp->right_child;
        }
        if(!temp->feature.empty())
        val = iris_feature(iris,temp->feature);
    }
    return temp->label;

}

void DecisionTree::build_tree(const vector<Iris> &dataset) {
    // TODO: implement this function
    vector<string> features={"sepal_length","sepal_width","petal_length","petal_width"};
    root_=build_tree_helper(dataset,features);
}

DecisionTree::Node *DecisionTree::build_tree_helper(const vector<Iris> &dataset, const vector<string> &features) {
    // TODO: implement this function  
    //vector<string> new_features={"sepal_length","sepal_width","petal_length","petal_width"};
    //判断是否只有一个label了
    Node * node =  new Node();
    string label = dataset[0].variety;
    bool flag=true;
    for(auto i : dataset)
    {
        if(i.variety!=label)
        {
            flag = false;
            break;
        }   
    }
    if(flag)
    {
        node->label=label;
        node->left_child = nullptr;
        node->right_child = nullptr;
        return node;
    }
    //没有feature了，就以最多的label最为lable
    if(features.size()==0)
    {
        map<string, double>m;
        double count=0;
        for(Iris item: dataset)
        {
            m[item.variety]++;
            if(count < m[item.variety])
            {
                label = item.variety;
                count = m[item.variety];
            }
        }   
        node->label=label;
        node->left_child = nullptr;
        node->right_child = nullptr;
        return node;
    }

    string maxFeature;
    double maxGain = INT_MIN;
    double GiniMin = INT_MAX;
    double thres = 0;
    if(metric_=="info_gain")
    {
        for(auto feature : features)
        {
            vector<double> thresholds = generate_thresholds(dataset,feature);
            for(int i =0;i<thresholds.size();i++)
            {
                double gain = information_gain(dataset,feature,thresholds[i]);
                //print_info(to_string(gain),"gain");
                if(gain>maxGain)
                {
                    maxGain = gain;
                    maxFeature = feature;
                    thres = thresholds[i];
                }
            }
        }
    }
    else
    {
        for(auto feature : features)
        {
            vector<double> thresholds = generate_thresholds(dataset,feature);
            for(int i =0;i<thresholds.size();i++)
            {
                double gini = gini_index(dataset,feature,thresholds[i]);
                if(gini<GiniMin)
                {
                    GiniMin = gini;
                    maxFeature = feature;
                    thres = thresholds[i];
                }
            }
        }
    }
    node->feature = maxFeature;
    node->threshold = thres;
    vector<Iris> left;
    vector<Iris> right;
    split_dataset_by_feature(dataset,maxFeature,thres,left,right);
    vector<string> f = remove_feature(features,maxFeature);
    node->left_child = build_tree_helper(left,f);
    node->right_child = build_tree_helper(right,f);
    return node;
    
}

double DecisionTree::information_gain(const vector<Iris> &dataset, const string &feature, double &threshold) {
    // TODO: implement this function
    double sum=0;
    vector<Iris> left;
    vector<Iris> right;
    split_dataset_by_feature(dataset,feature,threshold,left,right);

    sum+=(double)left.size()/dataset.size()*entropy(left)+
         (double)right.size()/dataset.size()*entropy(right);
    return entropy(dataset)-sum;
}


double DecisionTree::gini_index(const vector<Iris> &dataset, const string &feature, double &threshold) {
    // TODO: implement this function'
    vector<Iris> left;
    vector<Iris> right;
    split_dataset_by_feature(dataset,feature,threshold,left,right);
    double lval=gini(left);
    double rval=gini(right);
    int llen = left.size();
    int rlen = right.size();
    int len = dataset.size();
    return double(llen)/len*lval+double(rlen)/len*rval;
}

double DecisionTree::gini(const vector<Iris> &dataset) {
    // TODO: implement this function
    int len = dataset.size();
    map<string,int> m;//count the size of each classification
    for(int i=0;i<len;i++)
    {
        m[dataset[i].variety]++;
    }
    double sum=0;
    for(auto it = m.begin();it!=m.end();it++)
    {
        sum+=pow((double)it->second/len,2);//calculate the segma part
    }

    return 1-sum;
}

double DecisionTree::entropy(const vector<Iris> &dataset) {
    // TODO: implement this function
    map<string,int> m;
    for(auto i : dataset)
    {
        m[i.variety]++;
    }
    double sum =0;
    int len = dataset.size();
    for(auto it = m.begin();it!=m.end();it++)
    {
        if(it->second!=0)
        sum+=double(it->second)/len * log2(double(it->second)/len);
    }
    return -sum;
}

vector<double> DecisionTree::generate_thresholds(const std::vector<Iris> &dataset, const std::string &feature) {
    // TODO: implement this function
    vector<double> res;
    //均值生成
    double minval = INT_MAX;
    double maxval = INT_MIN;
    for(auto i : dataset)
    {
        double val=iris_feature(i,feature);
        minval = min(val,minval);
        maxval = max(val,maxval);
    }
    const int sg=100;
    double step = (maxval-minval)/sg;
    for(int i=0;i<=sg;i++)
    {
        res.push_back(minval+i*step);
    }
    return res;
}

vector<string> DecisionTree::remove_feature(const vector<string> &features, const string &feature) {
    vector<string> result;
    for (const auto &f: features) {
        if (f != feature) {
            result.push_back(f);
        }
    }
    return result;
}

void DecisionTree::split_dataset_by_feature(const vector<Iris> &dataset, const string &feature, double threshold,
                                            vector<Iris> &left_dataset, vector<Iris> &right_dataset) {
    for (const auto &iris: dataset) {
        if (iris_feature(iris, feature) <= threshold) {
            left_dataset.push_back(iris);
        } else {
            right_dataset.push_back(iris);
        }
    }
}

void DecisionTree::print() const {
    print_helper(root_, 0);
}

void DecisionTree::print_helper(const DecisionTree::Node *node, int indent) const {
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < indent; i++) {
        cout << " ";
    }
    if (node->label.empty()) {
        cout << node->feature << " <= " << node->threshold << endl;
        print_helper(node->left_child, indent + 4);
        print_helper(node->right_child, indent + 4);
    } else {
        cout << node->label << endl;
    }
}


