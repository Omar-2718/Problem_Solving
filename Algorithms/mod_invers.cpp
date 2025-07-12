int fastpow(int Base , int Power , int MOD = 10000000007){
    int Result = 1;

    while(Power){
        if(Power & 1){
            Result = (Result * Base) % MOD;
        }
        Base = (Base * Base) % MOD;
        Power >>= 1;
    }
    return Result % MOD;
}
int modInverse(int n , int MOD){
    return fastpow(n , MOD - 2 , MOD);
}