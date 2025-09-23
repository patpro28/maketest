/*
Author: Tu Pham Anh
Date: 2025/06/09 - 15:35
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

/*
Basic implementation of big integer class in C++.
Supports addition, subtraction and multiplication positive integers.

Example:
    bigint a = 123456789;
    bigint b = "987654321";
    bigint c;
    cin >> c;
    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * c << endl;
    cout << a * 123 << endl;
*/
const int base = 1000000000;
const int base_digits = 9;
struct bigint
{
    vector<int> a;

    bigint(long long v = 0) { *this = v; }

    bigint(const string &s) { read(s); }

    void operator=(long long v)
    {
        a.clear();
        for (; v > 0; v = v / base)
            a.push_back(v % base);
    }

    void operator+=(const bigint &v)
    {
        for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i)
        {
            if (i == (int)a.size())
                a.push_back(0);
            a[i] += carry + (i < (int)v.a.size() ? v.a[i] : 0);
            carry = a[i] >= base;
            if (carry)
                a[i] -= base;
        }
    }

    bigint operator+(const bigint &v) const
    {
        bigint res = *this;
        res += v;
        return res;
    }

    void operator-=(const bigint &v)
    {
        for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i)
        {
            a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry)
                a[i] += base;
        }
        trim();
    }

    bigint operator-(const bigint &v) const
    {
        bigint res = *this;
        res -= v;
        return res;
    }

    void operator*=(const int &v)
    {
        for (int i = 0, carry = 0; i < (int)a.size() || carry; ++i)
        {
            if (i == (int)a.size())
                a.push_back(0);
            long long cur = a[i] * 1ll * v + carry;
            carry = (int)(cur / base);
            a[i] = (int)(cur % base);
        }
        trim();
    }

    bigint operator*(int v) const
    {
        bigint res = *this;
        res *= v;
        return res;
    }

    bigint operator*(const bigint &v) const
    {
        bigint res;
        res.a.resize(a.size() + v.a.size());
        for (int i = 0; i < (int)a.size(); ++i)
            if (a[i])
                for (int j = 0, carry = 0; j < (int)v.a.size() || carry; ++j)
                {
                    long long cur = res.a[i + j] + a[i] * 1ll * (j < (int)v.a.size() ? v.a[j] : 0) + carry;
                    carry = (int)(cur / base);
                    res.a[i + j] = (int)(cur % base);
                }
        res.trim();
        return res;
    }

    bool operator<(const bigint &v) const
    {
        if (a.size() != v.a.size())
            return a.size() < v.a.size();
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] < v.a[i];
        return false;
    }

    bool operator>(const bigint &v) const { return v < *this; }
    bool operator<=(const bigint &v) const { return !(v < *this); }
    bool operator>=(const bigint &v) const { return !(*this < v); }
    bool operator==(const bigint &v) const
    {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const bigint &v) const { return *this < v || v < *this; }

    void trim()
    {
        while (!a.empty() && !a.back())
            a.pop_back();
    }

    void read(const string &s)
    {
        a.clear();
        for (int i = s.size() - 1; i >= 0; i -= base_digits)
        {
            int x = 0;
            for (int j = max(0, i - base_digits + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }

    friend istream &operator>>(istream &stream, bigint &v)
    {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream &operator<<(ostream &stream, const bigint &v)
    {
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int)v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    bigint a, b;
    cin >> a >> b;
    cout << a * b;
    return 0;
}