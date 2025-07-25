#include <bits/stdc++.h>
#define msb(x) (63 - __builtin_clzll(x))
#define lsb(x) (__builtin_ctzll(x))
#define bit_count(x) (__builtin_popcountll(x))
#define ll long long
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

vector<int> pi_function(string s){

    vector<int>pi(s.size());
    pi[0] = 0;
    for(int i =1;i<s.size();i++){
        int l = pi[i-1];
        while (s[l] != s[i] and l){
            l = pi[l-1];
        }
        if(s[l] == s[i])
            pi[i] = l+1;
    }
    return pi;

}
// longest prefix of pattern that is a suffix of the search
int aut[N+2][26];
void compute_automaton(string s)
{
    s += '#';
    int n = (int)s.size();
    vector<int> pi = pi_function(s);
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i]) aut[i][c] = aut[pi[i-1]][c];
            else aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}
void solve(){
    string s;cin>>s;
    compute_automaton(s);

    cout << "Enter characters one by one to simulate automaton. Use '.' to stop.\n";
    int state = 0;
    while (true) {
        char t; cin >> t;
        if (t == '.') break;
        if (t < 'a' || t > 'z') {
            cout << "Invalid character. Please enter a lowercase letter.\n";
            continue;
        }
        state = aut[state][t - 'a'];
        cout << "Current state: " << state << "\n";
        if (state == s.size()) {
            cout << "Pattern fully matched!\n";
        }
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