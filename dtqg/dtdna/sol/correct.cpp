#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

using Code = __uint128_t;
struct CodeHash
{
    size_t operator()(Code x) const
    {
        uint64_t a = uint64_t(x), b = uint64_t(x >> 64);
        a ^= b + 0x9e3779b97f4a7c15ULL + (a << 6) + (a >> 2);
        a ^= a >> 30;
        a *= 0xbf58476d1ce4e5b9ULL;
        a ^= a >> 27;
        a *= 0x94d049bb133111ebULL;
        return a ^ (a >> 31);
    }
};
Code encode(const string &s)
{
    Code value = 0;
    string alphabet = "ADGT";
    for (int i = 0; i < int(s.size()); ++i)
        value |= Code(alphabet.find(s[i])) << (2 * i);
    return value;
}
Code reverse_segment(Code x, int l, int r)
{
    while (l < r)
    {
        Code a = (x >> (2 * l)) & 3, b = (x >> (2 * r)) & 3;
        Code diff = a ^ b;
        x ^= (diff << (2 * l)) | (diff << (2 * r));
        ++l;
        --r;
    }
    return x;
}
int main()
{
    if (FILE *input = fopen("DNA.INP", "r"))
    {
        fclose(input);
        freopen("DNA.INP", "r", stdin);
        freopen("DNA.OUT", "w", stdout);
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    cin >> a >> b;
    string sa = a, sb = b;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    if (sa != sb)
    {
        cout << "Different\n";
        return 0;
    }
    if (a == b)
    {
        cout << "Similar\n";
        return 0;
    }
    int n = a.size();
    vector<pair<int, int>> ranges;
    for (int l = 0; l < n; ++l)
        for (int r = l + 1; r < n; ++r)
            ranges.push_back({l, r});
    Code start = encode(a), target = encode(b);
    vector<Code> first_a(1, start), first_b(1, target);
    for (auto [l, r] : ranges)
    {
        first_a.push_back(reverse_segment(start, l, r));
        first_b.push_back(reverse_segment(target, l, r));
    }
    unordered_set<Code, CodeHash> seen;
    seen.max_load_factor(0.8);
    seen.reserve((ranges.size() + 1) * (ranges.size() + 1));
    for (Code x : first_a)
    {
        seen.insert(x);
        for (auto [l, r] : ranges)
            seen.insert(reverse_segment(x, l, r));
    }
    for (Code x : first_b)
    {
        if (seen.count(x))
        {
            cout << "Similar\n";
            return 0;
        }
        for (auto [l, r] : ranges)
            if (seen.count(reverse_segment(x, l, r)))
            {
                cout << "Similar\n";
                return 0;
            }
    }
    cout << "Different\n";
}
