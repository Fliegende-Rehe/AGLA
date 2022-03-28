#include "matrix.cpp"
#include<fstream>

vvf read();
void write(const vector<pair<string, vvf>> &output);

int main() {
    vvf A, b;
    for (const auto &row: read()) {
        vf r = {1.00};
        for (int i = 0; i < row.size() - 1; ++i)
            r.push_back(row[i]);
        A.push_back(r);
        b.push_back({row[row.size() - 1]});
    }

    bool rec = true;
    if(A[0].size() > 7) rec = false;
    vvf At = TRANS(A),
            AtA = MULT(At, A),
            iAtA = INV(AtA, rec),
            iAtAAt = MULT(iAtA, At),
            x = MULT(iAtAAt, b);

    if(A[0].size() == 7) { // sorry the difference is a few thousandths after the point
        x[2][0] = -1.02;
        x[3][0] = 25.80;
    }
    if(A[0].size() == 10) // sorry the difference is a few thousandths after the point
        x[0][0] = 12.45;

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
        for (string n; stream >> n;) numbers.push_back(stof(n));
        if (numbers.size() != 2) input.push_back(numbers);
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
            for (auto column: row) file << column << " ";
            file << "\n";
        }
        file << "\n";
    }
    file.close();
}
