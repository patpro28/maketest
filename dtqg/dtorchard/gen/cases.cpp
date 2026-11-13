#include "testlib.h"
#include "../params.h"
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int id = atoi(argv[1]);
    int n = 1, m = 2;
    if (id == 2) n = m = 3;
    if (id == 3 || id == 4 || id == 11) {
        n = 7;
        m = 9;
    }
    if (id == 5 || id == 6) m = M_SINGLE_MAX;
    if (id == 7) {
        n = 2;
        m = M_DOUBLE_MAX;
    }
    if (id == 8 || id == 9) {
        n = N_MAX;
        m = M_MAX;
    }
    if (id == 10) n = N_MAX;
    if (id >= 12) {
        n = rnd.next(1, 8);
        m = rnd.next(2, 10);
    }

    println(n, m);
    vector<int> row(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            switch (id) {
                case 0: row[j] = j; break;
                case 1: row[j] = 1 - j; break;
                case 2:
                case 6:
                case 9: row[j] = i != n / 2 || j != m / 2; break;
                case 3: row[j] = i == n / 2 && j == m / 2; break;
                case 4:
                case 10: row[j] = (i + j) % 2; break;
                case 11: row[j] = 1 <= i && i <= 4 && 2 <= j && j <= 7; break;
                default: row[j] = rnd.next(0, 1); break;
            }
            if (id >= 5 && id != 6 && id != 9 && id != 10 && id != 11 && i == 0 && j < 2) {
                row[j] = j;
            }
        }
        println(row);
    }
}
