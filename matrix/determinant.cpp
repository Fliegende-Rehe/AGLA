#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<double>> read();
vector<vector<double>> sub(vector<vector<int>> mat, int q, int n);
int det(vector<vector<double>> matrix, int n);
void write(int output);

int main() {
    vector<vector<double>> matrix = read();
    int determinant = det(matrix, matrix.size());
    write(determinant);
    return 0;
}

vector<vector<double>> read() {
    string input;
    ifstream file("input.txt");
    getline(file, input);
    file.close();

    vector<vector<double>> matrix;
    vector<double> row;
    for (int i = 2, st = i; i < input.length(); ++i) {
        if(input[i] == ',' || input[i] == '}') {
            row.push_back(stod(input.substr(st, i)));
            st = i + 1;
        }
        if(input[i] == '}') {
            matrix.push_back(row);
            st = i + 3;
            if(st > input.length()) break;
            i += 2;
            row.clear();
        }
    }

    return matrix;
}

vector<vector<double>> sub(vector<vector<double>> mat, int q, int n) {
    vector<vector<double>> temp;
    vector<double> row;
    for (int r = 0, j = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r == 0 || c == q) continue;
            row.push_back(mat[r][c]);
            j++;
            if (j != n - 1) continue;
            j = 0;
            temp.push_back(row);
            row.clear();
        }
    }
    return temp;
}

int det(vector<vector<double>> m, int n) {
    int d = 0;
    if (n == 1) return m[0][0];
    if (n == 2) return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    for (int i = 0; i < n; i++)
        d += (i % 2 == 0 ? 1 : -1) * m[0][i] * det(sub(m, i, n), n - 1);
    return d;
}

void write(int output) {
    cout << output;
    ofstream file;
    file.open("output.txt");
    file << output;
    file.close();
}
