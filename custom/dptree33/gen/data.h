#pragma once
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

inline int generate(int argc,char **argv,int mode) {
    using ll = long long;
    int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    Random rng(20261028ULL+PROBLEM_KIND*10000ULL+mode*100ULL+seed);
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
    std::vector<std::pair<int,int>> edges;
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
        edges.push_back({p,v});
    }
    std::vector<ll> value(n);
    for (ll &x : value) x = rng.uniform(PROBLEM_KIND == 34 ? -LIM : 0LL,LIM);
    if (mode == 1 || mode == 2) {
        if (seed%3 == 0)
            for (ll &x : value) x = rng.uniform(PROBLEM_KIND == 34 ? -10LL : 0LL,10LL);
    }
    if (mode == 0) {
        for (int i = 0; i < n; ++i) value[i] = i%2 ? 1 : LIM;
        if (PROBLEM_KIND == 32) {
            if (seed == 0 || seed == 6) std::fill(value.begin(),value.end(),0);
            if (seed == 1 || seed >= 10) std::fill(value.begin(),value.end(),LIM);
        }
        if (PROBLEM_KIND == 34) {
            if (seed == 0 || seed == 6) std::fill(value.begin(),value.end(),-LIM);
            if (seed == 1) value = {-5,-7};
            if (seed == 2) value = {10,-20,-3};
            if (seed == 3) value = {-5,-10,-2,-7};
            if (seed == 5) {
                std::fill(value.begin(),value.end(),-LIM);
                value.back() = LIM;
            }
            if (seed == 7) std::fill(value.begin(),value.end(),0);
            if (seed == 8) std::fill(value.begin(),value.end(),LIM);
        }
        if (PROBLEM_KIND == 35) {
            if (seed == 0) value[0] = 7;
            if (seed == 1) value = {LIM,1};
            if (seed == 2) value = {7,9,3};
            if (seed == 3 || seed == 5) {
                std::fill(value.begin(),value.end(),1);
                value[0] = LIM;
                if (seed == 5) value.back() = LIM;
            }
            if (seed == 6) std::fill(value.begin(),value.end(),0);
            if (seed == 7 || seed >= 10) std::fill(value.begin(),value.end(),LIM);
            if (seed == 8) for (int i = 0; i < n; ++i) value[i] = 100-i;
            if (seed == 9) {
                std::fill(value.begin(),value.end(),LIM);
                value[0] = 1;
            }
        }
    }
    if (mode == 3) {
        if (PROBLEM_KIND == 32) {
            if (seed <= 2) std::fill(value.begin(),value.end(),LIM);
            if (seed == 3) std::fill(value.begin(),value.end(),0);
        }
        if (PROBLEM_KIND == 34) {
            if (seed <= 1) std::fill(value.begin(),value.end(),LIM);
            if (seed == 2 || seed == 5) std::fill(value.begin(),value.end(),-LIM);
            if (seed == 3) std::fill(value.begin(),value.end(),0);
        }
        if (PROBLEM_KIND == 35) {
            if (seed <= 1) std::fill(value.begin(),value.end(),LIM);
            if (seed == 2 || seed == 4) std::fill(value.begin(),value.end(),1);
            if (seed == 3) std::fill(value.begin(),value.end(),0);
            if (seed == 4) value[0] = LIM;
        }
    }
    std::vector<int> label(n);
    std::iota(label.begin(),label.end(),0);
    if (mode == 0 && seed == 4) std::swap(label[0],label[n/2]);
    if (mode == 0 && seed == 5) std::swap(label[0],label[n-1]);
    if (mode != 0) {
        int first = seed >= 6 ? 0 : 1;
        for (int i = n-1; i > first; --i)
            std::swap(label[i],label[rng.uniform(first,i)]);
    }
    std::vector<ll> printed(n);
    for (int i = 0; i < n; ++i) printed[label[i]] = value[i];
    for (int i = int(edges.size())-1; i > 0; --i)
        std::swap(edges[i],edges[rng.uniform(0,i)]);
    std::cout << n << '\n';
    if (PROBLEM_KIND == 32 || PROBLEM_KIND == 34 || PROBLEM_KIND == 35) {
        for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << printed[i];
        std::cout << '\n';
    }
    for (auto e : edges) {
        if (rng.uniform_bool()) std::swap(e.first,e.second);
        std::cout << label[e.first]+1 << ' ' << label[e.second]+1 << '\n';
    }
    return 0;
}
