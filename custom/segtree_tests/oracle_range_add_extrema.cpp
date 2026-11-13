// Independent reference using square-root decomposition and an offset per block.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using i64 = long long;

template <int Kind>
struct Extrema {
    static constexpr i64 infinity = std::numeric_limits<i64>::max();
    i64 low = infinity;
    i64 high = -infinity;
    i64 next_low = infinity;
    i64 next_high = -infinity;
    int first_low = 0;
    int high_count = 0;

    void include(i64 value, int index) {
        if (value < low) {
            if constexpr (Kind == 226) next_low = low;
            low = value;
            if constexpr (Kind == 223) first_low = index;
        } else if constexpr (Kind == 226) {
            next_low = std::min(next_low, value);
        }

        if (value > high) {
            if constexpr (Kind == 226) next_high = high;
            high = value;
            if constexpr (Kind == 224) high_count = 1;
        } else {
            if constexpr (Kind == 226) next_high = std::max(next_high, value);
            if constexpr (Kind == 224) high_count += value == high;
        }
    }

    void merge(const Extrema &other, i64 offset = 0) {
        if (other.low == infinity) return;
        i64 other_low = other.low + offset;
        i64 other_high = other.high + offset;

        if (other_low < low) {
            if constexpr (Kind == 226) {
                next_low = other.next_low == infinity ? low : std::min(low, other.next_low + offset);
            }
            low = other_low;
            if constexpr (Kind == 223) first_low = other.first_low;
        } else if constexpr (Kind == 226) {
            next_low = std::min(next_low, other_low);
        }

        if (other_high > high) {
            if constexpr (Kind == 226) {
                next_high = other.next_high == -infinity ? high : std::max(high, other.next_high + offset);
            }
            high = other_high;
            if constexpr (Kind == 224) high_count = other.high_count;
        } else {
            if constexpr (Kind == 226) next_high = std::max(next_high, other_high);
            if constexpr (Kind == 224) {
                if (other_high == high) high_count += other.high_count;
            }
        }
    }
};

template <int Kind>
class Blocks {
    static constexpr int block_size = 320;
    std::vector<i64> values;
    std::vector<i64> offsets;
    std::vector<Extrema<Kind>> summaries;

    int end_of(int block) const {
        return std::min(int(values.size()), (block + 1) * block_size);
    }

    void rebuild(int block) {
        auto &summary = summaries[block];
        summary = {};
        for (int i = block * block_size; i < end_of(block); ++i) summary.include(values[i], i);
    }

public:
    explicit Blocks(std::vector<i64> initial) : values(std::move(initial)) {
        int count = (int(values.size()) + block_size - 1) / block_size;
        offsets.resize(count);
        summaries.resize(count);
        for (int block = 0; block < count; ++block) rebuild(block);
    }

    void add(int left, int right, i64 delta) {
        while (left < right) {
            int block = left / block_size;
            int end = std::min(right, end_of(block));
            if (left == block * block_size && end == end_of(block)) {
                offsets[block] += delta;
            } else {
                for (int i = left; i < end; ++i) values[i] += delta;
                rebuild(block);
            }
            left = end;
        }
    }

    Extrema<Kind> query(int left, int right) const {
        Extrema<Kind> answer;
        while (left < right) {
            int block = left / block_size;
            int end = std::min(right, end_of(block));
            if (left == block * block_size && end == end_of(block)) {
                answer.merge(summaries[block], offsets[block]);
            } else {
                for (int i = left; i < end; ++i) answer.include(values[i] + offsets[block], i);
            }
            left = end;
        }
        return answer;
    }
};

