class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n + 1, 0), nxt(n + 1, n);
        for (int i = 0; i + 1 < n; i++)
            pre[i + 1] = pre[i] + (nums[i] > nums[i + 1] ? 1 : 0);
        for (int i = n - 2; i >= 0; i--)
            nxt[i] = nums[i] > nums[i + 1] ? i : nxt[i + 1];
        int ans = 0;
        for (int k = 1; k <= n; k++) {
            if (n % k)
                continue;
            int prev = 0;
            bool ok = true;
            for (int s = 0; s < n; s += k) {
                int e = s + k - 1;
                int c = pre[e] - pre[s];
                int mn, mx;
                if (c > 1) {
                    ok = false;
                    break;
                }
                if (c == 1) {
                    if (nums[e] > nums[s]) {
                        ok = false;
                        break;
                    }
                    int j = nxt[s];
                    mn = nums[j + 1];
                    mx = nums[j];
                } else {
                    mn = nums[s];
                    mx = nums[e];
                }
                if (mn < prev) {
                    ok = false;
                    break;
                }
                prev = mx;
            }
            if (ok)
                ans += k;
        }
        return ans;
    }
};