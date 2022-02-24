#include <vector>
#include <sstream>
#include "../IO.h"

using namespace std;

vector<int> parseInt(string str) {
    vector<int> output;
    stringstream stream(str);
    string word;
    while (stream >> word) output.push_back(stoi(word));
    return output;
}

string largestSum(const vector<int>& input) {
    int output = 0, sum = 0;
    for (int i : input) {
        sum += i;
        output = max(output, sum);
        if (sum < 0) sum = 0;
    }
    return to_string(output);
}

int main() {
    string input = Read();

    vector<int> array = parseInt(input);

    string output = largestSum(array);

    Write(output);

    return 0;
}