template <class Feasible>
i64 least_feasible(i64 high, Feasible feasible) {
    i64 low = 0;
    while (low < high) {
        i64 mid = low + (high - low) / 2;
        if (feasible(mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

template <int Kind>
int solve() {
    int n, q;
    if (!(std::cin >> n >> q)) return 1;
    i64 slope = 0;
    if constexpr (Kind == 227) std::cin >> slope;
    std::vector<i64> values(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i];
        if constexpr (Kind == 227) values[i] -= i * slope;
    }
    int pairs = n / 2;
    if constexpr (Kind == 228) {
        for (int i = 0; i < pairs; ++i) values[i] -= values[n - 1 - i];
        values.resize(pairs);
    }
    Blocks<Kind> blocks(std::move(values));

    for (int operation = 0; operation < q; ++operation) {
        int type, l, r;
        std::cin >> type >> l >> r;
        --l;
        if (type == 0) {
            i64 delta;
            std::cin >> delta;
            if constexpr (Kind == 225) {
                if (l >= r) {
                    blocks.add(l, n, delta);
                    blocks.add(0, r, delta);
                    continue;
                }
            }
            if constexpr (Kind == 228) {
                blocks.add(l, std::min(r, pairs), delta);
                blocks.add(n - r, std::min(n - l, pairs), -delta);
            } else {
                blocks.add(l, r, delta);
            }
            continue;
        }

        if constexpr (Kind == 221) {
            std::cout << blocks.query(l, r).low << '\n';
        } else if constexpr (Kind == 222) {
            auto extrema = blocks.query(l, r);
            std::cout << extrema.high - extrema.low << '\n';
        } else if constexpr (Kind == 223) {
            auto extrema = blocks.query(l, r);
            std::cout << extrema.low << ' ' << extrema.first_low + 1 << '\n';
        } else if constexpr (Kind == 224) {
            auto extrema = blocks.query(l, r);
            std::cout << extrema.high << ' ' << extrema.high_count << '\n';
        } else if constexpr (Kind == 225) {
            i64 best = l < r ? blocks.query(l, r).high
                : std::max(blocks.query(l, n).high, blocks.query(0, r).high);
            std::cout << best << '\n';
        } else if constexpr (Kind == 226) {
            auto extrema = blocks.query(l, r);
            i64 spread = r - l == 1 ? 0
                : std::min(extrema.high - extrema.next_low, extrema.next_high - extrema.low);
            std::cout << spread << '\n';
        } else if constexpr (Kind == 227) {
            i64 p, s;
            std::cin >> p >> s;
            p -= l * slope;
            s -= l * slope;
            auto extrema = blocks.query(l, r);
            i64 upper = std::max(std::abs(extrema.low - p), std::abs(extrema.high - p));
            i64 error = least_feasible(upper, [&](i64 e) {
                return std::max(p, extrema.high - e) <= std::min(s, extrema.low + e);
            });
            std::cout << error << '\n';
        } else if constexpr (Kind == 228) {
            int first = std::max(l, n - r);
            int end = std::min({r, n - l, pairs});
            auto extrema = blocks.query(first, end);
            std::cout << (first < end ? std::max(-extrema.low, extrema.high) : 0) << '\n';
        } else if constexpr (Kind == 229) {
            int u, v, s, t;
            i64 budget;
            std::cin >> u >> v >> s >> t >> budget;
            --u;
            --s;
            auto a = blocks.query(u, v);
            auto b = blocks.query(s, t);
            auto outside = blocks.query(l, u);
            outside.merge(blocks.query(v, s));
            outside.merge(blocks.query(t, r));

            i64 maximum = std::max({a.high, b.high, outside.high});
            i64 minimum = std::min({a.low, b.low, outside.low});
            i64 answer = least_feasible(maximum - minimum, [&](i64 width) {
                if (width < a.high - a.low || width < b.high - b.low) return false;
                i64 floor = maximum - width;
                if (outside.low < floor) return false;
                i64 raise_a = std::max(0LL, floor - a.low);
                i64 raise_b = std::max(0LL, floor - b.low);
                return raise_a + raise_b <= budget;
            });
            std::cout << answer << '\n';
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    switch (std::atoi(argv[1])) {
        case 221: return solve<221>();
        case 222: return solve<222>();
        case 223: return solve<223>();
        case 224: return solve<224>();
        case 225: return solve<225>();
        case 226: return solve<226>();
        case 227: return solve<227>();
        case 228: return solve<228>();
        case 229: return solve<229>();
        default: return 1;
    }
}
