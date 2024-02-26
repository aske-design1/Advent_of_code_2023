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
    for(const std::string& line : input)
        res += Arrangements(line);
    return res;
}

int Arrangements(const std::string& line){
    int split = (int) line.find(' ');
    std::string row = line.substr(0, split);
    std::vector<int> numbers;
    stringToNumbers(line.substr(split), numbers); //Takes last part of string with numbers and the variable Numbers is updated through a reference

    //Logic here
    return checkArrangementRec(row, numbers, 0, 0);

}

void stringToNumbers(const std::string& str, std::vector<int>& numbers) {
    for(const char& ch : str)
        if(isdigit(ch))
            numbers.push_back(ch - '0');
}

int checkArrangementRec(std::string& str, std::vector<int>& numArr, int strIndex, int numIndex){
    if (numIndex + 1 >= numArr.size()) { // If all numbers have been cycled through
        return 1;

    } else if(strIndex + 1 >= str.size()) { // If we have reached the end of the string and not all numbers have been cycled through
        return 0;

    } else if (str[strIndex] == '?') { // If the given char is a ? then this line of logic is followed
        if(checkIfPossible(str.substr(strIndex, numArr[numIndex] + 1))) { //Takes the substring that goes from the current char to the length of the given group
            return checkArrangementRec(str, numArr, strIndex + numArr[numIndex] + 1, numIndex + 1) +
            checkArrangementRec(str, numArr, strIndex + 1, numIndex);
        } else {
            return checkArrangementRec(str, numArr, strIndex + 1, numIndex);
        }

    } else if (str[strIndex] == '#') { // If the given char is a # then this line of logic is followed
        if(checkIfPossible(str.substr(strIndex, numArr[numIndex] + 1))) {
            return checkArrangementRec(str, numArr, strIndex + numArr[numIndex] + 1, numIndex + 1) +
                   checkArrangementRec(str, numArr, strIndex + 1, numIndex);
        } else
            return 0;

    } else { // If the given char is a '.' then this line of logic is followed
        return checkArrangementRec(str, numArr, strIndex + 1, numIndex);
    }
}



bool checkIfPossible(std::string substr) {
    int i;
    for(i = 0; i < substr.size() - 1; i++)
        if(substr[i] == '.') return false;
    return substr[i] != '#';
}


/* std::cout << row;
   for(const int& num : numbers) {
       std::cout << " " << num;
   }
   std::cout << std::endl;*/

/*
Pseudo code for recursive function:
    int rec(str, numArr, index, numCounter)
        if index >= size || numCounter + 1 >= numArr.size()
            return numCounter + 1 >= numArr.size() ? 1 : 0;
        else if str[index] == ?
            if(checkifpossible())
                return recfunc(str, numArr, index + num + 1, numCounter + 1)
                    + recfunc(str, numArr, index + 1, numCounter)
            else if(numArr[numCounter] + index >= size
                return 0;
            else
                return recfunc(str, numArr, index + 1, numCounter);
        else if str[index] == #
            if(check if possible())
                return recfunc(str, numArr, index + num + 1, numCounter + 1)
            else
                return 0;
        else
            recfunc(str, numArr, index + 1, numCounter)

        checkifpossible(str.substr(index, numArr[numCounter] + 1))
*/