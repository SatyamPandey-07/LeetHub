class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n = nums.size(), answer = -1;

        for (int i = 0; i < n; i++) {
            if (nums[i] != i) {
                answer &= nums[i];
            }
        }

        return answer == -1 ? 0 : answer;
    }
};