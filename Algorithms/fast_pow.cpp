int fast_pow(int base,int p,int mod = 1000000007){
    int res = 1;
    base %= mod;
    while (p) {
        if (p & 1) {
            res = (res*base)%mod;
        }
        base *= base;
        base %= mod;
        p >>= 1;
    }
    return res;
}