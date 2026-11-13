class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        deque<int> starts;  
        long long ans = 0, water = 0;
        int n = nums.size(), r = n - 1;
        for (int l = n - 1; l >= 0; --l) {
            int x = nums[l];
            while (!starts.empty() && nums[starts.front()] <= x) { 
                int s = starts.front();
                starts.pop_front();
                int end = starts.empty() ? r + 1 : starts.front();
                water += 1LL * (x - nums[s]) * (end - s);
            }
            starts.push_front(l);
            while (water > k) {  
                water -= nums[starts.back()] - nums[r];
                if (starts.back() == r)
                    starts.pop_back();
                --r;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};