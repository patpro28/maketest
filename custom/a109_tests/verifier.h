#include <iostream>
#include <cstdlib>
#include <cstring>
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

void requireValid(bool condition) {
    if (!condition) { std::cerr << "Invalid binary input\n"; std::exit(1); }
}
template<class T> bool readBinary(T& value) {
    return bool(std::cin.read(reinterpret_cast<char*>(&value), sizeof(value)));
}
bool inRange(long long value, long long lo, long long hi) { return lo <= value && value <= hi; }
#if KIND == 4 || KIND == 9
void validateCode(const char* code, int size) {
    requireValid(code[0] >= 'A' && code[0] <= 'Z');
    bool padding = false;
    for (int j = 0; j < size; ++j) {
        if (code[j] == 0) padding = true;
        else requireValid(!padding && code[j] >= 'A' && code[j] <= 'Z');
    }
}
#endif
void validateRecord(const Record& r) {
#if KIND == 1
    requireValid(inRange(r.id, 1, 1000000000) && inRange(r.value, -1000000000, 1000000000));
#elif KIND == 2
    requireValid(inRange(r.id, 1, 1000000000) && inRange(r.score, 0, 10));
#elif KIND == 3
    requireValid(inRange(r.id, 1, 1000000000) && inRange(r.quantity, 0, 10000) && inRange(r.price, 0, 1000000000));
#elif KIND == 4
    validateCode(r.code, 8);
    for (int j = 0; j < 3; ++j) requireValid(inRange(r.score[j], 0, 10));
#elif KIND == 5
    requireValid(inRange(r.type, 1, 2) && inRange(r.amount, 0, 1000000000));
#elif KIND == 6
    requireValid(inRange(r.kind, 1, 3) && inRange(r.quantity, 0, 1000000000));
#elif KIND == 7
    requireValid(inRange(r.x, -1000000000, 1000000000) && inRange(r.y, -1000000000, 1000000000));
#elif KIND == 8
    requireValid((r.state == 'R' || r.state == 'S') && inRange(r.seconds, 0, 1000000000));
#elif KIND == 9
    validateCode(r.code, 12);
    requireValid(inRange(r.stock, 0, 1000000000));
#elif KIND == 10
    requireValid(inRange(r.date.year, 2000, 2100) && inRange(r.date.month, 1, 12) &&
        inRange(r.date.day, 1, 28) && inRange(r.temperature, -100, 100));
#endif
}
int main() {
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_BINARY);
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#if KIND == 1 || KIND == 8
    int n = 0;
    Record r;
    while (readBinary(r)) { validateRecord(r); requireValid(++n <= 200000); }
    requireValid(std::cin.eof() && std::cin.gcount() == 0);
#else
#if KIND == 3 || KIND == 4 || KIND == 6 || KIND == 7 || KIND == 9
    int n;
    requireValid(readBinary(n));
    requireValid(inRange(n, 1, 200000));
#else
    Header h;
    requireValid(readBinary(h));
    requireValid(inRange(h.n, 1, 200000));
    unsigned int n = h.n;
#endif
#if KIND == 2
    requireValid(inRange(h.threshold, 0, 10));
#elif KIND == 5
    requireValid(inRange(h.initial, -1000000000000LL, 1000000000000LL));
#elif KIND == 10
    requireValid(std::memcmp(h.magic, "A109", 4) == 0);
#endif
    for (unsigned int i = 0; i < static_cast<unsigned int>(n); ++i) {
        Record r;
        requireValid(readBinary(r));
        validateRecord(r);
    }
    requireValid(std::cin.get() == std::char_traits<char>::eof());
#endif
}
