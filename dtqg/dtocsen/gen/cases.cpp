#include "testlib.h"
#include "../params.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int id = atoi(argv[1]);
    const vector<pair<long long, vector<long long>>> fixed = {
        {1, {1}}, {2, {5}}, {5, {-1, 0, -2}},
        {8, {4, -8, 4}}, {8, {4, -10, 4}},
        {H_MAX, {1}}, {H_MAX, {-P_MAX, P_MAX - 1, 2}},
        {30, {-13, 5, 10, -1}},
    };

    long long target = H_MAX;
    vector<long long> moves;
    if (id < static_cast<int>(fixed.size())) {
        target = fixed[id].first;
        moves = fixed[id].second;
    } else if (id <= 11) {
        moves.assign(N_MAX, 0);
        if (id == 9) moves.back() = 1;
        if (id >= 10) {
            for (int i = 0; i < N_MAX; i += 2) {
                moves[i] = P_MAX - 1;
                moves[i + 1] = -(P_MAX - 1);
            }
            if (id == 11) moves.back() += 1;
        }
    } else {
        target = rnd.next(1, 80);
        moves.resize(rnd.next(2, 40));
        for (auto& move : moves) move = rnd.next(-20, 20);
    }
    println(target, moves.size());
    println(moves);
}
