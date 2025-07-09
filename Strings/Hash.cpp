int pow_mod(int a,int b,int m){
    int ans = 1;
    while (b){
        if(b&1){
            ans = (ans*a*1ll)%m;
        }
        a = (a * a*1ll)%m;
        b>>=1;
    }
    return ans;
}
const int N =2e6+5;
vector<int>pw1(N);
int m1=1000002637 + 7,b1=31;
void init(){

    pw1[0] = 1;
    for(int i =1;i<=N;i++){
        pw1[i] = (1ll * pw1[i-1] * b1)%m1;
    }

}
vector<int>hs(N);
class Hash{
public:
    void build(string &arr){
        int h1=0,h2=0;
        for(int i =0;i<arr.size();i++){
            h1 = (1ll*h1*b1)%m1 + arr[i]-'a' + 1;
            h1 %= m1;

            hs[i] = h1;
        }
    }

    int get(int l,int r){
        return (hs[r] - ((1ll * (l-1 >= 0 ? hs[l-1] : 0) *pw1[r-l+1])) + 1ll * m1*m1)%m1;
    }

};