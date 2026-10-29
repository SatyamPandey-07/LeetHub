class Solution {
    int n, LOG = 17, timer = 0;
    vector<vector<int>> g, up;
    vector<int> tin, tout, dep, bit;
    string s;

    int sum(int i) {
        int x = 0;
        for (; i; i -= i & -i) x ^= bit[i];
        return x;
    }

    void update(int u, int x) {
        for (int i : {tin[u], tout[u] + 1})
            for (; i <= n; i += i & -i) bit[i] ^= x;
    }

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[0][u] = p;

        for (int j = 1; j < LOG; j++)
            up[j][u] = up[j-1][up[j-1][u]];

        for (int v : g[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
        tout[u] = timer;
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);

        for (int j = LOG-1; j >= 0; j--)
            if (dep[u] - (1 << j) >= dep[v])
                u = up[j][u];

        if (u == v) return u;

        for (int j = LOG-1; j >= 0; j--)
            if (up[j][u] != up[j][v])
                u = up[j][u], v = up[j][v];

        return up[0][u];
    }

public:
    vector<bool> palindromePath(int N, vector<vector<int>>& edges,
                                string S, vector<string>& queries) {
        n = N;
        s = S;
        g.assign(n, {});

        for (auto& e : edges)
            g[e[0]].push_back(e[1]), g[e[1]].push_back(e[0]);

        tin.resize(n);
        tout.resize(n);
        dep.assign(n, 0);
        up.assign(LOG, vector<int>(n));
        bit.assign(n + 2, 0);

        dfs(0, 0);

        for (int u = 0; u < n; u++)
            update(u, 1 << (s[u] - 'a'));

        vector<bool> ans;

        for (auto& q : queries) {
            string op;
            int u, v;
            char c;
            stringstream ss(q);
            ss >> op >> u;

            if (op == "update") {
                ss >> c;
                update(u, (1 << (s[u]-'a')) ^ (1 << (c-'a')));
                s[u] = c;
            } else {
                ss >> v;
                int w = lca(u, v);
                int mask = sum(tin[u]) ^ sum(tin[v]) ^
                           (1 << (s[w]-'a'));
                ans.push_back((mask & (mask-1)) == 0);
            }
        }
        return ans;
    }
};