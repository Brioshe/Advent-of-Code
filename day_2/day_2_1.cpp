#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool isSafeCheck(const std::vector<int> &numbers)
{
    bool isIncreasing = true;
    bool isDecreasing = true;

    for (size_t i = 1; i < numbers.size(); i++)
    {
        int diff = numbers[i] - numbers[i - 1];

        if (abs(diff) < 1 || abs(diff) > 3)
        {
            std::cout << "\n\nNOT WITHIN RANGE." << std::endl;
            return false;
        }

        if (diff > 0)
        {
                isDecreasing = false;
        }
        if (diff < 0)
        {
                isIncreasing = false;
        }
    }

    return isIncreasing || isDecreasing;
}

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile)
    {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> numbers;
    int safeCount = 0;

    while (std::getline(inputFile, line))
    {
        std::stringstream inputStream(line);
        int number;

        numbers.clear();
        while (inputStream >> number)
        {
            numbers.push_back(number);
        }

        if(isSafeCheck(numbers)) {
            safeCount++;
        }

        std::cout << "Report: ";
        for (int num: numbers) {
            std::cout << num << " ";
        }
        std::cout << (isSafeCheck(numbers) ? "SAFE" : "UNSAFE") << std::endl;
    }

    std::cout << "\nNumber of SAFE reports: " << safeCount << std::endl;

    inputFile.close();

    return 0;
}