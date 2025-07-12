const int N = 200005;
vector<pair<int,int>>adj[N];
int n,m;
void dijkstra(){
    int dis[n+1];
    memset(dis,'?',sizeof dis);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,1});
    while (pq.size()){
        auto [c,u] = pq.top();
        pq.pop();
        if(dis[u] <= c)continue;
        dis[u] = c;
        for(auto [v,nc] : adj[u]){
            pq.push({nc+c,v});
        }
    }
    for(int i =1;i<=n;i++){
        cout << dis[i] << " ";
    }
}