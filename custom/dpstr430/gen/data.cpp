#include "random.h"
#include "../params.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

string cycle(const string &pattern, int n) {
    string result(n, ' ');
    for (int i = 0; i < n; ++i) result[i] = pattern[i % pattern.size()];
    return result;
}

void emit(const string &s, const vector<pair<string, long long>> &entries) {
    cout << s.size() << ' ' << entries.size() << '\n' << s << '\n';
    for (const auto &entry : entries) cout << entry.first << ' ' << entry.second << '\n';
}

void maximum(int kind) {
    const int n = N_MAX;
    if (kind == 0) {
        vector<pair<string, long long>> entries;
        for (int i = 0; i < 10000; ++i) entries.emplace_back("aaaaa", 7 + i);
        emit(string(n, 'a'), entries);
    } else if (kind == 1) {
        emit(string(n, 'a'), {{"a", 1000000000}, {string(100, 'a'), 1000000000}});
    } else if (kind == 2) {
        emit(string(n - 1, 'a') + 'b', {{"a", 1}, {"aa", 1}});
    } else {
        emit(cycle("ab", n), {{"ab", 0}, {"a", 100}, {"b", 100}});
    }
}

int main(int argc, char **argv) {
    int seed = argc > 1 ? atoi(argv[1]) : 0;
    const char *edges[] = {
        "1 1\na\nb 1\n",
        "1 1\na\na 0\n",
        "1 2\na\na 9\na 1\n",
        "3 3\nabc\na 1\nab 0\nbc 2\n",
        "4 1\naaaa\na 1000000000\n",
        "3 1\nabc\nabc 7\n",
        "4 2\naaaa\naa 2\naaa 0\n",
        "5 2\nababa\nab 1\naba 3\n",
        "3 2\nabc\nab 1\nbc 1\n",
        "6 3\naaaaaa\na 7\naa 1\naaa 3\n",
        "3 2\nzzz\nzz 0\nz 1\n",
        "2 3\nab\nab 9\na 3\nb 3\n"
    };
    if (seed < 12) {
        cout << edges[seed];
        return 0;
    }
    if (seed >= 26) {
        maximum(seed - 26);
        return 0;
    }
    Random rng(20261108430ULL + seed);
    const int lowSize = seed < 20 ? 1 : 12;
    const int highSize = seed < 20 ? 9 : 45;
    const int n = rng.uniform(lowSize, highSize);
    auto word = [&](const string &alphabet, int length) {
        string result(length, ' ');
        for (char &ch : result) ch = alphabet[rng.uniform(0, int(alphabet.size()) - 1)];
        return result;
    };
    string s = word("abc", n);
    vector<pair<string, long long>> entries;
    const int count = rng.uniform(2, 10);
    const long long prices[] = {0, 1, 7, 1000000000};
    for (int i = 0; i < count; ++i) {
        int start = rng.uniform(0, n - 1);
        int length = rng.uniform(1, 5);
        entries.emplace_back(s.substr(start, length), prices[rng.uniform(0, 3)]);
    }
    if (seed % 2 == 0) {
        for (char ch : string("abc")) entries.emplace_back(string(1, ch), rng.uniform(1, 10));
    }
    emit(s, entries);
}
