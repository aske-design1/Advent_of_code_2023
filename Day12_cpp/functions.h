#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

void ReadFile(const std::string& filename, std::vector<std::string>& paragraphs);
int PartOne(const std::vector<std::string>& input);
int Arrangements(const std::string& line);
void stringToNumbers(std::string& str, std::vector<int>& numbers);
bool checkArrangementRec(std::string& row, std::vector<int>& numbers, int currentCh, int numberIndex);