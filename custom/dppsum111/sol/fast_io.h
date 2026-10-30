#ifndef PREFIX_FAST_IO_H
#define PREFIX_FAST_IO_H
#include <cstdio>
#include <string>

// Buffered input/output; all problem inputs are validated separately.
class FastInput {
    char buffer[1 << 16];
    size_t position = 0, length = 0;
    int next() {
        if (position == length) {
            length = std::fread(buffer, 1, sizeof(buffer), stdin);
            position = 0;
            if (!length) return EOF;
        }
        return static_cast<unsigned char>(buffer[position++]);
    }
    int first() {
        int c;
        do { c = next(); } while (c != EOF && c <= ' ');
        return c;
    }
public:
    template<class T> FastInput &operator>>(T &value) {
        int c = first();
        bool negative = c == '-';
        if (negative) c = next();
        long long x = 0;
        while (c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = next();
        }
        value = static_cast<T>(negative ? -x : x);
        return *this;
    }
    FastInput &operator>>(std::string &value) {
        value.clear();
        int c = first();
        while (c != EOF && c > ' ') {
            value.push_back(static_cast<char>(c));
            c = next();
        }
        return *this;
    }
    FastInput &operator>>(char &value) {
        value = static_cast<char>(first());
        return *this;
    }
};

class FastOutput {
    char buffer[1 << 16];
    size_t length = 0;
    void put(char c) {
        if (length == sizeof(buffer)) flush();
        buffer[length++] = c;
    }
    void flush() {
        std::fwrite(buffer, 1, length, stdout);
        length = 0;
    }
public:
    ~FastOutput() { flush(); }
    FastOutput &operator<<(char c) { put(c); return *this; }
    template<class T> FastOutput &operator<<(T value) {
        long long x = value;
        if (x < 0) { put('-'); x = -x; }
        char digits[32];
        int count = 0;
        do { digits[count++] = static_cast<char>('0' + x % 10); x /= 10; } while (x);
        while (count) put(digits[--count]);
        return *this;
    }
};
#endif
