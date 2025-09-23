#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX_X = 100;
const int MAX_Y = 100;
const int MAX_Z = 100;

int MAX_Q = 200000;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int X = gen.uniform(50, MAX_X);
    int Y = gen.uniform(50, MAX_Y);
    int Z = gen.uniform(50, MAX_Z);
    cout << X << " " << Y << " " << Z << "\n";
    for (int z = 0; z < Z; z++) {
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                cout << gen.uniform(-1000, 1000) << (x == X - 1 ? "\n" : " ");
            }
        }
    }
    int Q = gen.uniform(1, MAX_Q);

    cout << Q << "\n";
    while (Q--) {
        int x1 = gen.uniform(1, X);
        int y1 = gen.uniform(1, Y);
        int z1 = gen.uniform(1, Z);
        int x2 = gen.uniform(x1, X);
        int y2 = gen.uniform(y1, Y);
        int z2 = gen.uniform(z1, Z);
        cout << x1 << " " << y1 << " " << z1 << " " << x2 << " " << y2 << " " << z2 << "\n";
    }
    return 0;
}
