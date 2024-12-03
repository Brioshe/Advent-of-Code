#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Function to check if report is safe
bool isSafeCheck(const std::vector<int> &numbers)
{
    bool isIncreasing = true;
    bool isDecreasing = true;

    // Iterate over every number in report starting at 2nd element
    for (size_t i = 1; i < numbers.size(); i++)
    {
        int diff = numbers[i] - numbers[i - 1]; // Difference of prior element and current element

        if (abs(diff) < 1 || abs(diff) > 3) // Check to see if current difference is in range
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

    return isIncreasing || isDecreasing; // If no switch between increase and decrease occurs, only one will return true.
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
        std::stringstream inputStream(line); // Read in line as string stream
        int number;

        numbers.clear();
        while (inputStream >> number) // Input each element of string stream into an int 
        {
            numbers.push_back(number); // Push int to vector
        }

        if(isSafeCheck(numbers)) { // Run safety check
            safeCount++;
        }

        std::cout << "Report: ";
        for (int num: numbers) {
            std::cout << num << " ";
        }
        std::cout << (isSafeCheck(numbers) ? "SAFE" : "UNSAFE") << std::endl; // State each report and if it's safe or unsafe
    }

    std::cout << "\nNumber of SAFE reports: " << safeCount << std::endl; // State number of safe reports

    inputFile.close();

    return 0;
}