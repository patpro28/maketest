#pragma once
#include <cstdio>
#include <string>
#include <vector>

// Buffered input/output, kept separate from the tree-DP algorithm.
class FastInput {
    char buffer[1 << 16];
    std::size_t position = 0,length = 0;
    int next() {
        if (position == length) {
            length = std::fread(buffer,1,sizeof(buffer),stdin);
            position = 0;
            if (length == 0) return EOF;
        }
        return static_cast<unsigned char>(buffer[position++]);
    }
public:
    template<class T> void read(T &value) {
        int c = next();
        while (c != EOF && c <= ' ') c = next();
        bool negative = c == '-';
        if (negative) c = next();
        long long result = 0;
        while ('0' <= c && c <= '9') {
            result = result*10+c-'0';
            c = next();
        }
        value = static_cast<T>(negative ? -result : result);
    }
};

template<class T> inline void writeArray(const std::vector<T> &values) {
    std::string output;
    output.reserve(values.size()*16);
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i) output.push_back(' ');
        output += std::to_string(values[i]);
    }
    output.push_back('\n');
    std::fwrite(output.data(),1,output.size(),stdout);
}

inline void writeValue(long long value) {
    std::string output = std::to_string(value)+"\n";
    std::fwrite(output.data(),1,output.size(),stdout);
}
