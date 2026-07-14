class Solution {
public:
    static const int MOD = 1e9 + 7;

    int subsequencePairCount(vector<int>& nums) {

        vector<vector<int>> cur(201, vector<int>(201, 0));
        vector<vector<int>> nxt(201, vector<int>(201, 0));

        cur[0][0] = 1;

        for (int x : nums) {

            for (int i = 0; i <= 200; i++)
                fill(nxt[i].begin(), nxt[i].end(), 0);

            for (int g1 = 0; g1 <= 200; g1++) {
                for (int g2 = 0; g2 <= 200; g2++) {

                    if (cur[g1][g2] == 0) continue;

                    long long ways = cur[g1][g2];

        
                    nxt[g1][g2] = (nxt[g1][g2] + ways) % MOD;

          
                    int ng1 = (g1 == 0 ? x : gcd(g1, x));
                    nxt[ng1][g2] = (nxt[ng1][g2] + ways) % MOD;

                    int ng2 = (g2 == 0 ? x : gcd(g2, x));
                    nxt[g1][ng2] = (nxt[g1][ng2] + ways) % MOD;
                }
            }

            swap(cur, nxt);
        }

        long long ans = 0;

        for (int g = 1; g <= 200; g++)
            ans = (ans + cur[g][g]) % MOD;

        return ans;
    }
};