const int N = 2e5 + 5;
int T[N][msb(N) + 3];
vector<int>arr(N);
int n;
int merge(int a,int b){
    return max(a,b);
}
void build(){
    for(int pw = 0;1 <<pw <= n;pw++){
        for(int i = 0;i + (1 << pw)<=n;i++){
            if(pw == 0)
                T[i][0] = arr[i];
            else
                T[i][pw] = merge(T[i][pw-1],T[i +(1 << (pw-1))][pw-1]);
        }
    }
}
int query(int l,int r){
    int sz = r-l+1;
    int ret = 0;
    while (sz) {
        ret = merge(ret, T[l][msb(sz)]);
        l += 1 << msb(sz);
        sz &= ~(1 << msb(sz));
    }
    return ret;
}
int query2(int l,int r){
    int sz = r-l+1;
    return merge(T[l][msb(sz)],T[r - (1 << msb(sz))+1][msb(sz)]);
}