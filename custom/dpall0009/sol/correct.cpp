#include <algorithm>
#include <cstdio>
#include <vector>

constexpr long long UNREACHABLE = -(1LL << 60);

class Input {
    char buffer[1 << 16];
    size_t position = 0;
    size_t length = 0;

    int nextChar() {
        if (position == length) {
            length = std::fread(buffer, 1, sizeof(buffer), stdin);
            position = 0;
        }
        return position < length ? buffer[position++] : EOF;
    }

public:
    int readInt() {
        int ch = nextChar();
        while (ch != EOF && ch <= ' ') ch = nextChar();
        const bool negative = ch == '-';
        if (negative) ch = nextChar();

        int value = 0;
        while ('0' <= ch && ch <= '9') {
            value = value * 10 + ch - '0';
            ch = nextChar();
        }
        return negative ? -value : value;
    }
};

int main() {
    Input input;
    const int rows = input.readInt();
    const int cols = input.readInt();
    std::vector<long long> best(cols, 0);
    std::vector<long long> row(cols), fromLeft(cols);
    for (int i = 0; i < rows; ++i) {
        for (auto& cell : row) cell = input.readInt();

        long long running = UNREACHABLE;
        for (int j = 0; j < cols; ++j) {
            running = row[j] + std::max(best[j], running);
            fromLeft[j] = running;
        }

        running = UNREACHABLE;
        for (int j = cols - 1; j >= 0; --j) {
            running = row[j] + std::max(best[j], running);
            best[j] = std::max(fromLeft[j], running);
        }
    }
    std::printf("%lld\n", *std::max_element(best.begin(), best.end()));
}
