class Solution {
public:
    string reverseWords(string s) {
        string ans = "";
        vector<string> toRev;
        istringstream is(s);
        while(is){
            string n;
            is >> n;
            toRev.push_back(n);
        }
        int m = toRev.size();
        ans += toRev[m-2];
        for(int i = m - 3; i >= 0; i--){
            ans += " " + toRev[i];
        }
        return ans;
    }
};