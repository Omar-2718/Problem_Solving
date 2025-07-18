int adj[101][101];
vector<vector<int>>dis;
int n;
void floyd(){
    dis.assign(n+1,vector<int>(n+1,inf));
    for(int i =1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dis[i][j] = adj[i][j];
        }
    }
    for(int k=1;k<=n;k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis[i][k] == inf or dis[k][j] == inf)continue;
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

            }
        }
    }
}
int ans = 0;
void clean(){
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dis[i][j] == inf or i == j)continue;
            bool can = true;
            for(int k=1;k<=n;k++){
                if(k == i or k == j)continue;
                if(dis[i][k] + dis[k][j] <= adj[i][j]){
                    can = false;
                    break;
                }
            }
            ans += !can;

        }
    }
}
bool coherent(){
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(dis[i][j] < adj[i][j])return false;
        }
    }
    return true;
}