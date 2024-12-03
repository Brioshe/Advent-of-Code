#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

// Helper function to check if a sequence is safe (all increasing or all decreasing)
bool isSequenceSafe(const std::vector<int>& numbers) {
    bool isIncreasing = true;
    bool isDecreasing = true;

    for (size_t i = 1; i < numbers.size(); i++) {
        int diff = numbers[i] - numbers[i - 1];

        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;  // If any pair of adjacent levels is not within range
        }

        if (diff > 0) {
            isDecreasing = false;
        }
        if (diff < 0) {
            isIncreasing = false;
        }
    }

    return isIncreasing || isDecreasing;
}

// Main safe check function with Problem Dampener logic
bool isSafeCheck(const std::vector<int>& numbers, bool attemptRemaining) {
    if (isSequenceSafe(numbers)) {
        return true;  // If the sequence is safe as-is
    }

    if (!attemptRemaining) {
        return false;  // If we cannot use the dampener anymore
    }

    // Try removing one level at a time to see if it makes the sequence safe
    for (size_t i = 0; i < numbers.size(); i++) {
        std::vector<int> modifiedNumbers = numbers;
        modifiedNumbers.erase(modifiedNumbers.begin() + i);
        if (isSequenceSafe(modifiedNumbers)) {
            return true;  // Found a safe sequence by applying the dampener
        }
    }

    return false;  // No safe sequence could be formed
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> numbers;
    int safeCount = 0;

    while (std::getline(inputFile, line)) {
        std::stringstream inputStream(line);
        int number;

        numbers.clear();
        while (inputStream >> number) {
            numbers.push_back(number);
        }

        bool isSafe = isSafeCheck(numbers, true);
        if (isSafe) {
            safeCount++;
        }

        std::cout << "Report: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << (isSafe ? "SAFE" : "UNSAFE") << std::endl;
    }

    std::cout << "\nNumber of SAFE reports: " << safeCount << std::endl;

    inputFile.close();
    return 0;
}
