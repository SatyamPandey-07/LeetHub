class Solution {
public:
    int longestValidParentheses(string s) {
        int open = 0, close = 0;
        int ans = 0;

        // Left → Right
        for (char c : s) {
            if (c == '(')
                open++;
            else
                close++;

            if (open == close)
                ans = max(ans, 2 * close);

            if (close > open)
                open = close = 0;
        }

        open = close = 0;

        // Right → Left
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '(')
                open++;
            else
                close++;

            if (open == close)
                ans = max(ans, 2 * open);

            if (open > close)
                open = close = 0;
        }

        return ans;
    }
};