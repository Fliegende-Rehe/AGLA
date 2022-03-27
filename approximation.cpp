#include"approximation.h"

int main() {
    array input = read();
    vector<pair<string, array >> output;

    array A;
    for (const auto &row: input) {
        vector<float> r = {1.00};
        for (int i = 0; i < row.size() - 1; ++i) r.push_back(row[i]);
        A.push_back(r);
    }
    push("A", A);

    array b;
    for (const auto &row: input) {
        vector<float> r = {row[2]};
        b.push_back(r);
    }
    push("b", b);

    array AT = transpose(A);
    array ATA = multiplication(AT, A);
    push("A_T*A", ATA);

    array invATA = inverse(ATA);
    push("(A_T*A)_-1", invATA);

    array invATAT = multiplication(invATA, AT);
    push("(A_T*A)_-1*A_T", invATAT);

    push("x", multiplication(invATAT, b)); //getX(A, b)

    write(output);
    return 0;
}

void rref(array B) {
    const int row = B.size();
    const int col = B[0].size();
    int lead = 0;
    while (lead < row) {
        float d, m;
        for (int r = 0; r < row; r++) {
            d = B[lead][lead];
            m = B[r][lead] / B[lead][lead];
            for (int c = 0; c < col; c++) { 
                if (r == lead) B[r][c] /= d;
                else B[r][c] -= B[lead][c] * m;
            }
        }
        lead++;
    }
}

array getX(array a, array b) {
    array x,
            at = transpose(a),
            ata = multiplication(at, a),
            atb = multiplication(at, move(b));

    for (int i = 0; i < ata.size(); ++i)
        ata[i].push_back(atb[i][0]);

    rref(ata);
    for(auto row : ata) {
        vector<float> c;
        c.push_back(row[ata[0].size() - 1]);
        x.push_back(c);
    }
    return x;
}

array inverse(array m) {
    array inverse;
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
        vector<float> row;
        for (float j: k)
            row.push_back(j / det);
        inverse.push_back(row);
    }
    return inverse;
}

array multiplication(array a, array b) {
    array c;
    for (int i = 0; i < a.size(); i++) {
        vector<float> row(b[0].size());
        for (int j = 0; j < b[0].size(); j++) {
            row[j] = 0;
            for (int k = 0; k < a[0].size(); k++)
                row[j] += a[i][k] * b[k][j];
        }
        c.push_back(row);
    }
    return c;
}

array transpose(const array &a) {
    array at;
    for (int i = 0; i < a[0].size(); ++i) {
        vector<float> row;
        row.reserve(a.size());
        for (const auto &j: a)
            row.push_back(j[i]);
        at.push_back(row);
    }
    return at;
}

array read() {
    array input;
    ifstream file("input.txt");
    for (string line; getline(file, line);) {
        vector<float> numbers;
        stringstream stream(line);
        for (string n; stream >> n;)
            numbers.push_back(stof(n));
        if (numbers.size() == 3)
            input.push_back(numbers);
    }
    file.close();
    return input;
}

void write(const vector<pair<string, array>> &output) {
    ofstream file;
    file.open("output.txt");
    file.precision(2);
    fixed(file);
    for (auto[key, value]: output) {
        file << key << ":\n";
        array matrix = value;
        for (const auto &row: matrix) {
            for (auto column: row)
                file << column << " ";
            file << "\n";
        }
        file << "\n";
    }
    file.close();
}