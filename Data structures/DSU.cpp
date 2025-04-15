class DSU{
public:
    vector<int>par;
    vector<set<int>>st;
    void init(int n){
        par.assign(n+1,0);
        st.assign(n+1,{});
        for(int i =1;i<=n;i++){
            st[i].insert(i);
            par[i] = i;
        }
    }
    int find(int u){
        if(u == par[u])return u;
        return par[u] = find(par[u]);
    }
    bool merge(int u,int v){
        u = find(u),v=find(v);
        if(u == v)return false;
        if(st[u].size() > st[v].size())swap(u,v);
        for(auto e : st[u]){
            st[v].insert(e);
        }
        par[u] = v;
        return true;
    }
};