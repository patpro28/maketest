#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

using i64 = long long;
using Wide = __int128_t;

struct Operation {
    int type, left, right;
    i64 delta = 0;
};

// Difference events evaluated against a prefix of immutable weights.
class WeightedFenwick {
    struct Event {
        Wide delta = 0;
        Wide weighted = 0;
    };
    int size;
    const std::vector<i64> &weights;
    std::vector<Event> tree;

    void addEvent(int position, i64 delta) {
        Wide weighted = Wide(delta) * weights[position - 1];
        for (int i = position; i <= size; i += i & -i) {
            tree[i].delta += delta;
            tree[i].weighted += weighted;
        }
    }

    Wide prefix(int position) const {
        Event total;
        for (int i = position; i; i -= i & -i) {
            total.delta += tree[i].delta;
            total.weighted += tree[i].weighted;
        }
        return weights[position] * total.delta - total.weighted;
    }

public:
    WeightedFenwick(const std::vector<i64> &values, const std::vector<i64> &weights)
        : size(int(values.size()) - 1), weights(weights), tree(size + 1) {
        for (int i = 1; i <= size; ++i) addEvent(i, values[i] - values[i - 1]);
    }

    void add(int left, int right, i64 delta) {
        addEvent(left, delta);
        if (right < size) addEvent(right + 1, -delta);
    }

    Wide sum(int left, int right) const {
        return prefix(right) - prefix(left - 1);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) return 2;
    const int kind = std::atoi(argv[1]);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0, q, setting = 0;
    if (kind == 218) std::cin >> q;
    else std::cin >> n >> q;
    if (kind == 215 || kind == 217) std::cin >> setting;
    std::vector<i64> a(n + 1), fixed(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    if (kind == 219) {
        for (int i = 1; i <= n; ++i) std::cin >> fixed[i];
    }

    std::vector<Operation> ops(q);
    std::vector<int> coordinates;
    for (Operation &op : ops) {
        std::cin >> op.type >> op.left >> op.right;
        if (op.type == 1) std::cin >> op.delta;
        if (kind == 218) {
            coordinates.push_back(op.left);
            coordinates.push_back(op.right + 1);
        }
    }
    if (kind == 218) {
        std::sort(coordinates.begin(), coordinates.end());
        coordinates.erase(std::unique(coordinates.begin(), coordinates.end()), coordinates.end());
        n = int(coordinates.size()) - 1;
        a.assign(n + 1, 0);
    }
    std::vector<int> mapped;
    if (kind == 217) {
        mapped.resize(n + 1);
        std::vector<i64> reordered(n + 1);
        int next = 1;
        for (int start = 1; start <= setting; ++start) {
            for (int i = start; i <= n; i += setting) {
                mapped[i] = next;
                reordered[next++] = a[i];
            }
        }
        a.swap(reordered);
    }

    std::vector<i64> measure(n + 1), extraMeasure(n + 1);
    for (int i = 1; i <= n; ++i) {
        i64 w = 1;
        if (kind == 214) w = i % 2 ? 1 : -1;
        if (kind == 218) w = coordinates[i] - coordinates[i - 1];
        if (kind == 219) w = fixed[i];
        measure[i] = measure[i - 1] + w;
        extraMeasure[i] = extraMeasure[i - 1] + (kind == 212 ? i % 2 : i);
    }
    WeightedFenwick primary(a, measure);
    const bool dual = kind == 212 || kind == 213;
    // For scalar problems, construct an empty secondary structure.
    const std::vector<i64> empty(1);
    WeightedFenwick secondary(dual ? a : empty, dual ? extraMeasure : empty);
    for (const Operation &op : ops) {
        int left = op.left, right = op.right;
        if (kind == 217) {
            int last = left + ((right - left) / setting) * setting;
            left = mapped[left];
            right = mapped[last];
        } else if (kind == 218) {
            left = int(std::lower_bound(coordinates.begin(), coordinates.end(), left) - coordinates.begin()) + 1;
            right = int(std::lower_bound(coordinates.begin(), coordinates.end(), right + 1) - coordinates.begin());
        }
        const bool wraps = kind == 211 && left > right;
        if (op.type == 1) {
            if (wraps) {
                primary.add(left, n, op.delta);
                primary.add(1, right, op.delta);
            } else {
                primary.add(left, right, op.delta);
            }
            if (dual) secondary.add(left, right, op.delta);
            continue;
        }
        Wide answer = wraps ? primary.sum(left, n) + primary.sum(1, right) : primary.sum(left, right);
        if (kind == 212) {
            Wide odd = secondary.sum(left, right);
            std::cout << i64(odd) << ' ' << i64(answer - odd) << '\n';
            continue;
        }
        if (kind == 213) answer = secondary.sum(left, right) - (left - 1) * answer;
        if (kind == 214 && left % 2 == 0) answer = -answer;
        if (kind == 215) {
            answer %= setting;
            if (answer < 0) answer += setting;
        }
        if (kind == 216) {
            i64 length = right - left + 1, sum = i64(answer);
            i64 divisor = std::gcd(sum, length);
            std::cout << sum / divisor << ' ' << length / divisor << '\n';
        } else {
            std::cout << i64(answer) << '\n';
        }
    }
}
