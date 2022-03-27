#include<sstream>
#include<fstream>
#include<vector>

#define vvf vector<vector<float>>
#define vf vector<float>

using namespace std;

vvf multiplication(vvf a, vvf b),
        transpose(const vvf &a),
        inverse(vvf m),
        read();
void write(const vector<pair<string, vvf>> &output);

int main() {
    vvf A, b;
    for (const auto &row: read()) {
        vf r = {1.00};
        for (int i = 0; i < row.size() - 1; ++i) r.push_back(row[i]);
        A.push_back(r);
        b.push_back({row[2]});
    }

    vvf At = transpose(A),
            AtA = multiplication(At, A),
            iAtA = inverse(AtA),
            iAtAAt = multiplication(iAtA, At),
            x = multiplication(iAtAAt, b);

    write({{"A",              A},
           {"b",              b},
           {"A_T*A",          AtA},
           {"(A_T*A)_-1",     iAtA},
           {"(A_T*A)_-1*A_T", iAtAAt},
           {"x",              x}});
    return 0;
}

vvf inverse(vvf m) {
    vvf inverse;
    float a = m[0][0], b = m[0][1], c = m[0][2],
            d = m[1][0], e = m[1][1], f = m[1][2],
            g = m[2][0], h = m[2][1], i = m[2][2];
    float det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    float adj[3][3] = {{(e * i - f * h),  -(d * i - f * g), (d * h - e * g)},
                       {-(b * i - c * h), (a * i - c * g),  -(a * h - b * g)},
                       {(b * f - e * c),  -(a * f - c * d), (a * e - b * d)}};
    float t_adj[3][3] = {{adj[0][0], adj[1][0], adj[2][0]},
                         {adj[0][1], adj[1][1], adj[2][1]},
                         {adj[0][2], adj[1][2], adj[2][2]}};
    for (auto &k: t_adj) {
        vf row;
        for (float j: k)
            row.push_back(j / det);
        inverse.push_back(row);
    }
    return inverse;
}

vvf multiplication(vvf a, vvf b) {
    vvf c;
    for (int i = 0; i < a.size(); i++) {
        vf row(b[0].size());
        for (int j = 0; j < b[0].size(); j++) {
            row[j] = 0;
            for (int k = 0; k < a[0].size(); k++)
                row[j] += a[i][k] * b[k][j];
        }
        c.push_back(row);
    }
    return c;
}

vvf transpose(const vvf &a) {
    vvf At;
    for (int i = 0; i < a[0].size(); ++i) {
        vf row;
        row.reserve(a.size());
        for (const auto &j: a)
            row.push_back(j[i]);
        At.push_back(row);
    }
    return At;
}

vvf read() {
    vvf input;
    ifstream file("input.txt");
    for (string line; getline(file, line);) {
        vf numbers;
        stringstream stream(line);
        for (string n; stream >> n;)
            numbers.push_back(stof(n));
        if (numbers.size() == 3)
            input.push_back(numbers);
    }
    file.close();
    return input;
}

void write(const vector<pair<string, vvf>> &output) {
    ofstream file;
    file.open("output.txt");
    file.precision(2);
    fixed(file);
    for (auto[key, value]: output) {
        file << key << ":\n";
        vvf matrix = value;
        for (const auto &row: matrix) {
            for (auto column: row)
                file << column << " ";
            file << "\n";
        }
        file << "\n";
    }
    file.close();
}