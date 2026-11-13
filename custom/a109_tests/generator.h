#include <iostream>
#include <random>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

template<class T> void writeBinary(const T& value) {
    std::cout.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

int main(int argc, char** argv) {
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_BINARY);
#endif
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    std::mt19937 rng(1090000u + KIND * 1000u + GEN_GROUP * 100u + seed);
    auto number = [&](int lo, int hi) {
        return lo + int(rng() % static_cast<unsigned int>(hi - lo + 1));
    };
    int n;
    if (GEN_GROUP == 0) {
        const int sizes[8] = {1, 1, 2, 3, 8, 13, 26, 100};
        n = sizes[seed % 8];
#if KIND == 1 || KIND == 8
        if (seed == 0) n = 0;
#endif
    } else if (GEN_GROUP == 1) n = number(1, 12);
    else if (GEN_GROUP == 2) n = number(100, 5000);
    else n = 200000;
    (void)number;

#if KIND == 3 || KIND == 4 || KIND == 6 || KIND == 7 || KIND == 9
    writeBinary(n);
#elif KIND != 1 && KIND != 8
    Header h;
    std::memset(&h, 0, sizeof(h));
    h.n = n;
#if KIND == 2
    h.threshold = GEN_GROUP == 0 ? seed % 11 : number(0, 10);
#elif KIND == 5
    h.initial = seed % 2 ? -1000000000000LL : 1000000000000LL;
#elif KIND == 10
    std::memcpy(h.magic, "A109", 4);
#endif
    writeBinary(h);
#endif

    for (int i = 0; i < n; ++i) {
        Record r;
        std::memset(&r, 0, sizeof(r));
        bool extreme = GEN_GROUP == 3 || (GEN_GROUP == 0 && seed >= 4);
        (void)extreme;
#if KIND == 1
        r.id = i % 3 == 0 ? 10 : i % 3 == 1 ? 13 : 26;
        r.value = extreme ? (seed == 0 ? 1000000000 : seed == 1 ? -1000000000 :
            (i % 2 ? -1000000000 : 1000000000)) : number(-100, 100);
#elif KIND == 2
        r.id = i + 1;
        r.score = extreme ? (seed == 0 ? 10 : seed == 1 ? 0 : h.threshold) : number(0, 10);
#elif KIND == 3
        r.id = i + 1;
        r.quantity = extreme ? (seed == 1 ? 0 : 10000) : number(0, 10000);
        r.price = extreme ? (seed == 2 ? 0 : 1000000000LL) : number(0, 1000000000);
#elif KIND == 4
        int length = GEN_GROUP == 0 ? 1 + seed % 8 : number(1, 8);
        if (GEN_GROUP == 3) length = 8;
        for (int j = 0; j < length; ++j) r.code[j] = char('A' + number(0, 25));
        for (int j = 0; j < 3; ++j) r.score[j] = extreme ? (seed % 2 ? 0 : 10) : number(0, 10);
#elif KIND == 5
        r.type = extreme ? (seed == 0 ? 1 : seed == 1 ? 2 : i % 2 + 1) : number(1, 2);
        r.amount = extreme ? 1000000000LL : number(0, 1000000000);
#elif KIND == 6
        r.kind = extreme && seed < 2 ? seed + 1 : number(1, 3);
        r.quantity = extreme ? (seed == 2 ? 0 : 1000000000) : number(0, 1000000000);
#elif KIND == 7
        const int xs[9] = {0, 0, 1, -1, -1, 1, 0, 1000000000, -1000000000};
        const int ys[9] = {0, 1, 1, 1, -1, -1, -1, -1000000000, 1000000000};
        if (GEN_GROUP == 0 || extreme) {
            r.x = xs[(i + seed) % 9]; r.y = ys[(i + seed) % 9];
        } else { r.x = number(-1000000000, 1000000000); r.y = number(-1000000000, 1000000000); }
#elif KIND == 8
        r.state = extreme ? (seed == 0 ? 'R' : seed == 1 ? 'S' : (i % 2 ? 'R' : 'S')) : (number(0, 1) ? 'R' : 'S');
        r.seconds = extreme ? 1000000000 : number(0, 1000000000);
#elif KIND == 9
        int length = GEN_GROUP == 0 ? 1 + seed % 12 : number(1, 12);
        if (GEN_GROUP == 3) length = 12;
        for (int j = 0; j < length; ++j) r.code[j] = char('A' + number(0, 25));
        r.stock = extreme ? (seed == 1 ? 0 : 1000000000) : number(0, 100);
#elif KIND == 10
        r.date.year = number(2000, 2100);
        r.date.month = number(1, 12);
        r.date.day = number(1, 28);
        r.temperature = extreme ? (seed == 0 ? -100 : seed == 1 ? 100 : 0) : number(-100, 100);
#endif
        writeBinary(r);
    }
}
