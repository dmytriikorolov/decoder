#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

vector<vector<int> > readTable(const string &filename){
    vector<vector<int> > table;
    ifstream inputFile(filename);

    if (!inputFile){
        cout << "Can't open file named " << filename << endl;
    }
    string line;
    while (getline(inputFile, line)){
        istringstream content(line);
        vector<int> row;
        int number;

        while (content >> number) {
            row.push_back(number);
        }
        table.push_back(row);
    }
    return table;
}

pair<string, string> decodeAscii(const vector<vector<int>> &table, bool flip = false) {
    string answer;
    string notAnswer;
    bool changed = false;

    for (const auto &row : table) {
        for (const auto &element : row) {
            int value = element;
            if (value > 127) {
                changed = true;
                value %= 127;
            }

            char c = static_cast<char>(value);
            answer.push_back(c);
            if (flip){
                char notC = static_cast<char>(~value);
                notAnswer.push_back(notC);
            }
            // TODO: maybe create additional parameter that will maintain row structure.
        }
    }

    if (changed) {
        cout << "Note: Some values in dataset were > 127 and have been changed to value mod 127. The text might not be decodable via ASCII" << endl;
    }

    return make_pair(answer, notAnswer);
}

string decodeUTF8(const vector<vector<int>> &table){

    for (const auto &row : table){
        for (const auto &element : row){
            if (element <= 0xFF){ // 1 byte
                //
            }
            else if (element <= 0x7FF){ // 2 bytes

            }
            else if (element <= 0xFFFF){

            } // 3 bytes
            else if (element <= 0x10FFFF){

            } //4 bytes
            else {
                return "Invalid input\n";
            }
        }
    }
}

int main() {
    string filename = "/Users/dima/CLionProjects/decypher/dataset.txt";
    vector<vector<int> > table = readTable(filename);

    pair<string, string> decoded = decodeAscii(table, true);
    // TODO: maybe think about how to give this parameters when args
    cout << "Decoded Message: " << endl << decoded.first << endl;
    cout << "Bitwise NOT Decoded Message: " << endl << decoded.second << endl;

    return 0;
}
