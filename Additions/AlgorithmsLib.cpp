#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <climits>
#include <bits/stdc++.h>
#include <string>
#include <math.h>
#define int long long int
using namespace std;
//const int N =2e5 + 5;
//int n,q,s[N],T[N][22];
//int merge(int a,int b){
//    return min(a,b);
//}
//void build(){
//
//    for (int pw = 0; (1 << pw) <= n; pw++) {// nlog(n)
//        for(int i =0;i + (1 << pw)<=n;i++) {
//            if(!pw) {
//                T[i][pw] = s[i];
//                continue;
//            }
//            T[i][pw] = merge(T[i][pw - 1], T[i + (1 << (pw - 1))][pw - 1]);
//        }
//    }
//
//}
//int query(int l,int r){
//    int sz = r-l+1;
//    int ret = 1e10;
//    for(int i = 21;i>=0;i--){
//        // closest power of 2 or binary representation
//        if((sz >> i)&1){
//            ret = merge(ret,T[l][i]);
//            l += (1 << i);
//        }
//    }
//    return ret;
//}
//int query2(int l,int r){
//    int sz = r-l+1;
//    // 1 2 3 4 5 6 7
//    // 0 1 2 3 4 5 6
//    //  2 to 7
//    // 2 to 5
//    return merge(T[l][msb(sz)],T[(r - (1 << msb(sz))) + 1][msb(sz)]);
//}
class algo{
    class [[maybe_unused]] binary_search{
        void sliding_windows() {
            int ans = 0,sum=0,n=0,d=0;
            vector<pair<int,int>>arr;
            for (int l = 0, r = 0; r < n; r++) {
                sum += arr[r].second;
                while (arr[r].first - arr[l].first >= d) {
                    sum -= arr[l].second;
                    l++;
                }
                ans = max(ans, sum);
            }

            cout << ans;
        }
        int up_bound(int t){
            int n;
            vector<int>arr;
            int ans = n;
            int l =0,r=n-1;
            while (l<=r){
                int mid = (l+r)/2;
                if(arr[mid] > t){
                    ans = mid;
                    r = mid-1;
                    // 10 20 30 30 30 40 50
                }
                else{
                    l = mid + 1;
                }
            }
            return ans;
        }
    };
    class [[maybe_unused]] numberTheory {
        //int phi(int n){
        //    int res = n;
        //    if(n == 0)
        //        return 0;
        //    for(int i =0;primes[i] * primes[i] <= n;i++){
        //        if (n % primes[i] == 0){
        //            res -= res/primes[i];
        //            while (n % primes[i] == 0)
        //            n /= primes[i];
        //        }
        //    }
        //    if(n > 1){
        //        res -= res/n;
        //    }
        //    return res;
        //}
        vector<int> sieve(int n)
        {   // this calculate every prime through n
            /*Assume every number as prime and search every number from 2 -> n if the number is prime
             * make every multiple n + n + .. of it not prime*/
            vector<int> prime;
            vector<bool> notPrime(n + 1, false);
            for (int i = 2; i <= n; i++) {
                if (!notPrime[i]) {
                    prime.push_back(i);
                    for (int j = 2 * i; j <= n; j += i) {
                        notPrime[j] = true;
                    }
                }
            }
            return prime;
        }
        vector<int> divisors(int n) {
            /* calculate the divisors from 2 -> sqrt(n) since they mirror around the sqrt
             * we can run to the sqrt only and flip the n/divisor as the mirrored divisor
             * since if the number have a sqrt already it will be added twice
             * so we check if not so we can mul it
             * we flip the values to two vectors one is the divisor and the other is the mirror
             * divisor and then join them together*/
            vector<int> a, b;
            for (int i = 1; i * i <= n; i++) {
                if (n % i == 0) {
                    a.push_back(i);
                    if (i * i != n)b.push_back(n / i);
                }

            }
            int bs = b.size();
            for (int i = 0; i < bs; i++) {
                a.push_back(b.back());
                b.pop_back();
            }
            return a;
        }
        map<int, int> primeFactors(int n) {
            map<int, int> mp;
            while (n % 2 == 0) {
                mp[2]++;
                n /= 2;


            }
            for (int i = 3; i * i <= n; i += 2) {
                while (n % i == 0) {
                    mp[i]++;
                    n /= i;
                }
            }
            if (n > 1)mp[n]++;
            return mp;


        }
        bool isPrime(int n) {
            if (n < 2)
                return false;
            for (int i = 2; i * i <= n; i++) {
                if (n % i == 0)
                    return false;
            }
            return true;
        }
        int numOfFactors(int n) {
            map<int, int> mp;
            while (n % 2 == 0) {
                mp[2]++;
                n /= 2;


            }
            for (int i = 3; i * i <= n; i += 2) {
                while (n % i == 0) {
                    mp[i]++;
                    n /= i;
                }
            }
            if (n > 1)mp[n]++;
            int sum = 1;
            for (auto e: mp) {
                sum *= e.second + 1;
            }
            return sum;
        }
        bool IsUniquePrimeFactors(int n) {
            map<int, int> mp;
            bool firstTime = true;
            while (n % 2 == 0) {
                if (!firstTime)
                    return false;

                mp[2]++;
                n /= 2;
                firstTime = false;


            }

            for (int i = 3; i * i <= n; i += 2) {
                firstTime = true;
                while (n % i == 0) {
                    if (!firstTime)
                        return false;

                    mp[i]++;
                    n /= i;
                    firstTime = false;

                }
            }
            if (n > 1)
                if (mp[n] == 0)
                    return true;
                else
                    return false;

            return true;
        }
    };
    class [[maybe_unused]] numberTheory2{
        void ChadSieve(){
            int N = 5000005;
            vector<int>primesDivisor(N+10);
            vector<bool>isPrime(N+10, true);
            vector<int>numOfPrimes(N+10);

            isPrime[0]=isPrime[1]= false;
            for(int i =2;i<=N;i++){
                if(isPrime[i]){
                    primesDivisor[i] = i;
                    for(int j = i *i;j<=N;j+=i){
                        isPrime[j] = false;
                        primesDivisor[j] = i;
                    }
                }
            }

        }
        void divisors(){
            int n;
            vector<vector<int>>divisors(n);
            for(int i =1;i<=n;i++){
                for(int j =i;j<=n;j+=i){
                    divisors[j].push_back(i);
                }
            }
        }
        void calcNumOfPrimes(){
            int N = 5000005;
            vector<int>primesDivisor(N+10);
            vector<bool>isPrime(N+10, true);
            vector<int>numOfPrimes(N+10);
            numOfPrimes[0] = 0;
            numOfPrimes[1] = 1;
            for(int i =2;i<=N;i++){
                int sum =0;
                int n = i;
                while (n != 1){
                    int x = primesDivisor[n];
                    n /= x;
                    sum++;
                }
                numOfPrimes[i] += numOfPrimes[i-1]+sum;
            }
        }
        int N =1e6;
        void sieveTheSmallestPrimeFactor(){
            vector<int>smallestDivisor(N+10);
            vector<bool>isPrime(N, true);
            isPrime[0]=isPrime[1]=false;smallestDivisor[1]=1;
            for(int i =2;i<=N;i++){
                if(isPrime[i]){
                    smallestDivisor[i] = i;
                    for(int j =i*i;j<=N;j+=i){
                        if(smallestDivisor[j] == 0){
                            smallestDivisor[j] = i;
                        }
                        isPrime[j] = false;
                    }
                }
            }
        }
        int lcd(int a,int b){
            return (a/ gcd(a,b)) * b;
        }
        /*
         * gcd(a,b) = gcd(a-b,b)
         * lcm * gcd = a * b
         * lcd of a permutation is max max max exp 1+a1 2+a2 .. n = 5
         * 5 5 5 5 5
         *
         * */
    };
    class idk{
        // incomplete
        struct DSU {
            vector<int>parent;
            void init(int n){
                parent.resize(n+1);
                for(int i = 1;i<=n;i++){
                    parent[i] = i;
                }
            }
            int find_root(int u){
                if(parent[u] == u)
                    return u;
                return find_root(parent[u]);
            }
            bool merge(int u,int v){
                int root_u = find_root(u);
                int root_v = find_root(v);
                if(root_u == root_v)
                    return 0;
                parent[root_u] = root_v;
                return 1;
            }

        };
        void decimalToBinary(int n){
            vector<int>arr;
            while (n){
                arr.push_back(n%2);
                n /= 2;
            }
            //  8 4 2 1
            reverse(arr.begin(),arr.end());
            for(auto e : arr){
                cout << e << " ";
            }
        }
        void goodQuestion(){
            /*You have a number n
         and q
         queries.

        1 : change value of (first bit equal to 0) to 1.
        2 : change value of (first bit equal to 1) to 0.
        3 : change all bits (from index 0 until first bit equal to 1) to 1. if n equal 0,then n will be −1.
        4 :change all bits (from index 0 until first bit equal to 0) to 0.
        5 :if n is power of two print "is power of two", otherwise print "not power of two".*/
            int n,q;cin>>n>>q;
            while (q--){
                int t;cin>>t;
                switch (t) {
                    case 1:
                        n = n | n+1;
                        cout << n << "\n";
                        break;
                    case 2:
                        n = n & n-1;
                        cout << n << "\n";
                        break;
                    case 3:
                        n = n | n-1;
                        cout << n << "\n";
                        break;
                    case 4:
                        n = n & n+1;
                        cout << n << "\n";
                        break;
                    case 5:
                        if(!n || n & n-1){
                            cout <<"not power of two\n";
                        }
                        else{
                            cout << "is power of two\n";
                        }
                        break;

                }
            }
        }
        void prefix_And(){
            int n;cin>>n;
            vector<int>arr(n);
            for(int i =0;i<n;i++)
                cin>>arr[i];
            vector<vector<int>>prefix_bits(32,vector<int>(n+5));
            for(int i =0;i<n;i++){
                for(int j = 0;j<32;j++){
                    if(arr[i] & (1 << j)){
                        prefix_bits[j][i+1] = prefix_bits[j][i] + 1;
                    }
                    else{
                        prefix_bits[j][i+1] = prefix_bits[j][i];
                    }
                }
            }
            int q;cin>>q;
            while (q--){
                int l,r,ans=0;cin>>l>>r;
                for(int j =0;j<32;j++){
                    if(prefix_bits[j][r] - prefix_bits[j][l-1] == r-l+1){
                        ans = ans | 1 << j;
                    }
                }
                cout << ans<<"\n";
            }
        }
        /*n < 20 complexity 2^n * n */
        void printAllSub(){
            int n;cin>>n;
            vector<int>arr(n);
            for(int i =0;i<n;i++)
                cin >> arr[i];
            for(int i = 0;i< (1 << n) /*2 ^ n - 1*/;i++){
                int msk = i,j=0;
                while (msk){
                    if(msk & 1)
                        cout << arr[j] << " ";
                    j++;
                    msk = msk >> 1;
                }
                cout << "\n";
            }
        }
        int fast_pow(int x,int n){
            int res = 1,m = x;
            // 3 ^ 40
            while (n){
                if(n & 1){
                    /*n = 3 3*3*3 = 3^2 * 3^1 you want to represent the pow as multiple of 2
                     * n = 40 3^32 * 3^8
                     * 011
                     * */
                    res *= m;
                }
                m = m*m;
                // 3 3^2 3^4 3^8
                // 100011 -> 10001 -> 1000
                n = n >> 1;
            }
            return res;
        }
        /*use and to check if a bit is 0 or 1 ex
         n & (1 << index)
         use or to flip a bit to 1
         n = n | (1 << index)

         n & n-1 = removing the first 1 and making it 0 ex 011101 = 011100 and you can count
         the number of bits with a loop
         prefix xor works haha
         010000 001111

         a b c d x x = a^b^c^d
         x ^ a ^ b ^ c ^ d = 0 ^ both sides by a
         x ^ b ^ c ^ d = a
         then any element is an answer

         */
    };
    class studyLater{
        /*10
 * 5  0
 * 2   1
 * 1   0
 * 0    1*/
        int fast_pow(int x,int n){
            int res = 1,m = x;
            // 3 ^ 40
            while (n){
                if(n & 1){
                    // n = 3 3*3*3 = 3^2 * 3^1 you want to represent the pow as multiple of 2
                    res *= m;
                }
                m = m*m;
                n = n >> 1;

            }
            return res;
        }
        void solve(){
            // 2^0 * k + 2^1 * k + 2^2 * k k=0,1 1001
            // 10 ^ 0 *k + 10 ^ 1 *k + 10 ^ 2*k k = 0->9
            // 15 6^0 *5 + 6^1 *1 = 11
            int t,n,x,ans=0;cin>>t;
            int i =0;
            if(t == 1){
                // base x to decimal 1001 -> 9
                cin >> n >> x;
                while (n){
                    ans += (n % 10) * fast_pow(x,i);
                    n /= 10;
                    i++;
                }
                cout << ans;

            }
            else{
                /* decimal to base x
                 * 5
                 * 1  2
                 * 0  1
                 * 3 ^ 0 + 3 ^ 1
                 * */
                cin >> n >> x;
                vector<int>arr;
                while (n){
                    arr.push_back(n % x);
                    n /= x;
                }
                reverse(arr.begin(),arr.end());
                for(auto e : arr)
                    cout << e;

            }
        }

    };
    class recursion{
        /*int N = 8,ans = 0;
vector<vector<int>>val(N+1,vector<int>(N+1));
vector<bool>diag_r(2*N+1, false),diag_l(2*N+1,false),column(N, false);

void f(int r,int sum){
    if(r == N){
        ans = max(ans,sum);
        return;
    }
    for(int c = 0;c<N;c++){
        if(!diag_r[r+c] && !diag_l[N + r-c] && !column[c]){
            diag_r[r+c] = diag_l[N+r-c] = column[c] = true;
            sum += val[r][c];
            f(r+1,sum);
            sum -= val[r][c];
            diag_r[r+c] = diag_l[N+r-c] = column[c] = false;

        }
    }
}

void solve(){
    ans = 0;
    diag_r.clear();diag_l.clear();column.clear();
    for(int i =0;i<8;i++){
        for(int j =0;j<8;j++){
            cin >> val[i][j];
        }
    }
    f(0,0);
    cout << ans << "\n";

}
*/
        /*string arithmitic
         * string multiByNum(string & a,char  b){
    string res = "";
    stack<char>st;
    int n = a.size();
    int lft = 0;
    for(int i = n-1;i>=0;i--){
        int m = (b - '0') * (a[i] - '0') + lft;
        if( m >= 10){
            st.push((m % 10) + '0');
            lft = m/10;
        }
        else{
            lft = 0;
            st.push(m + '0');
        }
    }
    if(lft != 0)
        st.push(lft + '0');
    while (!st.empty()){
        res += st.top();
        st.pop();
    }
    return res;
}
string add_str(vector<string>strArr){
    int n = 0;
    stack<int>st;
    for(auto e : strArr){
        n = max((int)e.size(),n);
    }
    int lft = 0;
    for(int i =0;i<n;i++){
        int ans = 0;
        for(auto e : strArr){
            int s = e.size();
            if(s-1-i >= 0)
            ans += e[s-1 - i] - '0';
        }
        ans += lft % 10;
        if(ans >= 10) {
            st.push(ans % 10);
            lft = ans / 10;
        }
        else{
            st.push(ans);
            lft = 0;
        }
    }
    if(lft != 0)
        st.push(lft);
    string res= "";
    while (!st.empty()){
        res += st.top() + '0';
        st.pop();
    }
    return res;
}
string multiByStr(string & a,string & b){
    vector<string>arr;
    int n = b.size();
    for(int i =0;i<n;i++) {
        if(b[i] == '0')
            break;
        string ans = multiByNum(a, b[i]);
        ans.insert(ans.size(),(n-1)- i,'0');
        arr.push_back(ans);
    }
    return add_str(arr);

}*/
    };
    class graph{
        int n,m;
        vector<int> adj[10005];
        bool vis[10005];
        // min dis
        int dis[100009];
        int parent[100009];
        void bfs(int start){
            queue<int>q;

            q.push(start);
            dis[start] = 0;

            while (!q.empty()){
                int u = q.front();
                q.pop();
//        cout << u << " ";
                for(auto e : adj[u]){
                    if(dis[e] == -1) {
                        q.push(e);
                        parent[e] = u;
                        dis[e] = dis[u] + 1;
                    }
                }
            }

        }
        bool is_cyclic(int u,int p){
            // only work on undirected
            vis[u] = true;
            for(int v : adj[u]){
                if(vis[v] && v != p){
                    return true;
                }
                if(!vis[v]) {
                    if(is_cyclic(v, u)) return true;
                }
            }
            return false;
        }

    };
};
