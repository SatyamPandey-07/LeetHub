class Solution {
    #define ll long long
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> a(n);
        for(auto &i : edges) {
            a[i[0]].push_back({i[1], i[2]});
        }

        vector<vector<ll>> dp(n, vector<ll>(k+1, LLONG_MAX));
        priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<tuple<ll, ll, ll>>> pq;
        
        pq.push({0, 0, 1});
        dp[0][1] = 0;

        while(!pq.empty()) {
            auto [d, u, c] = pq.top();
            pq.pop();
            if(d != dp[u][c]) continue;
            if(u == n-1) return d;
            for(auto &[v, w] : a[u]) {
                int cc = 0;
                if(labels[u] == labels[v]) cc = c + 1;
                else cc = 1;
                if(cc > k) continue;
                if(dp[v][cc] > d + w) {
                    dp[v][cc] = d + w;
                    pq.push({dp[v][cc], v, cc});
                }
            }
        }

        return -1;
    }
};