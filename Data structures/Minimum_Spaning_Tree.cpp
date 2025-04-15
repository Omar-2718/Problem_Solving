#include <bits/stdc++.h>
using namespace std;
class DSU{
public:
    vector<int>par,sz;
    void init(int n){
        par.assign(n+1,0);
        sz.assign(n+1,1);
        for(int i =1;i<=n;i++){
            par[i] = i;
        }
    }
    int find(int u){
        if(par[u] == u)return u;
        return par[u] = find(par[u]);
    }
    bool merge(int u,int v){
        u = find(u),v= find(v);
        if(u == v){
            return false;
        }
        if(sz[u] > sz[v])swap(u,v);
        par[u] = v;
        sz[u] += sz[v];
        return true;
    }
};
vector<array<int,3>>edge_list(100009);
void solve(){
    int n,m;cin>>n>>m;
    for(int i =0;i<m;i++){
        cin >> edge_list[i][1] >> edge_list[i][2] >> edge_list[i][0];
    }
    std::sort(edge_list.begin(), edge_list.begin()+n);
    DSU ds;ds.init(n);
    int ans = 0;
    for(int i =0;i<m;i++){
        auto [w,u,v] = edge_list[i];
        if(ds.merge(u,v)){
            ans += w;
        }
    }
    cout << ans << '\n';
}