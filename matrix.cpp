#include<sstream>
#include<vector>
#include<iostream>

#define vvf vector<vector<float>>
#define vf vector<float>

using namespace std;

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

vvf INV(vvf &M) {
    int N = (int) M.size();
    float det = DET(M, N);
    vvf adj = ADJ(M), inv(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            inv[i].push_back(adj[i][j] / det);
    }
    return inv;
}

vvf MULT(vvf a, vvf b) {
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

template<class T> void PRINT(T m) {
    for (auto r: m) {
        for (auto c: r)
            cout << c << " ";
        cout << "\n";
    }
    cout << "\n";
}
