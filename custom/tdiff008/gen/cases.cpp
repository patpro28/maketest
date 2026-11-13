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

struct Update {
    int left, right;
    long long delta;
};

Update make_update(mt19937& rng, int n, int profile) {
    int left = pick(rng, 1, n);
    int right = pick(rng, left, n);
    switch (profile % 6) {
        case 0: left = 1; right = n; break;
        case 1: right = left; break;
        case 2: left = 1; break;
        case 3: right = n; break;
        case 4: left = n; right = n; break;
    }
    return {left, right, sample_value(rng, profile % 8, left)};
}

void write_case(mt19937& rng, int n, int style, int profile, int q) {
    vector<long long> values(n);
    for (int i = 0; i < n; ++i) values[i] = sample_value(rng, profile, i);
    cout << n << ' ' << q << '\n';
    write_row(values);
    const Update repeated = {1, n, -VALUE_MAX};
    for (int j = 0; j < q; ++j) {
        Update update = j % 8 == 0 ? repeated : make_update(rng, n, style + j);
        int position = pick(rng, 1, n);
        if (j % 8 <= 1) position = update.left;
        if (j % 8 == 2) position = min(n, update.right + 1);
        if (j % 8 == 3) position = update.right;
        cout << update.left << ' ' << update.right << ' ' << update.delta << ' ' << position << '\n';
    }
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

    int remaining_queries = Q_MAX;
    cout << sizes.size() << '\n';
    for (size_t i = 0; i < sizes.size(); ++i) {
        int n = sizes[i];
        int style = seed + static_cast<int>(i);
        int profile = style % 8;
        if (seed == 15) profile = 1;
        if (seed == 16) profile = 2;
        int q = pick(rng, 1, seed < 8 ? 30 : 100);
        if (seed >= 14) {
            q = remaining_queries / static_cast<int>(sizes.size() - i);
            remaining_queries -= q;
        }
        write_case(rng, n, style, profile, q);
    }
}
