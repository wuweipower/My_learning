# MLP Cpp
> MLp implementation in C++.


<p>
  <a href="https://raw.githubusercontent.com/songquanpeng/mlp-cpp/main/LICENSE">
    <img src="https://img.shields.io/github/license/songquanpeng/mlp-cpp?color=brightgreen" alt="license">
  </a>
  <a href="https://github.com/songquanpeng/mlp-cpp/releases/latest">
    <img src="https://img.shields.io/github/v/release/songquanpeng/mlp-cpp?color=brightgreen&include_prereleases" alt="release">
  </a>
  <a href="https://github.com/songquanpeng/mlp-cpp/releases/latest">
    <img src="https://img.shields.io/github/downloads/songquanpeng/mlp-cpp/total?color=brightgreen&include_prereleases" alt="release">
  </a>
</p>

## Build
```shell
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Usages
```shell
./mlp -d data --l 0.01 -e 10 -h 10
```

## Results
```
Training images: 60000 x 784
Training labels: 60000      
Test images: 10000 x 784    
Test labels: 10000
Epoch: 0, Iteration: 0, Loss: 3.508825
Epoch: 0, Iteration: 1000, Loss: 5.356829
Epoch: 0, Iteration: 2000, Loss: 3.998574
Epoch: 0, Iteration: 3000, Loss: 3.326644
Epoch: 0, Iteration: 4000, Loss: 2.967481
Epoch: 0, Iteration: 5000, Loss: 2.543284
Epoch: 0, Iteration: 6000, Loss: 2.402526
Epoch: 0, Iteration: 7000, Loss: 2.293073
Epoch: 0, Iteration: 8000, Loss: 2.221855
Epoch: 0, Iteration: 9000, Loss: 1.963259
Epoch: 0, Iteration: 10000, Loss: 1.766427
Epoch: 0, Iteration: 11000, Loss: 1.676143
```