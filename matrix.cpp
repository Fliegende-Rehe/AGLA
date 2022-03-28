#include<sstream>
#include<vector>
#include<iostream>

#define vvf vector<vector<float>>
#define vf vector<float>

using namespace std;

template<class T>
void PRINT(T m) {
    for (auto r: m) {
        for (auto c: r)
            cout << c << " ";
        cout << "\n";
    }
    cout << "\n";
}

vvf RREF(vvf &A) {
    vvf rref = A;
    const int row = (int) rref.size();
    const int col = (int) rref[0].size();
    int lead = 0;
    while (lead < row) {
        float d, m;
        for (int r = 0; r < row; r++) {
            d = rref[lead][lead];
            m = rref[r][lead] / rref[lead][lead];
            for (int c = 0; c < col; c++) {
                if (r == lead) rref[r][c] /= d;
                else rref[r][c] -= rref[lead][c] * m;
            }
        }
        lead++;
    }
    return rref;
}

vvf SUB(vvf &M, int p, int q, int n) {
    vvf temp;
    vf row;
    for (int r = 0, j = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r == p || c == q) continue;
            row.push_back(M[r][c]);
            j++;
            if (j != n - 1) continue;
            j = 0;
            temp.push_back(row);
            row.clear();
        }
    }
    return temp;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

float DET(vvf M, int n) {
    float D = 0;
    if (n == 1) return M[0][0];
    for (int i = 0; i < n; i++) {
        float sign = i % 2 == 0 ? 1.0 : -1.0;
        vvf t = SUB(M, 0, i, n);
        D += sign * M[0][i] * DET(t, n - 1);
    }
    return D;
}

#pragma clang diagnostic pop

vvf ADJ(vvf &M) {
    int N = (int) M.size();
    vvf adj(N);
    if (N != 1) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                float sign = (i + j) % 2 == 0 ? 1.0 : -1.0;
                vvf t = SUB(M, i, j, N);
                adj[i].push_back(sign * DET(t, N - 1));
            }
        }
    } else adj[0][0] = 1;
    return adj;
}

vvf GAUSS(vvf &M) {
    int n = (int) M.size();

    int MAX = n * 10;
    float** matrix = new float*[MAX];
    for (int i = 0; i < MAX; i++) matrix[i] = new float[MAX];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) matrix[i][j] = M[i][j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            if (j == (i + n)) matrix[i][j] = 1;
        }
    }

    for (int i = n - 1; i > 0; i--) {
        if (matrix[i - 1][0] >= matrix[i][0]) continue;
        float* temp = matrix[i];
        matrix[i] = matrix[i - 1];
        matrix[i - 1] = temp;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            float t = matrix[j][i] / matrix[i][i];
            for (int k = 0; k < 2 * n; k++)
                matrix[j][k] -= matrix[i][k] * t;
        }
    }

    vvf gauss;
    for (int i = 0; i < n; i++) {
        vf row;
        float t = matrix[i][i];
        for (int j = n; j < n * 2; j++) row.push_back(matrix[i][j] / t);
        gauss.push_back(row);
    }
    return gauss;
}

vvf INV(vvf &M, bool rec = true) {
    int N = (int) M.size();
    if (rec) {
        float det = DET(M, N);
        vvf adj = ADJ(M), inv(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                inv[i].push_back(adj[i][j] / det);
        }
        return inv;
    } else return GAUSS(M);
}

vvf MULT(vvf a, vvf b) {
    vvf c;
    for (int i = 0; i < a.size(); i++) {
        vf row(b[0].size());
        for (int j = 0; j < b[0].size(); j++) {
            row[j] = 0.0;
            for (int k = 0; k < a[0].size(); k++)
                row[j] += a[i][k] * b[k][j];
        }
        c.push_back(row);
    }
    return c;
}

vvf TRANS(const vvf &a) {
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

