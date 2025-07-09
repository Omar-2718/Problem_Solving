#include <bits/stdc++.h>
using namespace std;
class Hash{
private:
    int h1=0,b1=31,m1= 1e9 + 7,inv1;
    int h2=0,b2=53,m2= 1e9 + 9,sz=0,inv2;
    vector<int> pw1,pw2;
    deque<char>dq;
    int fst_pow(int a,int pr){
        int ans = 1;
        while (pr) {
            if (pr % 2) {
                ans = (ans * a) % m2;
            }
            a = (a % m2 * a % m2) % m2;
            pr >>= 1;
        }
        return ans;
    }
public:
    void init(int N){
        pw1.assign(N,1);
        pw2.assign(N,1);

        inv1 = fst_pow(b1, m1 - 2);
        inv2 = fst_pow(b2, m2 - 2);
        for(int i =1;i<N;i++){
            pw1[i] = (pw1[i-1] * b1) % m1;
            pw2[i] = (pw2[i-1] * b2) % m2;
        }
    }
    void push_back(char c){
        dq.push_back(c);
        c = c-'a'+1;
        h1 = (h1 % m1 * b1 % m1) % m1;
        h1 = (h1 + c) % m1;

        h2 = (h2 % m2 * b2 % m2) % m2;
        h2 = (h2 + c) % m2;
        sz++;
    }
    void push_front(char c){
        dq.push_front(c);
        c = c-'a'+1;
        h1 = (h1 + (c * pw1[sz]) % m1) % m1;
        h2 = (h2 + (c * pw2[sz]) % m2) % m2;
        sz++;
    }
    void pop_back(){
        sz--;
        char c = dq.back()-'a'+1;
        h1 = (h1 - c + m1) % m1;
        h1 = (h1 * inv1) % m1;

        h2 = (h2 - c + m2) % m2;
        h2 = (h2 * inv2) % m2;
        dq.pop_back();
    }
    void pop_front(){
        sz--;
        char c = dq.front()-'a'+1;
        h1 = ((h1 - (c * pw1[sz]) % m1) + m1) % m1;
        h2 = ((h2 - (c * pw2[sz]) % m2) + m2) % m2;
        dq.pop_front();
    }
    void clear(){
        h2 = h1 = sz =0;
        dq.clear();
    }
    bool operator==(const Hash&H)const{
        return H.h2 == h2 and H.h1 == h1;
    }
    string get_string(){
        return string(dq.begin(),dq.end());
    }
    pair<int,int> getHash(){
        return {h1,h2};
    }
};
void solve() {
    int t;

    Hash hs;hs.init(100);
    vector<Hash>arr;
    while (true){
        cout << "Enter 0 to push back and 1 to push front\n";
        cout << "Enter 5 to pop back and 6 to pop front\n";
        cout << "Enter 2 to store and 3 to print stored\n";
        cin>>t;
        system("cls");
        if(t == -1){
            return;
        }
        if(t == 0){
            char c;cin>>c;
            hs.push_back(c);
            cout << "String : ";
            cout << hs.get_string() << '\n';
            cout << "Hash 1 : ";
            cout << hs.get_hash().first << '\n';
            cout << "Hash 2 : ";
            cout << hs.get_hash().second << '\n';

        }
        if(t == 1){
            char c;cin>>c;
            hs.push_front(c);
            cout << "String : ";
            cout << hs.get_string() << '\n';
            cout << "Hash 1 : ";
            cout << hs.get_hash().first << '\n';
            cout << "Hash 2 : ";
            cout << hs.get_hash().second << '\n';
        }
        if(t == 5){
            hs.pop_back();
            cout << "String : ";
            cout << hs.get_string() << '\n';
            cout << "Hash 1 : ";
            cout << hs.get_hash().first << '\n';
            cout << "Hash 2 : ";
            cout << hs.get_hash().second << '\n';
        }
        if(t == 6){
            hs.pop_front();
            cout << "String : ";
            cout << hs.get_string() << '\n';
            cout << "Hash 1 : ";
            cout << hs.get_hash().first << '\n';
            cout << "Hash 2 : ";
            cout << hs.get_hash().second << '\n';
        }
        if(t == 2){
            arr.push_back(hs);
        }
        if(t == 3){
            for(auto e : arr){
                cout << "String : ";
                cout << e.get_string() << '\n';
                cout << "Hash 1 : ";
                cout << e.get_hash().first << '\n';
                cout << "Hash 2 : ";
                cout << e.get_hash().second << '\n';

            }
        }

    }
}