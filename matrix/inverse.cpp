#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<float>> read();
vector<vector<float>> inv(vector<vector<float>> matrix);
void write(vector<vector<float>> output);

int main() {
    vector<vector<float>> matrix = read();
    vector<vector<float>> inverse = inv(matrix);
    write(inverse);
    return 0;
}

vector<vector<float>> read() {
    string input;
    ifstream file("input.txt");
    getline(file, input);
    file.close();
    vector<vector<float>> matrix;
    vector<float> row;
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

vector<vector<float>> inv(vector<vector<float>> m) {
    vector<vector<float>> inverse;
    float a = m[0][0], b = m[0][1], c = m[0][2],
            d = m[1][0], e = m[1][1], f = m[1][2],
            g = m[2][0], h = m[2][1], i = m[2][2];
    float det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    float adj[3][3] = {{(e * i - f * h), -(d * i - f * g), (d * h - e * g)},
                        {-(b * i - c * h), (a * i - c * g), -(a * h - b * g)},
                        {(b * f - e * c), -(a * f - c * d), (a * e - b * d)}};
    float t_adj[3][3] ={{adj[0][0], adj[1][0], adj[2][0]},
                         {adj[0][1], adj[1][1], adj[2][1]},
                         {adj[0][2], adj[1][2], adj[2][2]}};
    for (auto & i : t_adj) {
        vector<float> row;
        for (float j : i) {
            row.push_back(j / det);
        }
        inverse.push_back(row);
    }
    return inverse;
}

void write(vector<vector<float>> output) {
    ofstream file;
    file.open("output.txt");
    for (int i = 0; i < output.size(); ++i) {
        for (int j = 0; j < output.size(); ++j) {
            file << fixed << setprecision(2);
            if(output[i][j] != 0) file << output[i][j];
            else file << abs(output[i][j]);
            file << " ";
        }
        file << "\n";
    }
    file.close();
}
