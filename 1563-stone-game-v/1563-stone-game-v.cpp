class Solution {
public:
    int solve(int start, int end, vector<int>& arr, vector<vector<int>>&dp){
        if(start>=end) return 0;
        // first we will be calulating the total sum
        int l=0;
        int r=0;

        if(dp[start][end]!=-1) return dp[start][end];
        for(int i=start;i<=end;i++){
            r+=arr[i];
        }
        int ans=0;
        for(int i=start ; i<end; i++ ){
            l+=arr[i];
            r-=arr[i];
            // now three condition will be there when l<r l==r and l>R
            if(l<r) ans=max(ans , l+solve(start, i, arr,dp));
            if(l==r) ans=max(ans, max(l+solve(start, i, arr, dp) , r+solve(i+1, end,arr, dp)));
            if(l>r) ans=max(ans, r+solve(i+1,end, arr, dp));
        }
        return dp[start][end]=ans;
    }

    int stoneGameV(vector<int>& stoneValue) {
        vector<vector<int>> dp(stoneValue.size(), vector<int>(stoneValue.size(), -1));
        return solve(0, stoneValue.size()-1, stoneValue, dp);
        
    }
};