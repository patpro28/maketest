#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y, Z;
    cin >> X >> Y >> Z;

    // Mảng 3D cộng dồn, thêm 1 đơn vị để dễ dùng chỉ số 1-based
    vector<vector<vector<long long>>> pre(
        X + 1, vector<vector<long long>>(Y + 1, vector<long long>(Z + 1, 0))
    );

    // Đọc dữ liệu
    for (int z = 1; z <= Z; z++) {
        for (int y = 1; y <= Y; y++) {
            for (int x = 1; x <= X; x++) {
                long long val;
                cin >> val;
                pre[x][y][z] = val
                    + pre[x - 1][y][z]
                    + pre[x][y - 1][z]
                    + pre[x][y][z - 1]
                    - pre[x - 1][y - 1][z]
                    - pre[x - 1][y][z - 1]
                    - pre[x][y - 1][z - 1]
                    + pre[x - 1][y - 1][z - 1];
            }
        }
    }

    auto getSum = [&](int x, int y, int z) -> long long {
        if (x < 0 || y < 0 || z < 0) return 0;
        if (x > X) x = X;
        if (y > Y) y = Y;
        if (z > Z) z = Z;
        return pre[x][y][z];
    };

    int Q;
    cin >> Q;
    while (Q--) {
        int x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

        long long ans = 0;
        ans += getSum(x2, y2, z2);
        ans -= getSum(x1 - 1, y2, z2);
        ans -= getSum(x2, y1 - 1, z2);
        ans -= getSum(x2, y2, z1 - 1);
        ans += getSum(x1 - 1, y1 - 1, z2);
        ans += getSum(x1 - 1, y2, z1 - 1);
        ans += getSum(x2, y1 - 1, z1 - 1);
        ans -= getSum(x1 - 1, y1 - 1, z1 - 1);

        cout << ans << "\n";
    }

    return 0;
}
