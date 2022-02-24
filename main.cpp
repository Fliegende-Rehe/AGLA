#include <vector>
#include <sstream>
#include "IO.h"

using namespace std;

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

string Counter(vector<string> combinations, string text) {
    string output;
    for(string c : combinations) {
        text.find(c);
    }
    return output;
}

vector<int> find(string arr, string value) {
    vector<int> indexes;

    while() {
        int i = arr.find(value);
        indexes.push_back(i);
        arr.replace(i, 0, 0, 's');
    }


    return indexes;
}

int main() {
    vector<string> input = Read();

    string text = input[0];

    vector<string> words = Parser(input[2]);

    vector<string> combinations = Combinator(words);


    return 0;
}
