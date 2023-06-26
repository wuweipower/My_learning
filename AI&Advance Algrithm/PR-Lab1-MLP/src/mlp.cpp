#include "mlp.h"
#include <cstdlib>
#include <cmath>
#include <cstdio>

using namespace std;
vector<double> input;
MLP::MLP(int input_dim, int hidden_dim, int output_dim) {
    // Randomly initialize the weights and biases
    W1 = vector<vector<double>>(hidden_dim, vector<double>(input_dim, 0));
    W2 = vector<vector<double>>(output_dim, vector<double>(hidden_dim, 0));
    printf("W1 %d*%d\n",W1.size(),W1[0].size());
    printf("W2 %d*%d\n",W2.size(),W2[0].size());
    b1 = vector<double>(hidden_dim, 0);
    b2 = vector<double>(output_dim, 0);
    printf("b1: %d b2: %d\n",b1.size(),b2.size());
    // TODO: initialize W1, W2, b1, b2
    // Your code here
    //use the random() function to init
    for(int i=0;i<W1.size();i++)
    {
        for(int j=0;j<W1[i].size();j++)
        {
            W1[i][j] = random(-1,1);
        }
    }
    for(int i=0;i<W2.size();i++)
    {
        for(int j=0;j<W2[i].size();j++)
        {
            W2[i][j] = random(-1,1);
        }
    }
    for(int i=0;i<b1.size();i++)b1[i]=random(-1,1);
    for(int i=0;i<b2.size();i++)b2[i]=random(-1,1);
    // Your code ends here
    // Initialize the gradients
    W1_grad = vector<vector<double>>(W1.size(), vector<double>(W1[0].size(), 0));
    W2_grad = vector<vector<double>>(W2.size(), vector<double>(W2[0].size(), 0));
    b1_grad = vector<double>(b1.size(), 0);
    b2_grad = vector<double>(b2.size(), 0);
}

void MLP::zero_grad() {
    for (auto &i: W1_grad) {
        fill(i.begin(), i.end(), 0);
    }
    for (auto &i: W2_grad) {
        fill(i.begin(), i.end(), 0);
    }
    fill(b1_grad.begin(), b1_grad.end(), 0);
    fill(b2_grad.begin(), b2_grad.end(), 0);
}


vector<double> MLP::forward(const vector<unsigned char> &x) {
    // TODO: implement forward propagation
    // Your code here
    //remenber the input which will be used in BP
    input.clear();
    for(int i =0;i<x.size();i++)
    {
        input.push_back(x[i]);//784
    }   
    unactivated_outputs.clear();
    activated_outputs.clear();
    vector<double>sum(W1.size(),0);
    //这个矩阵的设计是hidden_dim*input_dim所以直接针对每个nueral,计算weight和input的线性和
    //然后加上bias就可以了
    //最有activate一下就欧克了
    for(int i =0;i<W1.size();i++)
    {      
        for(int j=0;j<W1[i].size();j++)
        {
            sum[i]+=W1[i][j]*static_cast<double>(x[j]);     
        }
        sum[i]+=b1[i];    
    }
    unactivated_outputs.push_back(sum);
    sum = sigmoid(sum);
    activated_outputs.push_back(sum);
    vector<double> res(W2.size(),0);
    //如上，操作和前面一样
    for(int i =0;i<W2.size();i++)
    {      
        for(int j=0;j<W2[i].size();j++)
        {
            res[i]+=W2[i][j]*sum[j];
        }
        res[i]+=b2[i];
    }
    unactivated_outputs.push_back(res);
    vector<double> temp = softmax(res);
    activated_outputs.push_back(temp);
    return temp;
    // Make compiler happy :)
    // Your code ends here
}

void MLP::backward(const vector<double> &y, const vector<double> &y_hat) {
    // TODO: implement backward propagation
    // Your code here

    //直接获得输出层到隐藏层的梯度
    W2_grad = outer_product(d_softmax_cross_entropy(y,y_hat),activated_outputs[0]);
    b2_grad = d_softmax_cross_entropy(y,y_hat);

    //it is the part of partialJ/partialY 通用的部分，最左边的那两个乘积
    auto part_grad = d_softmax_cross_entropy(y,y_hat);
    //隐藏层的激活函数的求导 要使用没激活前的数据，因为助教这个函数又sigmoid一下
    auto ds = d_sigmoid(unactivated_outputs[0]);

    vector<double> y_;//partial J over partial y
    //按照列遍历 找对于某个隐藏层的神经元，遍历对输出元的weight 参考公式在ppt上
    for(int i =0;i<W2[0].size();i++)
    {
        double sum=0;//用来存前面part_grad与对应Wkj的乘积和
        for(int j=0;j<W2.size();j++)
        {
            sum+=part_grad[j]*W2[j][i];
        }
        y_.push_back(sum);
    }
    //然后根据ppt的公式更新参数
    for(int i=0;i<W1_grad.size();i++)
    {
        for(int j=0;j<W1_grad[0].size();j++)
        {
            W1_grad[i][j] = ds[i]*y_[i]*input[j];
        }
    }

    //更新b1的梯度数组
    for(int i=0;i<W1_grad.size();i++)
    {
        b1_grad[i]= ds[i]*y_[i];
    }

    // Your code ends here
}

void MLP::update(double lr) {
    // TODO: implement weight update
    // Your code here
    //直接就是用原来的值减去梯度乘以学习率
    for(int i=0;i<W1.size();i++)
    {
        for(int j =0;j<W1[i].size();j++)
        {
            W1[i][j]-=lr*W1_grad[i][j];
        }
      //  b1[i]-=lr*b1_grad[i];
    }
    for(int i=0;i<W2.size();i++)
    {
        for(int j =0;j<W2[i].size();j++)
        {
            W2[i][j]-=lr*W2_grad[i][j];
        }
       // b2[i]-=lr*b2_grad[i];
    }
    vector_multiply(b1_grad,-lr);
    vector_add(b1,b1_grad);
    vector_multiply(b2_grad,-lr);
    vector_add(b2,b2_grad);
    
    // Your code ends here
}

MLP::~MLP() = default;
