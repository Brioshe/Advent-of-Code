#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::ostringstream buffer;
    buffer << inputFile.rdbuf();
    std::string fileContent = buffer.str();
    std::cout << fileContent << std::endl;

    std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    std::sregex_iterator begin(fileContent.begin(), fileContent.end(), pattern);
    std::sregex_iterator end;
    
    int instructionTotal = 0;

    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch match = *it;

        int number1 = std::stoi(match[1].str());
        int number2 = std::stoi(match[2].str());
        std::cout << number1 << " " << number2 << std::endl;

        instructionTotal += number1 * number2;
    }

    std::cout << "Total result of instructions: " << instructionTotal << std::endl;
}