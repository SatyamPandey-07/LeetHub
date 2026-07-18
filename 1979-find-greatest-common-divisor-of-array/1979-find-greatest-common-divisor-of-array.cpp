class Solution {
public:
    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    int findGCD(vector<int>& nums) {
        int mn = nums[0], mx = nums[0];

        for (const auto &x : nums) {
            mn = min(mn, x);
            mx = max(mx, x);
        }

        return gcd(mx, mn);
    }
};