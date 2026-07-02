class Solution {
public:
    int countBinarySubstrings(string& s) {
        const int n=s.size();
        int prev=0, cur=1, cnt=0;
        for(int i=1; i<n; i++){
            bool same=s[i]==s[i-1];
            prev=(-same & prev)+(-!same & cur);
            //cur=(-same & (cur+1))+(-!same & 1);
            cur=1+(-same & cur );
            cnt+=cur<=prev;
        }
        return cnt;
    }
};