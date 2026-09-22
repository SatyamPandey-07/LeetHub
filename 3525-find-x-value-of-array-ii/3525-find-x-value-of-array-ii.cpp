class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();

        int size = 1;
        while (size < n) {
            size <<= 1;
        }

        vector<long long> H(2 * size * k, 0);
        vector<int> prod(2 * size, 1 % k);

        for (int i = 0; i < n; i++) {
            int v = nums[i] % k;
            int nd = size + i;

            H[nd * k + v] = 1;
            prod[nd] = v;
        }

        for (int i = size - 1; i >= 1; i--) {
            int lc = 2 * i;
            int rc = lc + 1;
            int lp = prod[lc];

            int bi = i * k;
            int bl = lc * k;
            int br = rc * k;

            for (int q = 0; q < k; q++) {
                H[bi + q] = H[bl + q];
            }

            for (int q = 0; q < k; q++) {
                long long c = H[br + q];

                if (c) {
                    H[bi + (lp * q) % k] += c;
                }
            }

            prod[i] = lp * prod[rc] % k;
        }

        vector<int> ans;

        for (auto& query : queries) {
            int idx = query[0];
            int val = query[1];
            int start = query[2];
            int x = query[3];

            int nd = size + idx;
            int base = nd * k;

            for (int q = 0; q < k; q++) {
                H[base + q] = 0;
            }

            int v = val % k;

            H[base + v] = 1;
            prod[nd] = v;

            int cur = nd >> 1;

            while (cur) {
                int lc = 2 * cur;
                int rc = lc + 1;
                int lp = prod[lc];

                int bi = cur * k;
                int bl = lc * k;
                int br = rc * k;

                for (int q = 0; q < k; q++) {
                    H[bi + q] = H[bl + q];
                }

                for (int q = 0; q < k; q++) {
                    long long c = H[br + q];

                    if (c) {
                        H[bi + (lp * q) % k] += c;
                    }
                }

                prod[cur] = lp * prod[rc] % k;
                cur >>= 1;
            }

            int l = start + size;
            int r = n + size;

            vector<int> ln;
            vector<int> rn;

            while (l < r) {
                if (l & 1) {
                    ln.push_back(l);
                    l++;
                }

                if (r & 1) {
                    r--;
                    rn.push_back(r);
                }

                l >>= 1;
                r >>= 1;
            }

            reverse(rn.begin(), rn.end());

            vector<long long> res(k, 0);
            int p = 1 % k;

            for (int node : ln) {
                int b = node * k;

                for (int q = 0; q < k; q++) {
                    long long c = H[b + q];

                    if (c) {
                        res[(p * q) % k] += c;
                    }
                }

                p = p * prod[node] % k;
            }

            for (int node : rn) {
                int b = node * k;

                for (int q = 0; q < k; q++) {
                    long long c = H[b + q];

                    if (c) {
                        res[(p * q) % k] += c;
                    }
                }

                p = p * prod[node] % k;
            }

            ans.push_back((int)res[x]);
        }

        return ans;
    }
};