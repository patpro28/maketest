#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
int main(int, char* argv[]) {
    int seed = atoi(argv[1]);
    vector<pair<int,int>> a;
    int s;
    switch(seed) {
        case 0: a={{1,100}}; s=1; break;
        case 1: a={{1,100}}; s=100; break;
        case 2: a={{1,100}}; s=50; break;
        case 3: a={{100,100}}; s=10000; break;
        case 4: a={{1,1}}; s=1; break;
        case 5: a={{1,1}}; s=2; break;
        case 6: a={{2,3},{4,5}}; s=7; break;
        case 7: a={{2,3},{4,5}}; s=2; break;
        case 8: a={{2,3},{4,5}}; s=9; break;
        case 9: a={{1,3},{1,3},{1,3}}; s=4; break;
        case 10: a={{1,100},{100,1},{1,100},{100,1}}; s=4; break;
        case 11: a={{1,100},{100,1},{1,100},{100,1}}; s=400; break;
        case 12: a={{5,5},{5,5},{5,5}}; s=15; break;
        case 13: a={{5,5},{5,5},{5,5}}; s=14; break;
        case 14: a={{1,2},{4,8},{16,32},{64,100}}; s=85; break;
        default: a={{1,2},{4,8},{16,32},{64,100}}; s=142;
    }
    cout << a.size() << ' ' << s << '\n';
    for (auto [x,y] : a) cout << x << ' ' << y << '\n';
}
