#include "testlib.h"
#include "../params.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int id = atoi(argv[1]);
    const vector<vector<string>> fixed = {
        {"1 1", "1=1"},
        {"5 6", "1<=2", "2<=3", "1>=3", "3<4", "5>=4", "5<=4"},
        {"6 4", "1<2", "2<3", "4<=3", "6=5"},
        {"9 7", "2>1", "2>=3", "4=3", "4<5", "6>7", "7<=8", "8>=6"},
    };
    if (id < static_cast<int>(fixed.size())) {
        for (const auto& line : fixed[id]) println(line);
        return 0;
    }
    if (4 <= id && id <= 6) {
        int n = N_MAX;
        println(n, n);
        const char* op = id == 4 ? "<" : (id == 5 ? "<=" : "=");
        for (int i = 1; i < n; ++i) cout << i << op << i + 1 << '\n';
        println(id == 4 ? "1<=1" : to_string(n) + op + "1");
        return 0;
    }
    if (id == 8) {
        int n = N_MAX;
        println(n, n);
        for (int i = 1; i < n; ++i) {
            cout << i << (i % 2 == 0 ? "<" : "<=") << i + 1 << '\n';
        }
        println("1<=1");
        return 0;
    }

    int n = id == 7 ? N_MAX : rnd.next(2, 9);
    int m = id == 7 ? M_MAX : rnd.next(1, 35);
    println(n, m);
    vector<int> value(n + 1);
    for (int i = 1; i <= n; ++i) value[i] = rnd.next(0, 4);
    for (int k = 0; k < m; ++k) {
        int i = rnd.next(1, n), j = rnd.next(1, n);
        const char* op;
        if (value[i] == value[j]) {
            const char* ties[] = {"=", "<=", ">="};
            op = ties[rnd.next(0, 2)];
        } else if (value[i] < value[j]) {
            op = rnd.next(0, 1) ? "<" : "<=";
        } else {
            op = rnd.next(0, 1) ? ">" : ">=";
        }
        cout << i << op << j << '\n';
    }
}
