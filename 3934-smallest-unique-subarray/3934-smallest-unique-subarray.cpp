#define ll long long int
class Solution {
    ll mod = 1e9+7;
    ll hash(vector<int> &v,int i,int j,int base){
        ll p = 1;
        ll ret = 0;
        for(int x=i;x<=j;x++){
            ret = (ret + (v[x]*p)%mod)%mod;
            p = (p*base)%mod;
        }
        return ret;
    }
    ll binpow(ll a,ll b){
        ll ret = 1;
        a %= mod;
        while(b>0){
            if(b&1){
                ret = ret*a%mod;
            }
            a = a*a%mod;
            b/=2;
        }
        return ret;
    }
    bool check(vector<int> &v,ll m){
        unordered_map<ll,ll> mp;
        ll base = 13;
        ll x = hash(v,0,m-1,base);
        ll p = binpow(base,m-1)%mod;
        ll inv = binpow(base,mod-2)%mod;

        mp[x]++;

        for(int i=0,j=m;j<v.size();i++,j++){
            x = x - v[i];
            x = (x*inv)%mod;
            x = (x + (v[j]*p)%mod)%mod;
            mp[x]++;
        }

        for(auto x:mp){
            if(x.second==1) return false;
        }
        return true;
    }

public:
    int smallestUniqueSubarray(vector<int>& v) {
        int n = v.size();
        int s=1,e=n;
        int ret = n;
        while(s<e){
            int m = s+(e-s)/2;
            if(check(v,m)){
                s = m+1;
            }else{
                e = m;
                ret = min(ret,m);
            }
        }
        return ret;
    }
};