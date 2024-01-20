#include <iostream>
#include <yaml-cpp/yaml.h>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <my-lib/my_lib.hpp>
#include "src/test.hpp"

int main() {
    std::cout << "OpenCV version: " << cv::getVersionString() << std::endl;

    YAML::Node config = YAML::LoadFile("./../config.yaml");

    // パースしたデータを表示する
    std::cout << "name: " << config["name"].as<std::string>() << std::endl;
    std::cout << "age: " << config["age"].as<int>() << std::endl;
    std::cout << "height: " << config["email"].as<std::string>() << std::endl;

    my_lib_fanc();
    test_fanc();

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore();
    return 0;
}
