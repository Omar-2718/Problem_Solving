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

struct query {
    int l, r, idx;

    bool operator<(query &other) {
        if (l / SQ != other.l / SQ) return l / SQ < other.l / SQ;
        return ((l / SQ) & 1) ? r > other.r : r < other.r;
    }
};

// DONT FORGET TO SORT THE V
// AND SET SQ
// Try n/log(n)
// AND RESET CNT FOR TEST DUMBASS
int cnt =0;
void add (int idx) {
}
void del(int idx) {
}
int get() {
    return cnt;
}
void solve(){
    int q;
    vector<query>v(q);
    vector<int> ans(q);
    std::sort(v.begin(), v.end());
    int l = 0, r = -1;
    for (auto &[lq, rq, idx]: v) {
        while (lq < l) add(--l);
        while (r < rq) add(++r);
        while (l < lq) del(l++);
        while (r > rq) del(r--);
        ans[idx] = get();
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