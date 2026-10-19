class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int left = ranges::count_if(nums, [&](int x) { return x < target; });  // bisect_left: 
        int right = ranges::count_if(nums, [&](int x) { return x <= target; });  // 
        vector<int> indices(right - left);
        iota(indices.begin(), indices.end(), left);
        return indices;
    }
};