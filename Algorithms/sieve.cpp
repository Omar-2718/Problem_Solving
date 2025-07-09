#include <bits/stdc++.h>
using namespace std;
vector<int>prime_factor(100009);
vector<bool>is_prime(100009, true);
void sieve(){
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2;i<=100007;i++){
        if(is_prime[i]){
            prime_factor[i] = i;
            for(int j = i*i;j<=100007;j+=i){
                is_prime[j] = 0;
                if(prime_factor[j] == 0)
                prime_factor[j] = i;
            }
        }
    }
}
vector<pair<int,int>>factorize(int a){
    vector<pair<int,int>>ans;
    while (a != 1){
        int cnt = 0;
        int fac = prime_factor[a];
        while (a != 1 && a%fac==0) {
            cnt++;
            a /= fac;
        }
        ans.push_back({fac,cnt});
    }
    return ans;
}