#include <bits/stdc++.h>
#define msb(x) (63 - __builtin_clzll(x))
#define lsb(x) (__builtin_ctzll(x))
#define bit_count(x) (__builtin_popcountll(x))
#define int long long

using namespace std;
const int N = 2e5 + 9, LG = 18, inf = 1e9 + 9;
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

struct node {
    // set variables of nodes here
    int sum =-inf;
    node() {
    }

    void change(int _val) {
        sum = _val;
    }
};

class seg_tree {
public:
    int sz;
    vector<node> arr_nodes;

    seg_tree(int _sz) {
        sz = 1 << (msb(_sz) + 1);
        arr_nodes.assign(2 * sz, {});
    }

    node merge(node lft, node rt) {
        node ans;
        // merge here
        ans.sum = max(lft.sum,rt.sum);
        return ans;
    }

    node get(int tl, int tr, int l, int r, int ni) {

        if (tl >= r or tr <= l) {
            return {};
        }
        if (tl <= l and tr >= r) {
            return arr_nodes[ni];
        }

        int mid = (r + l) / 2;
        return merge(get(tl, tr, l, mid, 2 * ni + 1),
                     get(tl, tr, mid, r, 2 * ni + 2));
    }

    void set(int idx, int val, int l, int r, int ni) {
        int mid = (r + l) / 2;
        if (idx < l or idx >= r)return;
        if (l == r - 1) {
            arr_nodes[ni].change(val);
            return;
        }
        set(idx, val, l, mid, 2 * ni + 1);
        set(idx, val, mid, r, 2 * ni + 2);
        arr_nodes[ni] = merge(arr_nodes[2 * ni + 1], arr_nodes[2 * ni + 2]);
    }

    node get(int tl, int tr) {
        return get(tl, tr, 0, sz, 0);
    }

    void set(int idx, int val) {
        set(idx, val, 0, sz, 0);
    }

    void init(vector<int> &arr, int l, int r, int ni) {
        if (l >= arr.size())return;
        int mid = (r + l) / 2;
        if (l == r - 1) {
            arr_nodes[ni].change(arr[l]);
            return;
        }
        init(arr, l, mid, 2 * ni + 1);
        init(arr, mid, r, 2 * ni + 2);
        arr_nodes[ni] = merge(arr_nodes[2 * ni + 1], arr_nodes[2 * ni + 2]);
    }

    void init(vector<int> &arr) {
        init(arr, 0, sz, 0);
    }
};
seg_tree t(N+2);
vector<int> g[N+2];
int par[N+1][LG + 1], dep[N+1], sz[N+1];
void dfs(int u, int p = 0) {
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    sz[u] = 1;
    for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
    if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
    for (auto &v : g[u]) if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
            if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
    if (u == v) return u;
    for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
    return par[u][0];
}
int kth(int u, int k) {
    assert(k >= 0);
    for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
    return u;
}
int T, head[N], st[N], en[N];
void dfs_hld(int u) {
    st[u] = ++T;
    for (auto v : g[u]) {
        head[v] = (v == g[u][0] ? head[u] : v);
        dfs_hld(v);
    }
    en[u] = T;
}
int query_up(int u, int v) {
    // change this
    int ans = -inf;
    while(head[u] != head[v]) {
        // change max to +
        ans = max(ans, t.get(st[head[u]], st[u]+1).sum);
        u = par[head[u]][0];
    }
    // change max to +
    ans = max(ans, t.get( st[v], st[u]+1).sum);
    return ans;
}
// to update set the seg tree with st[u]
int query(int u, int v) {
    int l = lca(u, v);
    int ans = query_up(u, l);
    // change max to +
    if (v != l) ans = max(ans, query_up(v, kth(v, dep[v] - dep[l] - 1)));
    return ans;
}
// add these in main
//   dfs(1);
//  head[1] = 1;
//  dfs_hld(1);
// Dont forget to set T = 0 for each tc
int n,m;
vector<int>val(N+1);
void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> val[i];
    }
    vector<int>arr(n+1);
    for(int i =1;i<=n-1;i++){
        int u,v;cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    head[1] = 1;
    dfs_hld(1);
    for(int i=1;i<=n;i++){
        arr[st[i]] = val[i];
    }
    t.init(arr);

    while (m--){
        int tp;cin>>tp;
        if(tp == 1){
            int s,x;cin>>s>>x;
            t.set(st[s],x);
        }
        else{
            int a,b;cin>>a>>b;
            cout << query(a,b) << " ";
        }
    }
}
