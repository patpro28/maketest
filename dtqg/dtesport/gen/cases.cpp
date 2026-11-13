#include "testlib.h"
#include "../params.h"
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int id = atoi(argv[1]);
    if (id == 0) {
        println(1, 5);
        println(-VALUE_MAX);
        println(3, 1, 1);
        println(1, 1, 1, VALUE_MAX, VALUE_MAX);
        println(3, 1, 1);
        println(2, 1, 1, VALUE_MAX, -VALUE_MAX);
        println(3, 1, 1);
        return 0;
    }
    if (id == 1) {
        println(3, 2);
        println(1, 1, 1);
        println(1, 1, 3, 1, -1);
        println(2, 2, 2, 2, 2);
        return 0;
    }
    if (id == 2) {
        println(2, 6);
        println(-VALUE_MAX, VALUE_MAX);
        println(3, 1, 2);
        println(2, 1, 2, -5, -2);
        println(3, 1, 2);
        println(1, 2, 2, 2, 2);
        println(3, 1, 2);
        println(3, 2, 2);
        return 0;
    }
    if (id == 14) {
        println(3, 4296);
        println(0, 0, 0);
        for (int i = 0; i < 4294; ++i) println(1, 3, 3, VALUE_MAX, 0);
        println(1, 3, 3, 967296, 0);
        println(3, 1, 3);
        return 0;
    }

    bool large = 9 <= id && id <= 13;
    int n = large ? N_MAX : rnd.next(5, 60);
    int q = large ? Q_MAX : rnd.next(100, 300);
    println(n, q);
    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        if (id == 10) values[i] = i;
        else if (id == 12 || id == 13 || id == 15) values[i] = i % 37;
        else values[i] = rnd.next(-5, 5);
    }
    println(values);

    for (int i = 0; i < q; ++i) {
        int l = rnd.next(1, n), r = rnd.next(l, n);
        int type = rnd.next(1, 3);
        int start = rnd.next(-5, 5), slope = rnd.next(-5, 5);
        if (large) {
            start = rnd.next(-VALUE_MAX, VALUE_MAX);
            slope = rnd.next(-VALUE_MAX, VALUE_MAX);
        }
        if (id == 10) {
            l = 1;
            r = n;
            type = i % 10 == 9 ? 3 : (i == q / 2 ? 2 : 1);
            start = slope = VALUE_MAX;
        }
        if (id == 11) {
            type = i % 3 == 2 ? 3 : 1;
            if (type == 1) r = min(n, l + i % 3);
        }
        if (id == 12) type = 3;
        if (id == 13) {
            // Repeated broad updates crossing interior nodes, interleaved with queries.
            l = rnd.next(2, n / 4);
            r = rnd.next(3 * n / 4, n - 1);
            type = i % 3 + 1;
        }
        if (type == 3) println(type, l, r);
        else println(type, l, r, start, slope);
    }
}
