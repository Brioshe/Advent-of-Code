#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>

int instructionOperation (std::string fileContent) {

    std::regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)");
    std::sregex_iterator begin(fileContent.begin(), fileContent.end(), pattern);
    std::sregex_iterator end;
    
    int instructionTotal = 0;
    bool mulEnabled = true;

    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch match = *it;
        std::string instruction = match.str();

        if (instruction == "do()") {
            mulEnabled = true;
        } else if (instruction == "don't()") {
            mulEnabled = false;
        } else if (instruction.substr(0, 4) == "mul(") {
            if (mulEnabled) {
                int number1 = std::stoi(match[1].str());
                int number2 = std::stoi(match[2].str());
                std::cout << number1 << " " << number2 << std::endl;

                instructionTotal += number1 * number2;
            }
        }
    }

    return instructionTotal;
}

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

    std::cout << "Total result of instructions: " << instructionOperation(fileContent) << std::endl;
}