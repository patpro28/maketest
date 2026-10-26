#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>

int main(int argc, char **argv) {
    registerValidation(argc,argv);
    int n = inf.readInt(1,N_MAX,"N"); inf.readEoln();
    if (PROBLEM_KIND == 27 || PROBLEM_KIND == 29) {
        for (int i = 0; i < n; ++i) {
            if (i) inf.readSpace();
            if (PROBLEM_KIND == 27) inf.readLong(-VALUE_MAX,VALUE_MAX,"A");
            else inf.readInt(0,2,"T");
        }
        inf.readEoln();
    }
    std::vector<int> p(n),size(n,1);
    std::iota(p.begin(),p.end(),0);
    auto find = [&](int u) {
        while (p[u] != u) { p[u] = p[p[u]]; u = p[u]; }
        return u;
    };
    for (int i = 1; i < n; ++i) {
        int u = inf.readInt(1,n,"u")-1; inf.readSpace();
        int v = inf.readInt(1,n,"v")-1;
        ensuref(u != v,"Self-loop");
        if (PROBLEM_KIND == 29 || PROBLEM_KIND == 30) {
            inf.readSpace();
            inf.readLong(PROBLEM_KIND == 30 ? -VALUE_MAX : 0,VALUE_MAX,"W");
        }
        inf.readEoln();
        int a = find(u),b = find(v);
        ensuref(a != b,"Cycle or duplicate edge");
        if (size[a] < size[b]) std::swap(a,b);
        p[b] = a; size[a] += size[b];
    }
    inf.readEof();
}
