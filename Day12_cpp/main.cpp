#include "functions.h"



int main() {
    std::string file = "testcase.txt";
    std::vector<std::string> input;
    ReadFile(file, input);

    std::cout << "Part 1 answer: \n\n\n" << PartOne(input) << std::endl;

    return 0;
}
