#pragma once
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

struct Slope {
    using ll = long long;
    std::priority_queue<ll> left;
    std::priority_queue<ll, std::vector<ll>, std::greater<ll>> right;
    ll offset_l = 0, offset_r = 0, minimum = 0;
    int size() const { return int(left.size() + right.size()); }
    void add_left(ll a) {
        if (!right.empty() && right.top() + offset_r < a) {
            ll x = right.top() + offset_r; right.pop();
            minimum += a - x;
            right.push(a - offset_r); left.push(x - offset_l);
        } else left.push(a - offset_l);
    }
    void add_right(ll a) {
        if (!left.empty() && left.top() + offset_l > a) {
            ll x = left.top() + offset_l; left.pop();
            minimum += x - a;
            left.push(a - offset_l); right.push(x - offset_r);
        } else right.push(a - offset_r);
    }
    void add_abs(ll a) { add_left(a); add_right(a); }
    void window(ll move_left, ll move_right) {
        offset_l -= move_left; offset_r += move_right;
    }
    void merge(Slope& other) {
        if (size() < other.size()) std::swap(*this, other);
        minimum += other.minimum;
        while (!other.left.empty()) {
            ll x = other.left.top() + other.offset_l;
            other.left.pop(); add_left(x);
        }
        while (!other.right.empty()) {
            ll x = other.right.top() + other.offset_r;
            other.right.pop(); add_right(x);
        }
    }
};
