#include <bits/stdc++.h>
using namespace std;
int nCr(int n,int k){
    int ans = 1;
    int tem = 1;
    if(k < 0)
        return 0;
    bool m = 1;
    for(int i = n;i>=n-k+1;i--){
        if(m) {
            ans *= i;
            ans /= tem++;
        }
        else ans *=i;

        if(tem > k)
            m = 0;
    }
    return ans;
}