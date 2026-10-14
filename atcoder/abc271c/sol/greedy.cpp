#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());
    auto end = unique(a.begin(), a.end());
    int spare = a.end() - end;
    deque<int> books(a.begin(), end);
    int next = 1;
    while (true) {
        if (!books.empty() && books.front() == next) {
            books.pop_front();
            ++next;
            continue;
        }
        while (spare < 2 && !books.empty()) {
            books.pop_back();
            ++spare;
        }
        if (spare < 2) break;
        spare -= 2;
        ++next;
    }
    cout << next - 1 << '\n';
}
