#include <vector>
#include <iostream>
#include "LightGBMWrapper.h"

int main() {
    std::cout << "请选择操作模式：\n";
    std::cout << "1. 训练模型\n";
    std::cout << "2. 进行预测\n";
    std::cout << "请输入数字 (1 或 2)：";

    int choice;
    std::cin >> choice;

    LightGBMWrapper lgb;

    if (choice == 1) {
        std::vector<double> train_data = {
            1.0, 0.2, 0.5,
            0.9, 0.4, 0.7
        };
        std::vector<float> train_labels = {0, 1};
        lgb.train(train_data, train_labels, 2, 3);
    } else if (choice == 2) {
        std::vector<double> features = {1.2, 0.3, 0.8};
        lgb.predict(features, 3);
    } else {
        std::cerr << "❗ 无效选项，请输入 1 或 2\n";
        return 1;
    }

    return 0;
}