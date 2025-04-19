#include <bits/stdc++.h>
using namespace std;

int a[100009];
int n, k;

int main()
{
    cin >> n >> k;
    k = k - 1; 
    
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    
    deque<int> dq;
    
    for (int i = 1; i <= n; i++)
    {
        if (!dq.empty() && dq.front() < i - k)
        {
            dq.pop_front();
        }
        
        while (!dq.empty() && a[dq.back()] >= a[i])
        {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k + 1)
        {
            cout << a[dq.front()] << endl;
        }
    }
    
    return 0;
}