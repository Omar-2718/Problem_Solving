class DSU{
public:
    vector<int>par,sz;
    int comp;
    void init(int n){
        comp = n;
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
        comp--;
        if(sz[u] > sz[v])swap(u,v);
        par[u] = v;
        sz[v] += sz[u];
        return true;
    }
};
int n,m;
pair<vector<int>,int> mst(vector<array<int,3>>&edge_list){
    std::sort(edge_list.begin(), edge_list.end());
    DSU ds;ds.init(n);
    int ans = 0;
    vector<int>remain;
    for(int i =0;i<edge_list.size();i++){
        auto [w,u,v] = edge_list[i];
        if(ds.merge(u,v)){
            remain.push_back(i);
            ans += w;
        }
    }
    if(ds.comp != 1)return {{},inf};
    return {remain,ans};
}