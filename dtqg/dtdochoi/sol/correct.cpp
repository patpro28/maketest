#include <algorithm>
#include <cstdio>
#include <deque>
#include <vector>

struct Toy {
    int color;
    int size;
};

struct Extremes {
    int low;
    int high;

    void include(int value) {
        low = std::min(low, value);
        high = std::max(high, value);
    }

    int width() const { return high - low; }
};

class Input {
    char buffer[1 << 16];
    std::size_t position = 0;
    std::size_t length = 0;

    char next() {
        if (position == length) {
            length = std::fread(buffer, 1, sizeof buffer, stdin);
            position = 0;
            if (length == 0) return '\0';
        }
        return buffer[position++];
    }

public:
    int readInt() {
        char digit = next();
        while (digit && digit <= ' ') digit = next();
        int value = 0;
        while ('0' <= digit && digit <= '9') {
            value = 10 * value + digit - '0';
            digit = next();
        }
        return value;
    }
};

// The query endpoints move to the left, so indices enter in decreasing order.
template <class Key>
class SlidingMinimum {
    std::deque<int> indices;
    int next;
    Key key;

public:
    SlidingMinimum(int right, Key key) : next(right), key(key) {}

    int query(int low, int high) {
        if (low > high) return 1000000000;
        while (!indices.empty() && indices.front() > high) indices.pop_front();
        next = std::min(next, high);
        for (; next >= low; --next) {
            const int value = key(next);
            while (!indices.empty() && key(indices.back()) >= value) indices.pop_back();
            indices.push_back(next);
        }
        return key(indices.front());
    }
};

int main() {
    Input input;
    const int n = input.readInt();
    std::vector<Toy> toys(n);
    for (auto& toy : toys) {
        toy.color = input.readInt();
        toy.size = input.readInt();
    }
    std::sort(toys.begin(), toys.end(), [](const Toy& a, const Toy& b) {
        return a.color < b.color;
    });

    int minSizeIndex = n - 1;
    int maxSizeIndex = n - 1;
    std::vector<Extremes> suffix(n);
    suffix.back() = {toys.back().size, toys.back().size};
    for (int i = n - 2; i >= 0; --i) {
        suffix[i] = suffix[i + 1];
        if (toys[i].size < suffix[i].low) minSizeIndex = i;
        if (toys[i].size > suffix[i].high) maxSizeIndex = i;
        suffix[i].include(toys[i].size);
    }

    int best = suffix.front().width();
    Extremes prefix{toys.front().size, toys.front().size};
    for (int k = 1; k < n; ++k) {
        best = std::min(best, toys[k - 1].color - toys.front().color + suffix[k].width());
        best = std::min(best, toys.back().color - toys[k].color + prefix.width());
        prefix.include(toys[k].size);
    }

    prefix = {toys.front().size, toys.front().size};
    auto sweep = [&](int firstLeft, int lastLeft, int firstRight) {
        if (firstLeft > lastLeft || firstRight == n) return;

        int lowCut = n;
        int highCut = n;
        auto suffixWidth = [&](int k) { return toys[k - 1].color + suffix[k].width(); };
        auto suffixLow = [&](int k) { return toys[k - 1].color - suffix[k].low; };
        auto suffixHigh = [&](int k) { return toys[k - 1].color + suffix[k].high; };
        SlidingMinimum bothFromSuffix(n - 1, suffixWidth);
        SlidingMinimum lowFromSuffix(n - 1, suffixLow);
        SlidingMinimum highFromSuffix(n - 1, suffixHigh);

        for (int l = firstLeft; l <= lastLeft; ++l) {
            prefix.include(toys[l - 1].size);
            while (lowCut > firstRight && suffix[lowCut - 1].low >= prefix.low) --lowCut;
            while (highCut > firstRight && suffix[highCut - 1].high <= prefix.high) --highCut;

            const int leftColor = toys[l].color;
            best = std::min(best, bothFromSuffix.query(firstRight, std::min(lowCut, highCut) - 1) - leftColor);
            best = std::min(best, lowFromSuffix.query(highCut, lowCut - 1) + prefix.high - leftColor);
            best = std::min(best, highFromSuffix.query(lowCut, highCut - 1) - prefix.low - leftColor);

            const int bothFromPrefix = std::max(lowCut, highCut);
            if (bothFromPrefix < n) {
                best = std::min(best, toys[bothFromPrefix - 1].color - leftColor + prefix.width());
            }
        }
    };

    const int firstAnchor = std::min(minSizeIndex, maxSizeIndex);
    const int secondAnchor = std::max(minSizeIndex, maxSizeIndex);
    sweep(1, firstAnchor, firstAnchor + 1);
    sweep(firstAnchor + 1, secondAnchor, secondAnchor + 1);

    std::printf("%d\n", best);
}
