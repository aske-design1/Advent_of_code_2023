#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

void ReadFile(const std::string& filename, std::vector<std::vector<std::string>>& paragraphs);
int calculateStoneNorth(const std::vector<std::string>& strings, int y, int x, int totalRows);
int calculateLoad(const std::vector<std::string>& strings);
int Part1(const std::vector<std::vector<std::string>>& stringArray);
void StringCycler(std::vector<std::string>* strings);

int main() {

    std::vector<std::vector<std::string>> stringArray;
    ReadFile("test.txt", stringArray);

    int answer = Part1(stringArray);
    std::cout << "Answer for part 1: " << answer << std::endl;

    return 0;
}

void ReadFile(const std::string& filename, std::vector<std::vector<std::string>>& paragraphs) {
    std::ifstream file(filename);
    std::vector<std::string> currentParagraph;
    std::string line;

    if(file.is_open()) {
        while(std::getline(file, line)) {
            if(line.empty()){
                paragraphs.push_back(currentParagraph);
                currentParagraph.clear();
            } else {
                currentParagraph.push_back(line);
            }
        }

        if(!currentParagraph.empty()){
            paragraphs.push_back(currentParagraph);
        }
        file.close();
    } else
        std::cout << "Error opening file" << std::endl;
}

int part2(const std::vector<std::vector<std::string>>& stringArray) {
    int sum = 0;
    int cycles;
    int resultOfFirstCycle;
    int resultCycle;

    //so, first figure out the length of a loop of cycles. Essientially, how long does it take for our result to equal the first result



    for (auto& strings : stringArray) {
        std::vector<std::string> stringToChange = strings;
        resultOfFirstCycle = StringCycler(stringToChange);
        while(resultOfFirstCycle != resultOfFirstCycle)


        for(int i = 0; i < 1000; i++) {
            StringCycler(&stringToChange);
        }

        sum += calculateLoad(stringToChange);
    }
    return sum;
}

int Part1(const std::vector<std::vector<std::string>>& stringArray) {

    int sum = 0;
    for (const auto& strings : stringArray) {

        sum += calculateLoad(strings);
    }
    return sum;
}

int calculateLoad(const std::vector<std::string>& strings) {
    int ySize = (int)strings.size(), xSize = (int)strings[0].size();
    int load = 0;
    int loadForEach;

    for(int y = 0; y < ySize; y++) {
        for(int x = 0; x < xSize; x++) {
            if(strings[y][x] == 'O') {
                loadForEach = 0;
                loadForEach += calculateStoneNorth(strings, y, x, ySize);

                //std::cout << "x: " << x << " y: " << y << " \nloadForEach " << loadForEach << std::endl;

                load += loadForEach;
            }

        }
    }

    return load;
}

int calculateStoneNorth(const std::vector<std::string>& strings, int y, int x, const int totalRows) {
    int rocksAbove = 0;
    //Decrement as we are looking for the one above;
    y--;

    for(; y >= 0; y--) {
        if(strings[y][x] == 'O') {
            rocksAbove++;
        } else if(strings[y][x] == '#') {
            return totalRows - (y + 1) - rocksAbove;
        }
    }

    return totalRows - rocksAbove;
}

int StringCycler(std::vector<std::string>& strings) {
    // Each cycle tilts the platform four times so that the rounded rocks roll north, then west, then south, then east.

    //Tilt North


    //Tilt West

    //Tilt South

    //Tilt East


}