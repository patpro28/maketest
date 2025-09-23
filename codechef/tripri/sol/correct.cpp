// subtask 2
#include <bits/stdc++.h>
using namespace std;
#ifdef tabr
#include "library/debug.cpp"
#else
#define debug(...)
#endif

#define IGNORE_CR

struct input_checker {
    string buffer;
    int pos;

    const string all = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const string number = "0123456789";
    const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string lower = "abcdefghijklmnopqrstuvwxyz";

    input_checker() {
        pos = 0;
        while (true) {
            int c = cin.get();
            if (c == -1) {
                break;
            }
#ifdef IGNORE_CR
            if (c == '\r') {
                continue;
            }
#endif
            buffer.push_back((char) c);
        }
    }

    string readOne() {
        assert(pos < (int) buffer.size());
        string res;
        while (pos < (int) buffer.size() && buffer[pos] != ' ' && buffer[pos] != '\n') {
            assert(!isspace(buffer[pos]));
            res += buffer[pos];
            pos++;
        }
        return res;
    }

    string readString(int min_len, int max_len, const string& pattern = "") {
        assert(min_len <= max_len);
        string res = readOne();
        assert(min_len <= (int) res.size());
        assert((int) res.size() <= max_len);
        for (int i = 0; i < (int) res.size(); i++) {
            assert(pattern.empty() || pattern.find(res[i]) != string::npos);
        }
        return res;
    }

    int readInt(int min_val, int max_val) {
        assert(min_val <= max_val);
        int res = stoi(readOne());
        assert(min_val <= res);
        assert(res <= max_val);
        return res;
    }

    long long readLong(long long min_val, long long max_val) {
        assert(min_val <= max_val);
        long long res = stoll(readOne());
        assert(min_val <= res);
        assert(res <= max_val);
        return res;
    }

    vector<int> readInts(int size, int min_val, int max_val) {
        assert(min_val <= max_val);
        vector<int> res(size);
        for (int i = 0; i < size; i++) {
            res[i] = readInt(min_val, max_val);
            if (i != size - 1) {
                readSpace();
            }
        }
        return res;
    }

    vector<long long> readLongs(int size, long long min_val, long long max_val) {
        assert(min_val <= max_val);
        vector<long long> res(size);
        for (int i = 0; i < size; i++) {
            res[i] = readLong(min_val, max_val);
            if (i != size - 1) {
                readSpace();
            }
        }
        return res;
    }

    void readSpace() {
        assert((int) buffer.size() > pos);
        assert(buffer[pos] == ' ');
        pos++;
    }

    void readEoln() {
        assert((int) buffer.size() > pos);
        assert(buffer[pos] == '\n');
        pos++;
    }

    void readEof() {
        assert((int) buffer.size() == pos);
    }
};

int main() {
    input_checker in;
    const int MAX = 100000;
    vector<int> primes;
    vector<bool> is_prime(MAX, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < MAX; i++) {
        if (!is_prime[i]) {
            continue;
        }
        primes.emplace_back(i);
        if ((long long) i * i >= MAX) {
            continue;
        }
        for (int j = i * i; j < MAX; j += i) {
            if (is_prime[j]) {
                is_prime[j] = false;
            }
        }
    }
    int tt = in.readInt(1, 500);
    in.readEoln();
    while (tt--) {
        long long n = in.readLong(0, 1e10);
        in.readEoln();
        assert(n % 2 == 0);
        string ans = "No";
        for (int p : primes) {
            long long x = n - 4 - p * 1LL * p;
            if (x <= 0) {
                break;
            }
            long long y = llround(sqrtl(x));
            while (y * y > x) {
                y--;
            }
            while ((y + 1) * (y + 1) <= x) {
                y++;
            }
            if (x == y * y && p != y && is_prime[y]) {
                ans = "Yes";
            }
        }
        cout << ans << '\n';
    }
    in.readEof();
    return 0;
}