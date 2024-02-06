#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

void readFile(const std::string& filename, std::vector<std::vector<std::string>>& paragraphs);
int part1(const std::vector<std::vector<std::string>>& stringArray);
int part2(std::vector<std::vector<std::string>>& stringArray);
int calculateRows(std::vector<std::string> strings, int startIndex);
int calculateColumns(std::vector<std::string> strings, int startIndex);
char smudgeFixer(char ch);
int smudgeFinderForRowsAdv(std::vector<std::string>& strings, int* smudgeCord, int& rows, int& columns, int startIndex);
int findSymmetryWithSmudge(std::vector<std::string>& strings, int* smudgeCord);
int smudgeFinderForColumnsAdv(std::vector<std::string>& strings, int* smudgeCord, int& rows, int& columns, int startIndex);

int main() {

    std::vector<std::vector<std::string>> stringArray;
    readFile("test.txt", stringArray);

    /*for (const auto& paragraph : stringArray) {
        for (const auto& line : paragraph) {
            std::cout << line << std::endl;
        }
        std::cout << "=== New Paragraph ===" << std::endl;
    }*/

    //int answer = part1(stringArray);
    //std::cout << "\n\nThe answer for part 1 is: " << answer << std::endl;
    int answer2 = part2(stringArray);
    std::cout << "\n\nThe answer for part 2 is: " << answer2 << std::endl;

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
        int sum2 = 0;
        sum2 += calculateRows(strings, 0);

        sum2 += calculateColumns(strings, 0);
        std::cout << sum2 << std::endl;
        sum += sum2;
    }

    return sum;
}

int part2(std::vector<std::vector<std::string>>& stringArray) {
    int sum = 0;
    int* smudgeCoordinates = new int[2];

    for(std::vector<std::string>& strings : stringArray) {
        sum += findSymmetryWithSmudge(strings, smudgeCoordinates);
    }

    delete(smudgeCoordinates);
    return sum;
}


int calculateRows(std::vector<std::string> strings, int startIndex) {


    int columns = strings[0].size(), rows = strings.size();
    int half = ceil((double) rows / 2);
    if(rows % 2 == 1)
        half++;

    int i;
    bool flag = false;

    for(i = startIndex; i < rows - 1; i++) {
        flag = true;

        for (int j = 0; j < columns; j++) {
            if (strings[i][j] != strings[i + 1][j]) {
                flag = false;
                break;
            }
        }

        if(flag) {
            break;
        }
    }

    if(!flag) {
        return 0;
    } else if(rows - (i + 1) >= half) {
        int compareDif = 3;
        for(int k = i - 1; k >= 0; k--){
            for(int j = 0; j < columns; j++) {
                if(strings[k][j] != strings[k + compareDif][j]){
                    return calculateRows(strings, i + 1 );
                }

            }
            compareDif+=2;
        }

    } else {
        int compareDif = -3;

        for(int k = i + 2; k < rows; k++){
            for(int j = 0; j < columns; j++) {
                if(strings[k][j] != strings[k + compareDif][j]){
                    return calculateRows(strings, i + 1);
                }
            }
            compareDif-=2;
        }
    }

    return (i + 1) * 100;
}

int calculateColumns(std::vector<std::string> strings, int startIndex) {
    int columns = strings[0].size(), rows = strings.size();
    int half =ceil((double) columns / 2);

    int i;
    bool twoIdenticals = false;

    for(i = startIndex; i < columns - 1; i++) {
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
        std::cout << startIndex + 1 << std::endl;
        compareDif = 3;
        for(int k = i - 1; k >= 0; k--){
            for(int j = 0; j < rows; j++) {
                if(strings[j][k] != strings[j][k + compareDif]){
                    return calculateColumns(strings, i + 1);
                }

            }
            compareDif+=2;
        }

    } else {
        std::cout << startIndex + 1 << std::endl;
        compareDif = -3;
        for(int k = i + 2; k < columns; k++){
            for(int j = 0; j < rows; j++) {
                if(strings[j][k] != strings[j][k + compareDif]){
                    return calculateColumns(strings, i + 1 );
                }
            }
            compareDif-=2;
        }
    }

    return i + 1;
}

