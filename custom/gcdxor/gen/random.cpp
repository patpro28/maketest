#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

const int MAX = (1 << 30) - 1;
const int T_MAX = 10000;
const int N_MAX = 200000;

void gen_1_gcd(int n, int k, vector<int> &v, Random &gen) {
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i] = k * gen.uniform<int>(1, MAX / k);
    }
}

void gen_1_xor(int n, vector<int> &v, Random &gen) {
    v.resize(n);
    int p = gen.uniform<int>(1, MAX);
    for (int i = 0; i < n; i++) {
        v[i] = p;
    }
}

void gen_2(int n, int k, vector<int> &v, Random &gen) {
    v.resize(n);
    int p = gen.uniform<int>(1, MAX);
    int l = gen.uniform<int>(1, n);
    int r = gen.uniform<int>(l, n);
    for (int i = 0; i < l; i++) {
        v[i] = k * gen.uniform<int>(1, MAX / k);
    }
    for (int i = l; i < r; i++) {
        v[i] = p;
    }
    for (int i = r; i < l; i++) {
        v[i] = k * gen.uniform<int>(1, MAX / k);
    }
}

void gen_random(int n, vector<int> &v, Random &gen) {
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i] = gen.uniform<int>(1, MAX);
    }
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = gen.uniform<int>(1, T_MAX);

    cout << t << endl;
    int limit = N_MAX / t;
    while (t--) {
        int n = gen.uniform<int>(1, limit);
        int k = gen.uniform<int>(1, MAX);
        int choice = gen.uniform<int>(0, 3);
        vector<int> v;
        switch (choice) {
            case 0:
                gen_1_gcd(n, k, v, gen);
                break;
            case 1:
                gen_1_xor(n, v, gen);
                break;
            case 2:
                gen_2(n, k, v, gen);
                break;
            default:
                gen_random(n, v, gen);
                break;
        }
        cout << n << " " << k << endl;
        for (int i = 0; i < n; i++) {
            cout << v[i] << " \n"[i == n - 1];
        }
    }

    return 0;
}
