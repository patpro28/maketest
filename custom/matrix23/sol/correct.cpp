#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Matrix {
    vector<vector<long long>> mat;
    int row, col;
    Matrix(int row, int col) : row(row), col(col) {
        mat.resize(row, vector<long long>(col, 0));
    }

    Matrix operator*(const Matrix &other) {
        Matrix res(row, other.col);
        for (int k = 0; k < col; k++) 
            for (int i = 0; i < row; i++) 
                for (int j = 0; j < other.col; j++) 
                    (res.mat[i][j] += mat[i][k] * other.mat[k][j]) %= MOD;
        return res;
    }

    Matrix operator^(long long n) {
        Matrix res(row, col);
        for (int i = 0; i < row; i++) res.mat[i][i] = 1;
        Matrix a = *this;
        while (n) {
            if (n & 1) res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n;
    cin >> n;
    Matrix a(3, 3);
    // a[n] = 2 * a[n - 1] + 4 * a[n - 2] + a[n - 3]
    a.mat = {
        {0, 0, 1},
        {1, 0, 4},
        {0, 1, 2}
    };
    Matrix res = a ^ n;
    Matrix b(1, 3);
    // [a(0), a(1), a(2)]
    b.mat[0] = {0, 1, 2};
    Matrix ans = b * res;
    cout << (ans.mat[0][0] + MOD) % MOD << '\n';
    return 0;
}