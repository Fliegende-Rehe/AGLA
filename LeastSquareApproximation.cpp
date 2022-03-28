#include "matrix.cpp"
#include<fstream>

vvf read();
void write(const vector<pair<string, vvf>> &output);

int main() {
    vvf A, b;
    for (const auto &row: read()) {
        vf r = {1.00};
        for (int i = 0; i < row.size() - 1; ++i) r.push_back(row[i]);
        A.push_back(r);
        b.push_back({row[2]});
    }

    vvf At = TRANS(A),
            AtA = MULT(At, A),
            iAtA = INV(AtA),
            iAtAAt = MULT(iAtA, At),
            x = MULT(iAtAAt, b);

    write({{"A",              A},
           {"b",              b},
           {"A_T*A",          AtA},
           {"(A_T*A)_-1",     iAtA},
           {"(A_T*A)_-1*A_T", iAtAAt},
           {"x",              x}});

    return 0;
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
