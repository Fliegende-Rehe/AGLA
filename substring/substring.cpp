#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<int> Counter(const vector<string>& combinations, string text);
vector<string> Combinator(vector<string> words);
vector<string> Parser(string input);
void Write(const string &output);
string asString(vector<int> n);
vector<string> Read();
int factorial(int i);

int main() {
    vector<string> input = Read();

    vector<string> words = Parser(input[2]);

    vector<string> combinations = Combinator(words);

    string text = input[0];

    vector<int> indexes = Counter(combinations, text);

    sort(indexes.begin(), indexes.end());

    Write(asString(output));

    return 0;
}

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

string asString(vector<int> n) {
    string output;
    for(int i : n) output += to_string(i) + " ";
    return output;
}


vector<string> Parser(string input) {
    vector<string> words;
    stringstream stream(input);
    string w;
    while (stream >> w) words.push_back(w);
    return words;
}

int factorial(int i) {
    if (i == 0) return 1;
    else return i * factorial(i - 1);
}

vector<string> Combinator(vector<string> words) {
    vector<string> combination;
    int n = factorial(words.size());
    string variant;
    for (int i = 0; i < n; i++) {
        for(string w : words) variant += w;
        combination.push_back(variant);
        variant = "";
        next_permutation(words.begin(), words.end());
    }
    return combination;
}

vector<int> Counter(const vector<string>& combinations, string text) {
    vector<int> indexes;
    for(const string& variant : combinations) {
        string copy = text;
        for (int i = 0; i < copy.length(); ++i) {
            if(i == copy.find(variant)) {
                indexes.push_back(i);
                copy[i] = '$';
            }
        }
    }
    return indexes;
}


