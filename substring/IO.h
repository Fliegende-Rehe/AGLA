//
// Created by Admin on 23.02.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void Write(const string &output) {
    cout << output;
    ofstream file;
    file.open("output.txt");
    file << output;
    file.close();
}

vector<string> Read() {
    string line;
    vector<string >input;
    ifstream file("input.txt");
    while (getline(file, line))
        input.push_back(line);
    file.close();
    return input;
}