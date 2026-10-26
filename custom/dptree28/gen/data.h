#pragma once
#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"
using ll = long long;
struct Edge { int u,v; ll w; };

inline int expression(Random &rng,int seed,int mode) {
    int n;
    if (mode == 0) {
        const int sizes[] = {1,3,3,5,7,9,11,13,15,17,19,21};
        n = sizes[seed];
    } else if (mode == 1) n = 2*rng.uniform(0,8)+1;
    else if (mode == 2) n = 2*rng.uniform(100,2500)+1;
    else n = int(N_MAX);
    int m = (n-1)/2,shape = seed%3;
    std::vector<int> type(n,0),pos(n),leaves{0},label(n);
    std::vector<std::array<int,2>> child(n);
    std::vector<std::array<ll,3>> cost(n);
    int next = 1;
    for (int i = 0; i < m; ++i) {
        int index = shape == 1 ? pos[i] : shape == 2
            ? rng.uniform(0,int(leaves.size())-1) : int(leaves.size())-1;
        int u = leaves[index];
        leaves[index] = leaves.back(); pos[leaves[index]] = index; leaves.pop_back();
        type[u] = rng.uniform(1,2);
        child[u] = {next,next+1};
        for (int j = 0; j < 2; ++j) {
            pos[next] = int(leaves.size()); leaves.push_back(next++);
        }
    }
    for (auto &c : cost) for (ll &x : c) x = rng.uniform(0LL,ll(VALUE_MAX));
    if (mode == 1 || mode == 2) {
        if (seed%3 == 0) for (auto &c : cost) for (ll &x : c) x = rng.uniform(0LL,20LL);
    }
    if (mode == 0) {
        for (int u = 0; u < n; ++u) cost[u] = {u%3,7,11};
        if (seed == 0) cost[0] = {VALUE_MAX,3,0};
        if (seed == 1 || seed == 3 || seed == 7)
            for (int &t : type) if (t) t = 1;
        if (seed == 2 || seed == 4 || seed == 5 || seed == 6)
            for (int &t : type) if (t) t = 2;
        if (seed == 5 || seed == 7)
            for (auto &c : cost) c = {0,VALUE_MAX,VALUE_MAX};
        if (seed == 6) for (auto &c : cost) c = {VALUE_MAX,0,VALUE_MAX};
        if (seed == 8) for (auto &c : cost) c = {VALUE_MAX,VALUE_MAX,VALUE_MAX};
        if (seed == 9) for (auto &c : cost) c = {0,0,0};
    }
    if (mode == 3) {
        if (seed == 0 || seed == 1 || seed == 5)
            for (auto &c : cost) c = {VALUE_MAX,VALUE_MAX,VALUE_MAX};
        if (seed == 0 || seed == 3) for (int &t : type) if (t) t = 1;
        if (seed == 1 || seed == 4) for (int &t : type) if (t) t = 2;
        if (seed == 2) for (auto &c : cost) c = {0,0,0};
        if (seed == 3) for (auto &c : cost) c = {0,VALUE_MAX,VALUE_MAX};
        if (seed == 4) for (auto &c : cost) c = {VALUE_MAX,0,VALUE_MAX};
    }
    std::iota(label.begin(),label.end(),0);
    for (int i = n-1; i > 1; --i) std::swap(label[i],label[rng.uniform(1,i)]);
    std::vector<int> inverse(n);
    for (int u = 0; u < n; ++u) inverse[label[u]] = u;
    std::cout << n << ' ' << seed%3 << '\n';
    for (int id = 0; id < n; ++id) {
        int u = inverse[id];
        std::cout << type[u];
        if (type[u] == 0) for (ll c : cost[u]) std::cout << ' ' << c;
        else std::cout << ' ' << label[child[u][0]]+1 << ' ' << label[child[u][1]]+1;
        std::cout << '\n';
    }
    return 0;
}

