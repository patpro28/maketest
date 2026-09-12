#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;
int H, W;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> W;
    vector<vector<int>> A(H, vector<int>(W));
    unordered_map<int, vector<pair<int,int>>> mp;
    mp.reserve(H * W * 2);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> A[i][j];
            mp[A[i][j]].push_back({i, j});
        }
    }

    int ans = INF;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    // Mỗi giá trị xử lý một lần
    for (auto &entry : mp) {
        auto &cells = entry.second;
        int k = cells.size();
        if (k <= 1) continue;

        // Case 1: freq <= 400 -> brute force
        if (k <= 500) {
            for (int i = 0; i < k; i++) {
                for (int j = i + 1; j < k; j++) {
                    int d = abs(cells[i].first - cells[j].first)
                          + abs(cells[i].second - cells[j].second);
                    ans = min(ans, d);
                }
            }
            continue;
        }

        // Case 2: freq > 400 -> multi-source BFS
        // dist = khoảng cách BFS
        // owner = nguồn BFS ban đầu nào
        static int dist[501][501];
        static int owner[501][501];

        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                dist[i][j] = -1, owner[i][j] = -1;

        queue<pair<int,int>> q;
        int id = 0;

        for (auto &p : cells) {
            int x = p.first, y = p.second;
            dist[x][y] = 0;
            owner[x][y] = id++;
            q.push({x, y});
        }

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();

            for (auto &d : dirs) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 0 || ny < 0 || nx >= H || ny >= W) continue;

                if (dist[nx][ny] == -1) {
                    // chưa được BFS tới lần nào
                    dist[nx][ny] = dist[x][y] + 1;
                    owner[nx][ny] = owner[x][y];
                    q.push({nx, ny});
                } else if (owner[nx][ny] != owner[x][y]) {
                    // hai BFS từ hai điểm khác nhau gặp nhau
                    int d_total = dist[nx][ny] + dist[x][y] + 1;
                    ans = min(ans, d_total);
                }
            }
        }
    }

    if (ans == INF) ans = -1;
    cout << ans << "\n";
    return 0;
}
