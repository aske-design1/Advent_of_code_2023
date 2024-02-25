#include "functions.h"

void ReadFile(const std::string& filename, std::vector<std::string>& stringArray) {
    std::ifstream file(filename);
    std::string line;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            stringArray.push_back(line);
        }

        file.close();
    } else
        std::cout << "Error opening file" << std::endl;
}

int PartOne(const std::vector<std::string>& input) {
    int res = 0;
    for(const std::string& line : input) {
        res += Arrangements(line);
    }
    return res;
}

int Arrangements(const std::string& line){
    int split = (int) line.find(' ');
    std::string row = line.substr(0, split);
    std::string numStr = line.substr(split);
    std::vector<int> numbers;
    stringToNumbers(numStr, numbers); //Numbers is updated through a reference

    int arrangements = 0;
    //Logic here
    for(int i = 0; i < row.size(); i++) {
        if(row[i] == '?' && checkArrangementRec(row, numbers, i, 0)) {
            arrangements++;
        }
    }



    return arrangements;
}

void stringToNumbers(std::string& str, std::vector<int>& numbers) {
    for(const char& ch : str)
        if(isdigit(ch))
            numbers.push_back(ch - '0');
}

bool checkArrangementRec(std::string& row, std::vector<int>& numbers, int currentCh, int numberIndex){

}

/* std::cout << row;
   for(const int& num : numbers) {
       std::cout << " " << num;
   }
   std::cout << std::endl;*/