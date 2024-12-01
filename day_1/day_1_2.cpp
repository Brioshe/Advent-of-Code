#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

int 
{
    std::ifstream inputFile("input.txt");

    if (!inputFile)
    { // Check that inputFile imports correctly.
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::vector<int> leftList;
    std::vector<int> rightList;
    int left, right;

    // Create vector lists for each column of inputFile.
    while (inputFile >> left >> right)
    {
        leftList.push_back(left);
        rightList.push_back(right);
    }

    inputFile.close();

    // Sort lists
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    int similarityScore = 0;
    for (size_t i = 0; i < leftList.size(); i++)
    {
        int comparator = leftList[i];
        int count = std::count(rightList.begin(), rightList.end(), comparator);

        similarityScore += comparator * count;
    }

    std::cout << "Similarity Score: " << similarityScore << std::endl;

    return 0;
}