inline int generate(int argc,char **argv,int mode) {
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261025ULL + PROBLEM_KIND*10000ULL + mode*100ULL + seed);
    if (PROBLEM_KIND == 28) return expression(rng,seed,mode);
    const ll LIM = VALUE_MAX;
    int n;
    if (mode == 0) {
        const int sizes[] = {1,2,3,4,5,6,7,8,9,10,12,15};
        n = sizes[seed];
    } else if (mode == 1) n = rng.uniform(1,16);
    else if (mode == 2) n = rng.uniform(200,6000);
    else n = int(N_MAX);
    int shape = seed%8;
    if (mode == 0) {
        const int shapes[] = {0,0,0,1,0,1,2,3,0,6,1,0};
        shape = shapes[seed];
    }
    std::vector<Edge> edges;
    for (int v = 1; v < n; ++v) {
        int p = 0;
        if (shape == 0) p = v-1;
        else if (shape == 1) p = 0;
        else if (shape == 2) p = (v-1)/2;
        else if (shape == 3) p = v < n/2 ? v-1 : n/2-1;
        else if (shape == 4) p = v < n/2 ? v-1 : (v-n/2)%(n/2);
        else if (shape == 5) p = v <= 4 ? 0 : v-4;
        else if (shape == 6) p = rng.uniform(0,v-1);
        else p = rng.uniform(std::max(0,v-30),v-1);
        edges.push_back({p,v,rng.uniform(PROBLEM_KIND == 30 ? -LIM : 0LL,LIM)});
    }
    std::vector<ll> value(n);
    for (ll &x : value) x = PROBLEM_KIND == 29 ? rng.uniform(0LL,2LL) : rng.uniform(-LIM,LIM);
    if (mode == 1 || mode == 2) {
        if (seed%3 == 0) {
            if (PROBLEM_KIND != 29) for (ll &x : value) x = rng.uniform(-10LL,10LL);
            for (auto &e : edges) e.w = rng.uniform(PROBLEM_KIND == 30 ? -10LL : 0LL,10LL);
        }
    }
    if (mode == 0) {
        if (PROBLEM_KIND == 27) {
            for (int i = 0; i < n; ++i) value[i] = i%3 == 0 ? -3 : LIM;
            if (seed == 0 || seed == 7) std::fill(value.begin(),value.end(),-LIM);
            if (seed == 1 || seed == 2 || seed == 3 || seed == 5)
                std::fill(value.begin(),value.end(),LIM);
            if (seed == 6) std::fill(value.begin(),value.end(),0);
        }
        if (PROBLEM_KIND == 29) {
            for (int i = 0; i < n; ++i) value[i] = i%3;
            if (seed == 0) value[0] = 0;
            if (seed == 1) value = {1,2};
            if (seed == 2) value = {1,0,2};
            if (seed == 5) std::fill(value.begin(),value.end(),1);
            if (seed == 6) { std::fill(value.begin(),value.end(),0); value.back() = 2; }
            if (seed == 8) for (int i = 0; i < n; ++i) value[i] = 1+i%2;
        }
        for (int i = 0; i < n-1; ++i) {
            edges[i].w = i%2 ? 1 : LIM;
            if (PROBLEM_KIND == 30) {
                if (seed == 1 || seed == 7) edges[i].w = -LIM;
                if (seed == 2 || seed == 3 || seed == 5 || seed == 8) edges[i].w = LIM;
                if (seed == 6) edges[i].w = 0;
            }
            if (PROBLEM_KIND == 29 && seed == 10) edges[i].w = 0;
        }
    }
    if (mode == 3) {
        if (PROBLEM_KIND == 27) {
            if (seed <= 1) std::fill(value.begin(),value.end(),LIM);
            if (seed == 2) std::fill(value.begin(),value.end(),-LIM);
            if (seed == 3) std::fill(value.begin(),value.end(),0);
        }
        if (PROBLEM_KIND == 29) {
            if (seed <= 1) {
                for (int i = 0; i < n; ++i) value[i] = seed == 0 ? 1+i%2 : i == 0 ? 1 : 2;
                for (auto &e : edges) e.w = LIM;
            }
            if (seed == 2) std::fill(value.begin(),value.end(),0);
            if (seed == 3) for (ll &x : value) x = rng.uniform(0LL,1LL);
            if (seed == 4) for (auto &e : edges) e.w = 0;
        }
        if (PROBLEM_KIND == 30) {
            for (auto &e : edges) {
                if (seed <= 1) e.w = LIM;
                if (seed == 2) e.w = -LIM;
                if (seed == 3) e.w = 0;
            }
        }
    }
    std::vector<int> label(n);
    std::iota(label.begin(),label.end(),0);
    if (mode == 0 && seed == 4) std::swap(label[0],label[n/2]);
    if (mode == 0 && seed == 5) std::swap(label[0],label[n-1]);
    if (mode != 0) {
        int first = seed >= 6 ? 0 : 1;
        for (int i = n-1; i > first; --i) std::swap(label[i],label[rng.uniform(first,i)]);
    }
    std::vector<ll> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = value[i];
    for (int i = int(edges.size())-1; i > 0; --i) std::swap(edges[i],edges[rng.uniform(0,i)]);
    std::cout << n << '\n';
    if (PROBLEM_KIND == 27 || PROBLEM_KIND == 29) {
        for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i];
        std::cout << '\n';
    }
    for (auto e : edges) {
        if (rng.uniform_bool()) std::swap(e.u,e.v);
        std::cout << label[e.u]+1 << ' ' << label[e.v]+1;
        if (PROBLEM_KIND == 29 || PROBLEM_KIND == 30) std::cout << ' ' << e.w;
        std::cout << '\n';
    }
    return 0;
}
