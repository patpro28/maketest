#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1'000'000'007;

long long modpow(long long a, long long e = MOD - 2)
{
    long long r = 1;
    while (e)
    {
        if (e & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int idxOfChar(char c)
{
    if ('a' <= c && c <= 'z')
        return c - 'a';
    if ('A' <= c && c <= 'Z')
        return 26 + (c - 'A');
    return -1; // should not happen
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S;
    if (!(cin >> S))
        return 0;
    int N = (int)S.size();
    if (N % 2)
    { // theo đề N chẵn; nếu dữ liệu xấu, không có xâu đẹp nào
        int Q;
        if (!(cin >> Q))
            Q = 0;
        while (Q--)
        {
            int x, y;
            cin >> x >> y;
            cout << 0 << "\n";
        }
        return 0;
    }
    int M = N / 2;

    // Đếm tần suất theo 52 ký tự
    vector<int> freq(52, 0);
    for (char c : S)
    {
        int id = idxOfChar(c);
        if (id >= 0)
            freq[id]++;
    }
    // Lọc các loại có f>0 để giảm K
    vector<int> ids;
    ids.reserve(52);
    for (int i = 0; i < 52; i++)
        if (freq[i] > 0)
            ids.push_back(i);
    int K = (int)ids.size();

    // Giai thừa tới M và inv
    vector<long long> fact(M + 1, 1), invfact(M + 1, 1);
    for (int i = 1; i <= M; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[M] = modpow(fact[M]);
    for (int i = M; i > 0; i--)
        invfact[i - 1] = invfact[i] * i % MOD;

    // Hệ số COEF = (M!)^2 / prod f_c!
    long long coef = fact[M] * fact[M] % MOD;
    long long denom = 1;
    for (int id : ids)
    {
        int f = freq[id];
        // cần f! trong mẫu, nhưng f có thể > M (không sao, chỉ nhân f! rồi lấy nghịch đảo)
        // ta tính trực tiếp bằng nhân từ 1..f (tránh phải fact tới N)
        long long ff = 1;
        for (int t = 2; t <= f; t++)
            ff = ff * t % MOD;
        denom = denom * ff % MOD;
    }
    coef = coef * modpow(denom) % MOD;

    // g[k] = số tập ký tự có tổng tần suất = k (0/1 knapsack theo types)
    vector<int> g(M + 1, 0), ng(M + 1, 0);
    g[0] = 1;
    for (int id : ids)
    {
        int w = freq[id];
        for (int k = M; k >= w; k--)
        {
            g[k] += g[k - w];
            if (g[k] >= MOD)
                g[k] -= MOD;
        }
    }

    // dp_excl_one[t] từ g bằng "chia" cho (1 + x^{f_t})
    // Thay vì lưu tất cả, ta lưu vào một map<id, vector<int>> vì K<=52 vẫn ổn.
    unordered_map<int, vector<int>> exclOne;
    exclOne.reserve(K * 2);
    // Từ g, "bỏ" 1 loại có d=freq[id]: h = g / (1 + x^d)
    for (int id : ids)
    {
        int d = freq[id];
        vector<int> h(M + 1, 0);
        if (d == 0)
        {
            h = g;
            exclOne[id] = move(h);
            continue;
        }
        for (int r = 0; r < d; ++r)
        {
            // lớp dư r: h[r] = g[r]; h[r+d] = g[r+d] - h[r]; h[r+2d] = g[r+2d] - h[r+d]; ...
            for (int k = r; k <= M; k += d)
            {
                if (k == r)
                    h[k] = g[k];
                else
                {
                    int val = g[k] - h[k - d];
                    if (val < 0)
                        val += MOD;
                    h[k] = val;
                }
            }
        }
        exclOne[id] = move(h);
    }

    // Đọc Q và tất cả truy vấn. Ta gom theo cặp (type(a), type(b)) để tính trước 2 giá trị cần.
    int Q;
    cin >> Q;
    struct PairKey
    {
        int a, b;
        bool operator==(const PairKey &o) const { return a == o.a && b == o.b; }
    };
    struct PairHash
    {
        size_t operator()(const PairKey &k) const
        {
            return (size_t)k.a * 61u + (size_t)k.b;
        }
    };

    vector<pair<int, int>> queries;
    queries.reserve(Q);
    queries.clear();

    auto getTypeAt = [&](int pos) -> int
    {
        char c = S[pos - 1];
        return idxOfChar(c);
    };

    vector<int> qa(Q), qb(Q);
    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;
        qa[i] = getTypeAt(x);
        qb[i] = getTypeAt(y);
        queries.push_back({qa[i], qb[i]});
    }

    // Chuẩn hóa key (không có thứ tự vì công thức đối xứng), và chỉ tính cho các cặp xuất hiện.
    unordered_map<PairKey, pair<int, int>, PairHash> pairVals; // -> (V_M, V_Mminus)
    pairVals.reserve(min(Q, 1500));

    auto norm = [&](int a, int b)
    {
        if (a > b)
            swap(a, b);
        return PairKey{a, b};
    };

    // Tiền tính câu trả lời khi a==b: BEAUTY_ALL
    long long beautyAll = coef * g[M] % MOD;

    for (int i = 0; i < Q; i++)
    {
        int a = qa[i], b = qb[i];
        if (a == b)
            continue;
        PairKey key = norm(a, b);
        if (pairVals.find(key) != pairVals.end())
            continue;

        // cần g_{\{a,b\}} ở k = M và k2 = M - f_a - f_b
        int fa = freq[a], fb = freq[b];

        // h = g\{a}
        const vector<int> &h = exclOne[a];

        // Từ h chia cho (1 + x^{fb}) bằng tổng luân phiên theo lớp dư mod fb.
        // Tính "online": duyệt mọi k theo từng r, bắt được đúng hai k cần nếu thuộc cùng lớp.
        auto grabVal = [&](int K, int d, const vector<int> &h) -> int
        {
            if (K < 0 || K > M)
                return 0;
            if (d == 0)
                return h[K]; // phòng thủ, thực tế d>=1
            int r = K % d;
            int z = 0;
            for (int k = r; k <= K; k += d)
            {
                if (k == r)
                    z = h[k];
                else
                {
                    z = h[k] - z;
                    if (z < 0)
                        z += MOD;
                }
            }
            return z;
        };

        int V1 = grabVal(M, fb, h);
        int V2 = (M - fa - fb >= 0) ? grabVal(M - fa - fb, fb, h) : 0;

        pairVals.emplace(key, make_pair(V1, V2));
    }

    // Trả lời
    for (int i = 0; i < Q; i++)
    {
        int a = qa[i], b = qb[i];
        if (a == b)
        {
            cout << beautyAll << "\n";
        }
        else
        {
            PairKey key = norm(a, b);
            auto it = pairVals.find(key);
            int fa = freq[a], fb = freq[b];
            long long term1 = it->second.first;                           // g_{-\{a,b\}}[M]
            long long term2 = (M - fa - fb >= 0) ? it->second.second : 0; // g_{-\{a,b\}}[M-fa-fb]
            long long ways = (term1 + term2) % MOD;
            long long ans = coef * ways % MOD;
            cout << ans << "\n";
        }
    }
    return 0;
}