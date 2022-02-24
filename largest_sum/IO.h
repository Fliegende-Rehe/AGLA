//
// Created by Admin on 23.02.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void Write(const string &output, const string& PATH) {
    cout << output;
    ofstream file;
    file.open(PATH);
    file << output;
    file.close();
}

string Read(const string& PATH) {
    string line, input;
    ifstream file(PATH);
    if (!file.is_open()) return "Unable to open file";
    while (getline(file, line))input += line;
    file.close();
    cout << input << "\n";
    return input;
}