int findSymmetryWithSmudge(std::vector<std::string>& strings, int* smudgeCord) {
    int sum = 0, difCounter;
    int rows = strings.size(), columns = strings[0].size();
    bool flag = false;

    //Loop through columns:
    for(int i = 0; i < columns - 1; i++) {
        difCounter = 0;
        for(int j = 0; j < rows; j++) {
            if(strings[j][i] != strings[j][i + 1]) {
                difCounter++;
                smudgeCord[0] = j;
                smudgeCord[1] = i;
            }
        }

        if(difCounter == 1){
            strings[smudgeCord[0]][smudgeCord[1]] = smudgeFixer(strings[smudgeCord[0]][smudgeCord[1]]);
            flag = true;
            break;
        }
    }
    if(flag)
        return calculateColumns(strings, 0);

    sum += smudgeFinderForColumnsAdv(strings, smudgeCord, rows, columns, 0);
    if(sum != 0) {
        return sum;
    }

    //Loop through rows
    flag = false;
    for(int i = 0; i < rows - 1; i++) {
        difCounter = 0;
        for(int j = 0; j < columns; j++) {
            if(strings[i][j] != strings[i + 1][j]) {
                difCounter++;
                smudgeCord[0] = j;
                smudgeCord[1] = i;
            }
        }

        if(difCounter == 1){
            strings[smudgeCord[1]][smudgeCord[0]] = smudgeFixer(strings[smudgeCord[1]][smudgeCord[0]]);
            flag = true;
            break;
        }
    }
    if(flag)
        return calculateRows(strings, 0);

    sum += smudgeFinderForRowsAdv(strings, smudgeCord, rows, columns, 0);

    return sum;
}

int smudgeFinderForColumnsAdv(std::vector<std::string>& strings, int* smudgeCord, int& rows, int& columns, int startIndex) {

    int i;
    bool flag;
    int half = ceil((double)columns / 2);
    int difCounter;


    for(i = startIndex; i < columns - 1; i++) {
        flag = true;

        for (int j = 0; j < rows; j++) {
            if (strings[j][i] != strings[j][i + 1]) {
                flag = false;
                break;
            }
        }

        if(flag)
            break;
    }

    if(!flag)
        return 0;

    else if(columns - (i + 1) >= half ) {
        int compareDif = 3;
        for(int k = i - 1; k >= 0; k--){
            difCounter = 0;
            for(int j = 0; j < rows; j++) {
                if(strings[j][k] != strings[j][k + compareDif]){
                    difCounter++;
                    smudgeCord[0] = j;
                    smudgeCord[1] = k;
                }

            }

            if(difCounter > 1)
                return smudgeFinderForColumnsAdv(strings, smudgeCord, rows, columns, startIndex);

            compareDif+=2;
        }

    } else {
        int compareDif = -3;
        for (int k = i + 2; k < columns; k++) {
            difCounter = 0;
            for (int j = 0; j < rows; j++) {
                if (strings[j][k] != strings[j][k + compareDif]) {
                    difCounter++;
                    smudgeCord[0] = j;
                    smudgeCord[1] = k;
                }

            }

            if (difCounter > 1)
                return smudgeFinderForColumnsAdv(strings, smudgeCord, rows, columns, startIndex);


            compareDif -= 2;

        }
    }

    return (i + 1) * 100;


}

int smudgeFinderForRowsAdv(std::vector<std::string>& strings, int* smudgeCord, int& rows, int& columns, int startIndex) {
    int i;
    bool flag;
    int half = ceil((double)rows / 2);
    int difCounter = 0;


    for(i = startIndex; i < rows - 1; i++) {
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

    if(!flag)
        return 0;

    else if(rows - (i + 1) >= half ) {
        int compareDif = 3;
        for(int k = i - 1; k >= 0; k--){
            difCounter = 0;
            for(int j = 0; j < columns; j++) {
                if(strings[k][j] != strings[k + compareDif][j]){
                    difCounter++;
                    smudgeCord[0] = k;
                    smudgeCord[1] = j;
                }

            }

            if(difCounter > 1)
                return smudgeFinderForRowsAdv(strings, smudgeCord, rows, columns, startIndex);


            compareDif+=2;
        }

    } else {
        int compareDif = -3;
        for (int k = i + 2; k < rows; k++) {
            difCounter = 0;
            for (int j = 0; j < columns; j++) {
                if (strings[k][j] != strings[k + compareDif][j]) {
                    difCounter++;
                    smudgeCord[0] = k;
                    smudgeCord[1] = j;
                }

            }

            if (difCounter > 1)
                return smudgeFinderForRowsAdv(strings, smudgeCord, rows, columns, startIndex);


            compareDif -= 2;

        }
    }

    return (i + 1) * 100;
}


char smudgeFixer(char ch) {
    switch(ch) {
        case '#':
            return '.';
        case '.':
            return '#';
    }
}
