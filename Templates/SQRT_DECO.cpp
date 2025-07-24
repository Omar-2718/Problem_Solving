#include <bits/stdc++.h>
#define msb(x) (63 - __builtin_clzll(x))
#define lsb(x) (__builtin_ctzll(x))
#define bit_count(x) (__builtin_popcountll(x))
#define int long long
using namespace std;
const int N = 2e5+2,inf = 1e9 + 9;
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
int SQ = 320;
void solve(){
    int n,q;cin >> n >> q;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin >> a[i];
    int len = sqrt(n)+1;
    vector<int>b(len);
    for(int i=0;i<n;i++){
        b[i/len] += a[i];
    }
    while (q--){
        int t;cin>>t;
        if(t == 1){
            int idx,v;cin>>idx>>v;
            idx--;
            int blk = idx/len;
            b[blk] -= a[idx];
            a[idx] = v;
            b[blk] += a[idx];
            continue;
        }
        int l,r;cin>>l>>r;
        l--,r--;
        int sum = 0;
        int blk_l = l/len;
        int blk_r = r/len;
        if(blk_l == blk_r){
            for(int i=l;i<=r;i++){
                sum += a[i];
            }
            cout << sum << "\n";
            continue;
        }
        for(int i=l;i<=blk_l*len+len-1;i++){
            sum += a[i];
        }
        for(int i =blk_l+1;i<=blk_r-1;i++){
            sum += b[i];
        }
        for(int i =blk_r*len;i<=r;i++){
            sum += a[i];
        }
        cout << sum << "\n";

    }

}

signed main() {
    fileIO();
    fastIO();
    int tc=1;
//    cin>>tc;
    while (tc--)
        solve();
    return 0;
}