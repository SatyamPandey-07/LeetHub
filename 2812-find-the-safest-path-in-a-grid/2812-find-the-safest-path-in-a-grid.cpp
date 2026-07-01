class Solution {
public:

    typedef pair<int,pair<int,int>> ppi;
    int dx[4]={0,0,1,-1};
    int dy[4]={1,-1,0,0};
    int maximumSafenessFactor(vector<vector<int>>&grid) {
        int m=grid.size();
        int n=grid[0].size();
        queue<pair<int,int>>q;
        vector<vector<int>>dist(m,vector<int>(n,-1));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    q.push({i,j});
                    dist[i][j]=0;
                }
            }
        }
        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            for(int k=0;k<4;k++){
                int ni=i+dx[k];
                int nj=j+dy[k];
                if(ni>=0 && ni<m &&
                   nj>=0 && nj<n &&
                   dist[ni][nj]==-1){
                    dist[ni][nj]=dist[i][j]+1;
                    q.push({ni,nj});
                }
            }
        }
        priority_queue<ppi>pq;
        vector<vector<int>>vis(m,vector<int>(n,0));
        pq.push({dist[0][0],{0,0}});
        while(!pq.empty()){
            auto cur=pq.top();
            pq.pop();
            int safe=cur.first;
            int i=cur.second.first;
            int j=cur.second.second;
            if(vis[i][j]) continue;
            vis[i][j]=1;
            if(i==m-1 && j==n-1){
                return safe;
            }
            for(int k=0;k<4;k++){
                int ni=i+dx[k];
                int nj=j+dy[k];
                if(ni>=0 && ni<m &&
                   nj>=0 && nj<n &&
                   !vis[ni][nj]){
                    int nsafe=min(safe,dist[ni][nj]);
                    pq.push({nsafe,{ni,nj}});
                }
            }
        }
        return -1;
    }
};