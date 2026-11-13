#include "testlib.h"
#include "../params.h"
#include <vector>
using namespace std;

void writeArray(const vector<int>& values) {
    println(values.size());
    println(values);
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int id = atoi(argv[1]);
    if (id == 0) {
        println(62);
        for (int n = 1; n <= 5; ++n) {
            vector<int> values(n);
            for (int mask = 0; mask < (1 << n); ++mask) {
                for (int i = 0; i < n; ++i) values[i] = (mask >> i) & 1;
                writeArray(values);
            }
        }
    } else if (id == 1) {
        const vector<vector<int>> arrays = {
            {1, 0, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1},
            {0, 0, 1, 1, 0, 0},
            {1, 0, 0, 1, 0, 1},
            {1, 1, 0, 0, 0, 0, 1, 1},
        };
        println(arrays.size());
        for (const auto& values : arrays) writeArray(values);
    } else if (id == 10 || id == 11) {
        println(T_MAX);
        for (int i = 0; i < T_MAX; ++i) {
            vector<int> values(id == 10 ? 1 : SUM_N_MAX / T_MAX);
            if (id == 10) {
                values[0] = i % 2;
            } else {
                int density = i % 5;
                for (int& value : values) value = rnd.next(0, 4) < density;
            }
            writeArray(values);
        }
    } else if (id == 13) {
        constexpr int tests = 200;
        println(tests);
        int remaining = SUM_N_MAX;
        for (int i = 1; i <= tests; ++i) {
            int n = i == tests ? remaining : rnd.next(1, 2 * remaining / (tests - i + 1) - 1);
            remaining -= n;
            vector<int> values(n);
            int density = rnd.next(1, 9);
            for (int& value : values) value = rnd.next(1, 10) <= density;
            writeArray(values);
        }
    } else {
        println(1);
        vector<int> values(N_MAX);
        for (int i = 0; i < N_MAX; ++i) {
            switch (id) {
                case 3: values[i] = 1; break;
                case 4: values[i] = i % 2; break;
                case 5: values[i] = i % 3 == 0; break;
                case 6: values[i] = i % 4 == 0 || i == N_MAX - 2; break;
                case 7: values[i] = i < 2; break;
                case 8: values[i] = i >= N_MAX - 2; break;
                case 9: values[i] = i == N_MAX / 2 - 1 || i == N_MAX / 2 + 1; break;
                case 12: values[i] = rnd.next(0, 1); break;
            }
        }
        writeArray(values);
    }
}
