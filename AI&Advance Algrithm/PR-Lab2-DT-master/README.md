# Decision Tree
> A decision tree implementation in C++.


<p>
  <a href="https://raw.githubusercontent.com/songquanpeng/dtree-cpp/main/LICENSE">
    <img src="https://img.shields.io/github/license/songquanpeng/dtree-cpp?color=brightgreen" alt="license">
  </a>
  <a href="https://github.com/songquanpeng/dtree-cpp/releases/latest">
    <img src="https://img.shields.io/github/v/release/songquanpeng/dtree-cpp?color=brightgreen&include_prereleases" alt="release">
  </a>
  <a href="https://github.com/songquanpeng/dtree-cpp/releases/latest">
    <img src="https://img.shields.io/github/downloads/songquanpeng/dtree-cpp/total?color=brightgreen&include_prereleases" alt="release">
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
./dtree -d ./data/iris.csv -m gini_index
```

## Demonstrations
### Info Gain
```shell
./dtree -d ./data/iris.csv -m info_gain
[2023-04-22 12:23:32][INFO][main]: Metric: info_gain
[2023-04-22 12:23:32][INFO][main]: Dataset path: data/iris.csv
[2023-04-22 12:23:32][INFO][main]: Dataset loading...
[2023-04-22 12:23:32][INFO][main]: Dataset loaded, total 150 records.
[2023-04-22 12:23:32][INFO][main]: Decision tree trained.
[2023-04-22 12:23:32][INFO][main]: Predicting...
[2023-04-22 12:23:32][INFO][main]: Prediction accuracy: 97.333333%
[2023-04-22 12:23:32][INFO][main]: Congratulations! You have passed the test!
```

### Gini Index
```shell
./dtree -d ./data/iris.csv -m gini_index
[2023-04-22 12:25:02][INFO][main]: Metric: gini_index
[2023-04-22 12:25:02][INFO][main]: Dataset path: data/iris.csv
[2023-04-22 12:25:02][INFO][main]: Dataset loading...
[2023-04-22 12:25:02][INFO][main]: Dataset loaded, total 150 records.
[2023-04-22 12:25:02][INFO][main]: Decision tree trained.
[2023-04-22 12:25:02][INFO][main]: Predicting...
[2023-04-22 12:25:02][INFO][main]: Prediction accuracy: 97.333333%
[2023-04-22 12:25:02][INFO][main]: Congratulations! You have passed the test!
```