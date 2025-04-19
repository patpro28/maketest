/*
Author: Tu Pham Anh
Date: 2024/10/26 - 22:36
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;
using ll = long long;

/**
    * @struct LazySegmentTree
    * @brief Segment Tree with lazy propagation
    * @tparam Node Type of the node
    * @tparam Lazy Type of the lazy
    * @details
    * 1. Node must have a default constructor
    * 2. Lazy must have a default constructor
    * 3. Node must have a operator + with Node
    * 4. Node must have a operator + with Lazy
    * 5. Lazy must have a operator + with Lazy
    * @example
    *	 struct Node {
    *		 ll sum, sz;
    *		 Node() : sum(0), sz(0) {}
    *		 Node(ll x, ll y) : sum(x), sz(y) {}
    *		 Node operator +(Node x) {
    *			 return Node(sum + x.sum, sz + x.sz);
    *		 }
    *		 Node operator +(Lazy x) {
    *			return Node(sum + x.a * sz, sz);
    *		 } 
    *	 };
    *	 struct Lazy {
    *		 ll a;
    *		 Lazy() : a(0) {}
    *		 Lazy(ll x) : a(x) {}
    *		 Lazy operator +(Lazy x) {
    *			 return Lazy(a + x.a);
    *		 }
    *	 };
    *	 vector<Node> a(n);
    *	 LazySegmentTree<Node, Lazy> st(a);
    *	 st.sum(l, r);
    *	 st.update(l, r, Lazy(x));
*/
template <typename Node, typename Lazy> 
struct LazySegmentTree {
    public:
        /**
            * @brief Constructor
            * @param a vector of nodes
        */
        LazySegmentTree(vector<Node> &a) : _n(a.size()) {
            t.resize(_n << 2);
            lazy.resize(_n << 2);
            build(a, 0, _n - 1);
        }

        /**
            * @brief Sum on the interval [l, r]
            * @param l left bound
            * @param r right bound
            * @return sum on the interval [l, r]
        */
        Node sum(int l, int r) {
            return sum(0, _n - 1, l, r);
        }

        /**
            * @brief Update on the interval [l, r]
            * @param l left bound
            * @param r right bound
            * @param v the lazy value add to the interval [l, r]
        */
        void update(int l, int r, Lazy v) {
            update(0, _n - 1, l, r, v);
        }

    private:
        vector<Node> t;
        vector<Lazy> lazy;

        int _n;

        void up(int k, Lazy v) {
            t[k] = t[k] + v;
            lazy[k] = lazy[k] + v;
        }

        void push(int k) {
            up(k + k, lazy[k]);
            up(k + k + 1, lazy[k]);
            lazy[k] = Lazy();
        }

        void build(vector<Node> &a, int tl, int tr, int k = 1) {
            if (tl == tr) {
                t[k] = a[tl];
                return;
            }
            int mid = (tl + tr) >> 1;
            build(a, tl, mid, k + k);				 
            build(a, mid + 1, tr, k + k + 1); 
            t[k] = t[k + k] + t[k + k + 1];
        }


        void update(int tl, int tr, int l, int r, Lazy v, int k = 1) {
            if (tl > r || l > tr)
                return;
            if (l <= tl and tr <= r) {
                up(k, v);
                return;
            }
            push(k);
            int mid = (tl + tr) >> 1;
            update(tl, mid, l, r, v, k + k);
            update(mid + 1, tr, l, r, v, k + k + 1);
            t[k] = t[k + k] + t[k + k + 1];
        }

        Node sum(int tl, int tr, int l, int r, int k = 1) {
            if (tl > r || l > tr)
                return Node();
            if (l <= tl and tr <= r)
                return t[k];
            push(k);
            int mid = (tl + tr) >> 1;
            return sum(tl, mid, l, r, k + k) + sum(mid + 1, tr, l, r, k + k + 1);
        }
};

struct Lazy {
    int type, val;
    // type = -1: do nothing
    // type = 0: assign
    // type = 1: flip
    Lazy(int _type = -1, int _val = 0) : type(_type), val(_val) {}
    Lazy operator +(Lazy x) {
        if (x.type == -1) return *this;
        if (x.type == 0) return x;
        if (type == 0) return x.val ? Lazy(0, 1 - val) : *this;
        return Lazy(1, (val + x.val) & 1);
    }
};

struct Node {
    ll ans, sum, sz;
    Node(ll _ans = 0, ll _sum = 0, ll _sz = 0) : ans(_ans), sum(_sum), sz(_sz) {}
    Node operator +(Node x) {
        return Node(ans ^ x.ans, sum + x.sum, sz + x.sz);
    }
    Node operator +(Lazy x) {
        if (x.type == 0) return Node(x.val * sz % 2, x.val * sz, sz);
        if (x.type == -1 || x.val == 0) return *this;
        return Node((sz - sum) % 2, sz - sum, sz);
    }
};

const int MAX_BIT = 18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<Node> a[MAX_BIT];
    for (int i = 0; i < MAX_BIT; i++) {
        a[i].resize(n, Node(0, 0, 1));
    }

    vector<LazySegmentTree<Node, Lazy>> st;
    for (int i = 0; i < MAX_BIT; i++)
        st.push_back(LazySegmentTree<Node, Lazy>(a[i]));

    while (q--) {
        int type, l, r, x;
        cin >> type >> l >> r;
        if (type == 1) {
            cin >> x;
            for (int i = 0; i < MAX_BIT; ++i) {
                if (x >> i & 1) {
                    st[i].update(l - 1, r - 1, Lazy(0, 1));
                }
                // debug(type, st[i].sum(0, n - 1).sum);
            }
        }
        if (type == 2) {
            cin >> x;
            for (int i = 0; i < MAX_BIT; ++i) {
                if (!(x >> i & 1)) {
                    st[i].update(l - 1, r - 1, Lazy(0, 0));
                }
                // debug(type, st[i].sum(0, n - 1).sum);
            }
        }
        if (type == 3) {
            cin >> x;
            for (int i = 0; i < MAX_BIT; ++i) {
                if (x >> i & 1) {
                    st[i].update(l - 1, r - 1, Lazy(1, 1));
                }
                // debug(type, st[i].sum(0, n - 1).sum);
            }
        }
        if (type == 4) {
            ll sum = 0;
            for (int i = 0; i < MAX_BIT; i++) {
                sum += st[i].sum(l - 1, r - 1).sum << i;
            }
            // debug(type, sum);
            cout << sum << '\n';
        }
        if (type == 5) {
            ll ans = 0;
            for (int i = 0; i < MAX_BIT; i++) {
                ans += st[i].sum(l - 1, r - 1).ans << i;
            }
            // debug(type, ans);
            cout << ans << '\n';
        }
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}