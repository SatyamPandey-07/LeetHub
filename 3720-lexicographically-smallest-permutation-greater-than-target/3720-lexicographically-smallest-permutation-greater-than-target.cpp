class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        // prefix = part that currently matches target
        string prefix;

        for (int i = 0; i < n; i++) {

            int x = target[i] - 'a';

            // If target[i] is unavailable,
            // we cannot continue matching.
            if (cnt[x] == 0) {
                break;
            }

            cnt[x]--;
            prefix += target[i];
        }

        // If we stopped before matching the whole target (because the
        // needed character ran out), first try placing a character
        // strictly greater than target[i] right at that same position,
        // using whatever counts are left (nothing was consumed here yet).
        if ((int)prefix.size() < n) {
            int i = prefix.size();
            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] == 0)
                    continue;

                string ans = prefix;
                ans += char('a' + c);

                cnt[c]--;

                for (int ch = 0; ch < 26; ch++) {
                    ans.append(cnt[ch], char('a' + ch));
                }

                return ans;
            }
        }

        // Otherwise (or if that attempt failed), backtrack through the
        // matched prefix from right to left.
        for (int i = prefix.size() - 1; i >= 0; i--) {

            // Restore the character at position i.
            cnt[prefix[i] - 'a']++;

            prefix.pop_back();

            int x = target[i] - 'a';

            // Find smallest character > target[i].
            for (int c = x + 1; c < 26; c++) {

                if (cnt[c] == 0)
                    continue;

                string ans = prefix;
                ans += char('a' + c);

                cnt[c]--;

                // Fill remaining characters in sorted order.
                for (int ch = 0; ch < 26; ch++) {
                    ans.append(cnt[ch], char('a' + ch));
                }

                return ans;
            }
        }

        return "";
    }
};