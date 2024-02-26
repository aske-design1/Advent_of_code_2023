#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

void ReadFile(const std::string& filename, std::vector<std::string>& paragraphs);
int PartOne(const std::vector<std::string>& input);
int Arrangements(const std::string& line);
void stringToNumbers(const std::string& str, std::vector<int>& numbers);
int checkArrangementRec(std::string& str, std::vector<int>& numArr, int strIndex, int numIndex);
bool checkIfPossible(std::string substr);