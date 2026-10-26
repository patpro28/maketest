#include "testlib.h"
#include "params.h"
#include <array>
#include <vector>

int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int n = inf.readInt(1,N_MAX,"N"); inf.readSpace();
    inf.readInt(0,2,"target"); inf.readEoln();
    ensuref(n % 2 == 1,"A full binary tree has odd size");
    std::vector<int> indegree(n,0),type(n);
    std::vector<std::array<int,2>> child(n);
    for (int u = 0; u < n; ++u) {
        type[u] = inf.readInt(0,2,"type"); inf.readSpace();
        if (type[u] == 0) {
            for (int r = 0; r < 3; ++r) {
                if (r) inf.readSpace();
                inf.readLong(0,VALUE_MAX,"cost");
            }
        } else {
            int x = inf.readInt(1,n,"x")-1; inf.readSpace();
            int y = inf.readInt(1,n,"y")-1;
            ensuref(x != y && x != u && y != u,"Invalid children");
            child[u] = {x,y};
            ensuref(++indegree[x] == 1 && ++indegree[y] == 1,"Child has multiple parents");
        }
        inf.readEoln();
    }
    inf.readEof();
    ensuref(indegree[0] == 0,"Root must have no parent");
    for (int u = 1; u < n; ++u) ensuref(indegree[u] == 1,"Non-root must have one parent");
    std::vector<int> order{0},seen(n,0);
    seen[0] = 1;
    for (int i = 0; i < int(order.size()); ++i) {
        int u = order[i];
        if (type[u]) for (int v : child[u]) {
            ensuref(!seen[v],"Cycle"); seen[v] = 1; order.push_back(v);
        }
    }
    ensuref(int(order.size()) == n,"Disconnected expression tree");
}
