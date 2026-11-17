class Solution {
    int memo[201][101];
    int cost[201][201];   
    int tmp[201][201];
    static const int INF = 10000;

    int solve(int idx, int k, int n) {
        if (idx == n || k == 0) return (idx == n && k == 0) ? 0 : INF;
        int &res = memo[idx][k];
        if (res != -1) return res;
        res = INF;
        for (int len = 2; idx + len <= n; ++len)
            res = min(res, cost[idx][len] + solve(idx + len, k - 1, n));
        return res;
    }

public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        memset(memo, -1, sizeof(memo));
        memset(cost, 0x3f, sizeof(cost));

        for (int d = 1; d <= n / 2; d++) {
            memset(tmp, 0, sizeof(tmp));
            for (int len = 2 * d; len <= n; len += d)
                for (int idx = 0; idx + len <= n; idx++) {
                    int ops = 0;
                    for (int o = 0; o < d; o++)
                        ops += s[idx + o] != s[idx + len - d + o];
                    tmp[idx][len] = ops + tmp[idx + d][len - 2 * d];
                    cost[idx][len] = min(cost[idx][len], tmp[idx][len]);
                }
        }
        return solve(0, k, n);
    }
};
