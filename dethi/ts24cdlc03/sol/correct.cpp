/*
Author: Tu Pham Anh
Date: 2025/04/13 - 21:50
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

string s, p;
int n;
set<int, greater<int>> S{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int main()
{
    cin >> p >> s;
    n = p.size();
    for (char c : s)
        S.erase(c - '0');
    string x = p;
    bool equal = true;
    for (int i = 0; i < n; ++i)
        for (int d : S) // Duyệt các chữ số được dùng từ lớn đến nhỏ
        {
            // Nếu X đang bằng P thì xi <= pi
            if (equal and d <= p[i] - '0')
            {
                x[i] = d + '0';
                equal = equal && (d == p[i] - '0');
                break; // Chọn d làm chữ số thứ i của X
            }
            // Nếu X đang nhỏ hơn P
            if (!equal)
            {
                x[i] = d + '0';
                break;
            }
        }
    int i = 0;
    while (i < n && x[i] == '0') i++;
    if (i == n)
        cout << -1;
    else
        cout << x.substr(i);
    return 0;
}