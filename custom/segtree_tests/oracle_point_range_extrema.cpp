// Independent reference using square-root decomposition.
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using i64 = long long;
constexpr i64 LOW = std::numeric_limits<i64>::lowest();
constexpr i64 HIGH = std::numeric_limits<i64>::max();

template <int Kind>
struct Summary {
    i64 minimum = HIGH;
    i64 maximum = LOW;
    i64 second = LOW;
    i64 signed_max[2] = {LOW, LOW};

    void add_candidate(i64 value) {
        if (value > maximum) {
            second = maximum;
            maximum = value;
        } else if (value < maximum && value > second) {
            second = value;
        }
    }

    void include(int index, i64 value) {
        if constexpr (Kind == 28) {
            signed_max[index % 2] = std::max(signed_max[index % 2], value);
            signed_max[1 - index % 2] = std::max(signed_max[1 - index % 2], -value);
        } else if constexpr (Kind == 29) {
            add_candidate(value);
        } else {
            if constexpr (Kind != 26) minimum = std::min(minimum, value);
            maximum = std::max(maximum, value);
        }
    }

    void merge(const Summary &other) {
        if constexpr (Kind == 28) {
            for (int p = 0; p < 2; ++p) {
                signed_max[p] = std::max(signed_max[p], other.signed_max[p]);
            }
        } else if constexpr (Kind == 29) {
            add_candidate(other.maximum);
            add_candidate(other.second);
        } else {
            if constexpr (Kind != 26) minimum = std::min(minimum, other.minimum);
            maximum = std::max(maximum, other.maximum);
        }
    }
};

template <int Kind>
class Blocks {
    static constexpr int width = 448;
    std::vector<i64> values;
    std::vector<Summary<Kind>> blocks;

    int block_end(int id) const {
        return std::min(int(values.size()), (id + 1) * width);
    }

    void rebuild(int id) {
        blocks[id] = {};
        int end = block_end(id);
        for (int index = id * width; index < end; ++index) blocks[id].include(index, values[index]);
    }

public:
    explicit Blocks(std::vector<i64> initial)
        : values(std::move(initial)), blocks((values.size() + width - 1) / width) {
        for (int id = 0; id < int(blocks.size()); ++id) rebuild(id);
    }

    void assign(int index, i64 value) {
        values[index] = value;
        rebuild(index / width);
    }

    // Half-open query, including empty ranges for the exclusion problem.
    Summary<Kind> query(int begin, int end) const {
        Summary<Kind> result;
        while (begin < end) {
            int id = begin / width;
            int boundary = block_end(id);
            int stop = std::min(end, boundary);
            if (begin == id * width && stop == boundary) {
                result.merge(blocks[id]);
            } else {
                for (int index = begin; index < stop; ++index) result.include(index, values[index]);
            }
            begin = stop;
        }
        return result;
    }
};

template <int Kind>
int solve() {
    int n, q;
    if (!(std::cin >> n >> q)) return 1;
    std::vector<i64> initial(n);
    for (auto &value : initial) std::cin >> value;
    Blocks<Kind> blocks(std::move(initial));

    while (q--) {
        int type, l;
        std::cin >> type >> l;
        --l;
        if (type == 1) {
            i64 value;
            std::cin >> value;
            blocks.assign(l, value);
            continue;
        }

        int r;
        std::cin >> r;
        if constexpr (Kind == 24) {
            i64 h;
            std::cin >> h;
            auto extrema = blocks.query(l, r);
            std::cout << std::max(extrema.maximum - h, h - extrema.minimum) << '\n';
        } else if constexpr (Kind == 26 || Kind == 27) {
            int u, v;
            std::cin >> u >> v;
            --u;
            if constexpr (Kind == 26) {
                std::cout << std::max(blocks.query(l, u).maximum, blocks.query(v, r).maximum) << '\n';
            } else {
                auto a = blocks.query(l, r);
                auto b = blocks.query(u, v);
                std::cout << std::max(a.maximum - b.minimum, b.maximum - a.minimum) << '\n';
            }
        } else if constexpr (Kind == 28) {
            std::cout << blocks.query(l, r).signed_max[l % 2] << '\n';
        } else if constexpr (Kind == 29) {
            i64 second = blocks.query(l, r).second;
            std::cout << (second == LOW ? -1 : second) << '\n';
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    switch (std::atoi(argv[1])) {
        case 24: return solve<24>();
        case 26: return solve<26>();
        case 27: return solve<27>();
        case 28: return solve<28>();
        case 29: return solve<29>();
        default: return 1;
    }
}
