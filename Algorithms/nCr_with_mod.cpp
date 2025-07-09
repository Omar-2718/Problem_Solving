#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6;
const int MOD = 1e9 + 7;

int fac[MAXN+1];
int inv[MAXN+1];
int pow_mod(int a,int p){
    int ans = 1;
    while (p){
        if(p%2){
            ans = ans%MOD * a %MOD;
            ans %= MOD;
            p--;
        }
        else{
            a = a%MOD * a%MOD;
            p /= 2;
        }
    }
    return ans;
}
void fact(){
    fac[0] = 1;
    for(int i =1;i<=MAXN;i++){
        fac[i] = fac[i-1] * i%MOD;
        fac[i] %= MOD;
    }
}
void inverse(){
    // n!^-1 = n^-1 mod p
    // n^-1 = n^-1 * (n+1)^-1 * (n+1)
    // n^-1 = (n*(n+1))^-1 * (n+1)
    // n^-1 = ((n+1)!)^-1 * (n+1)
    // set n to n-1
    // ((n-1)!)^-1 = (n!)^-1 * n
    inv[MAXN] = pow_mod(fac[MAXN],MOD-2);
    for(int i =MAXN;i>=1;i--){
        inv[i-1] = inv[i] * i%MOD;
        inv[i-1] %= MOD;
    }
}
int nCr(int n,int r){
    assert(n-r >= 0 and n >= r);
    return (((fac[n]*inv[r])%MOD)*inv[n-r])%MOD;

}
int nPr(int n,int r){
    assert(r >= 0 and n >= r);
    return (fac[n]*inv[r])%MOD;
}