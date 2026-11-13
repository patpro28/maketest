#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../params.h"

using namespace std;

int pick(mt19937& rng, int lo, int hi) {
    const unsigned int width = hi - lo + 1;
    return lo + static_cast<int>(rng() % width);
}

long long sample_value(mt19937& rng, int profile, int index) {
    if (profile == 0) return 0;
    if (profile == 1) return VALUE_MAX;
    if (profile == 2) return -VALUE_MAX;
    if (profile == 3) return index % 2 == 0 ? VALUE_MAX : -VALUE_MAX;
    if (profile == 4) return index % 4 == 0 ? pick(rng, -7, 7) : 0;
    return pick(rng, -VALUE_MAX, VALUE_MAX);
}

void write_row(const vector<long long>& values) {
    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i] << (i + 1 == values.size() ? '\n' : ' ');
    }
}

void write_case(mt19937& rng, int n, int style, int profile) {
    vector<long long> values(n);
    for (int i = 0; i < n; ++i) values[i] = sample_value(rng, profile, i) / 2;
    for (long long& value : values) value = style % 2 == 0 ? -abs(value) : abs(value);
    if (style % 6 == 3) values.back() = 0;
    vector<long long> b = values;
    const long long delta = style % 2 == 0 ? VALUE_MAX : -VALUE_MAX;
    switch (style % 6) {
        case 0:
            break;
        case 1:
            for (int i = 0; i < n; ++i) b[i] += delta;
            break;
        case 2: {
            int left = n >= 3 ? pick(rng, 1, n - 2) : 0;
            int right = n >= 3 ? pick(rng, left, n - 2) : n - 1;
            long long before = style % 4 == 0 ? -VALUE_MAX : VALUE_MAX;
            for (int i = left; i <= right; ++i) {
                values[i] = before;
                b[i] = -before;
            }
            break;
        }
        case 3:
            b.front() += delta;
            if (n > 1) b.back() -= delta;
            break;
        case 4:
            b.back() += delta;
            break;
        case 5:
            b.front() += delta;
            if (n > 2) b.back() += delta;
            break;
    }
    cout << n << '\n';
    write_row(values);
    write_row(b);
}

int main(int argc, char** argv) {
    if (argc != 2) return 1;
    int seed = stoi(argv[1]);
    mt19937 rng(410030u + seed);

    vector<int> sizes;
    if (seed == 0) {
        sizes = {1, 1, 1, 1, 1, 1};
    } else if (seed == 1) {
        sizes = {2, 5, 4, 2, 8, 12, 3, 9};
    } else if (seed == 14) {
        sizes.assign(T_MAX, N_MAX / T_MAX);
    } else if (seed == 15 || seed == 16) {
        sizes = {N_MAX};
    } else if (seed == 17) {
        sizes = {1, 70000, 129998, 1};
    } else {
        int count = seed < 8 ? 30 : 16;
        for (int i = 0; i < count; ++i) {
            sizes.push_back(pick(rng, 1, seed < 8 ? 20 : 4000));
        }
    }

    cout << sizes.size() << '\n';
    for (size_t i = 0; i < sizes.size(); ++i) {
        int n = sizes[i];
        int style = seed + static_cast<int>(i);
        int profile = style % 8;
        if (seed == 15) profile = 1;
        if (seed == 16) profile = 2;
        write_case(rng, n, style, profile);
    }
}
