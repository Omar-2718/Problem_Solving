#include <bits/stdc++.h>
#define msb(x) (63 - __builtin_clzll(x))
#define lsb(x) (__builtin_ctzll(x))
#define bit_count(x) (__builtin_popcountll(x))
#define int long long
using namespace std;
const int N = 1e5+2,inf = 1e9 + 9;
const int MOD = 1e9+7;
void fileIO() {
#ifndef ONLINE_JUDGE
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif
}

void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}


vector<int>col(200009);
vector<pair<int,int>>adj[200009];
vector<pair<int,int>>hv_adj[200009];
map<int,int>nod_col_sm[200009];
bool heavy[200009];
int tot =0;
int sq = 2;
void update_light(int u,int c){
    if(col[u] == c)return;
    int og = col[u];
    col[u] = c;
    for(auto e : adj[u]){
        auto [v,w] = e;
        if(heavy[v]){
            nod_col_sm[v][og] -= w;
            nod_col_sm[v][c] += w;
        }
        if(og == col[v]){
            tot -= w;
        }
        if(col[u] == col[v])
            tot += w;

    }
}
void update_heavy(int u,int c){
    if(col[u] == c)return;
    int og = col[u];
    col[u] = c;
    tot -= nod_col_sm[u][og];
    tot += nod_col_sm[u][c];
    for(auto e : hv_adj[u]){
        auto [v,w] = e;
        nod_col_sm[v][og] -= w;
        nod_col_sm[v][c] += w;
    }
}
int n,q;
void solve(){
    int sm =0;
    tot =0;
    cin >> n >> q;
    sq = sqrt(n+0.1)+1;
    for(int i =1;i<=n;i++){
        cin >> col[i];
        adj[i].clear();
        hv_adj[i].clear();
        nod_col_sm[i].clear();
        heavy[i] = 0;
    }
    for(int i=0;i<n-1;i++){
        int a,b,c;
        cin>>a>>b>>c;
        sm += c;
        if(col[a] == col[b])tot +=c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    for(int i=1;i<=n;i++){
        if(adj[i].size() < sq)continue;
        heavy[i] = 1;
        for(auto u : adj[i]){
            auto [v,c] = u;
            if(adj[v].size() < sq)continue;
            hv_adj[i].push_back({v,c});
        }
    }
    for(int i=1;i<=n;i++){
        for(auto e : adj[i]){
            auto [v,w] = e;
            nod_col_sm[v][col[i]] += w;
        }
    }
    while (q--){
        int u,c;cin>>u>>c;
        if(heavy[u]){
            update_heavy(u,c);
        }
        else{
            update_light(u,c);
        }
        cout << sm - tot << "\n";
    }
}

signed main() {
    fileIO();
    fastIO();
    int tc=1;
    cin>>tc;
    while (tc--)
        solve();
    return 0;
}