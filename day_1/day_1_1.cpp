#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) { // Check that inputFile imports correctly.
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::vector<int> leftList;
    std::vector<int> rightList;
    int left, right;

    // Create vector list for each column of inputFile.
    while (inputFile >> left >> right) {
        leftList.push_back(left);
        rightList.push_back(right);
    }

    inputFile.close();

    // Test to make sure each list is input correctly by verifying each size.
    std::cout << "Left List Size: " << leftList.size() << std::endl;
    std::cout << "Right List Size: " << rightList.size() << std::endl;

    // Sort lists
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    // Calculate distance of each list according to ruleset.
    int totalDistance = 0;
    for (size_t i = 0; i < leftList.size(); i++) {
        totalDistance += std::abs(leftList[i] - rightList[i]); // abs to assure nonnegative
    }

    std::cout << "Total distance: " << totalDistance << std::endl;

    return 0;
}