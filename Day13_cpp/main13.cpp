#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

void readFile(const std::string& filename, std::vector<std::vector<std::string>>& paragraphs);
int part1(const std::vector<std::vector<std::string>>& stringArray);
int calculateRows(std::vector<std::string> strings);
int calculateColumns(std::vector<std::string> strings);

int main() {

    std::vector<std::vector<std::string>> stringArray;
    readFile("input.txt", stringArray);

    /*for (const auto& paragraph : stringArray) {
        for (const auto& line : paragraph) {
            std::cout << line << std::endl;
        }
        std::cout << "=== New Paragraph ===" << std::endl;
    }*/

    int answer = part1(stringArray);
    std::cout << "\n\nThe answer for part 1 is: " << answer << std::endl;


    return 0;
}

/**
 * Reads the file and puts it into an array of an array of strings.
 * */
void readFile(const std::string& filename, std::vector<std::vector<std::string>>& paragraphs) {
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

int part1(const std::vector<std::vector<std::string>>& stringArray) {
    int sum = 0;

    for(const auto& strings : stringArray) {
        sum += calculateRows(strings);

        sum += calculateColumns(strings);
    }

    return sum;
}

int calculateRows(std::vector<std::string> strings) {
    int columns = strings[0].size(), rows = strings.size();
    int half = rows / 2;
    if(rows % 2 == 1)
        half++;
    int i;
    bool flag;

    for(i = 0; i < rows - 1; i++) {
        flag = true;

        for (int j = 0; j < columns; j++) {
            if (strings[i][j] != strings[i + 1][j]) {
                flag = false;
                break;
            }
        }

        if(flag)
            break;
    }



    if(!flag) {
        return 0;
    } else if(rows - (i + 1) >= half) {
        int compareDif = 3;
        for(int k = i - 1; k >= 0; k--){
            for(int j = 0; j < columns; j++) {
                if(strings[k][j] != strings[k + compareDif][j]){
                    return 0;
                }

            }
            compareDif+=2;
        }

    } else {
        int compareDif = -3;
        for(int k = i + 2; k < rows; k++){
            for(int j = 0; j < columns; j++) {
                if(strings[k][j] != strings[k + compareDif][j]){
                    return 0;
                }
            }
            compareDif-=2;
        }
    }

    return (i + 1) * 100;
}

int calculateColumns(std::vector<std::string> strings) {
    int columns = strings[0].size(), rows = strings.size();
    int half = columns / 2;
    if(columns % 2 == 1) {
        half++;
    }
    int i;
    bool twoIdenticals;

    for(i = 0; i < columns - 1; i++) {
        twoIdenticals = true;

        for (int j = 0; j < rows; j++) {
            if (strings[j][i] != strings[j][i + 1]) {
                twoIdenticals = false;
                break;
            }
        }
        if (twoIdenticals) {
            break;
        }
    }

    int compareDif;

    if(!twoIdenticals)
        return 0;

    else if(columns - (i + 1) >= half) {
        compareDif = 3;
        for(int k = i - 1; k >= 0; k--){
            for(int j = 0; j < rows; j++) {
                if(strings[j][k] != strings[j][k + compareDif]){
                    return 0;
                }

            }
            compareDif+=2;
        }

    } else {
        compareDif = -3;
        for(int k = i + 2; k < columns; k++){
            for(int j = 0; j < rows; j++) {
                if(strings[j][k] != strings[j][k + compareDif]){
                    return 0;
                }
            }
            compareDif-=2;
        }
    }

    return i + 1;
}