mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int m1 = 1e9+7;
int b1 = uniform_int_distribution<int>(0.1 * m1, 0.9 * m1)(rng);

int m2 = 991831889;
int b2 = uniform_int_distribution<int>(0.1 * m2, 0.9 * m2)(rng);

vector<int> pw1,iv1(1);
vector<int>pw2,iv2(1);

int pow_mod(int a,int b,int m){
    int ans = 1;
    while (b){
        if(b&1){
            ans = ans*a;
            ans %= m;
        }
        a = a * a;
        a %= m;
        b>>=1;
    }
    return ans;
}
void init(int n){
    pw1.assign(n+2,1);
    pw2.assign(n+2,1);
    iv1.assign(n+2,1);
    iv2.assign(n+2,1);
    pw1[0] = pw2[0] = 1;
    iv1[1] = pow_mod(b1,m1-2,m1);
    iv2[1] = pow_mod(b2,m2-2,m2);
    for(int i =1;i<=n;i++){
        pw1[i] = pw1[i-1] * b1%m1;
        pw2[i] = pw2[i-1] * b2%m2;
        iv1[i] = (iv1[i-1] * iv1[1])%m1;
        iv2[i] = (iv2[i-1] * iv2[1])%m2;
    }
}
class Hash{
    // BE CAREFUL ABOUT MODS OPERATIONS
    // REMOVE THE DOUBLE HASH AND DEQUE IF NEEDED
    // TO USE GET() YOU HAVE TO USE THE DEQUE IN PUSH AND POP
public:
    int h1=0,h2=0,sz=0;
    vector<pair<int,int>>hs;
    void build(string& s){
        clear();
        hs.assign(s.size(),{});
        for(int i =0;i<s.size();i++){
            h1 = ((h1*b1) + (s[i] - 'a' +1))%m1;

            h2 = ((h2*b2) + (s[i] -'a' +1))%m2;

            hs[i] = {h1,h2};
        }
    }
    void push_back(char c){
        c = c-'a'+1;
        h1 = (h1 * b1 + c)%m1;

        h2 =(h2 * b2 + c)%m2;

        sz++;
    }
    void push_front(char c){
        c = c-'a'+1;
        h1 = (h1 + (pw1[sz] * c))%m1;

        h2 = (h2 + (pw2[sz] * c))%m2;

        sz++;
    }

    void pop_front(char d){
        char c = d - 'a' + 1;
        sz--;

        h1 = (h1 - (c*pw1[sz]) + m1*m1);
        h1 %= m1;

        h2 = (h2 - (c*pw2[sz]) + m2*m2);
        h2 %= m2;
    }
    void clear(){
        sz = h1 = h2= 0;
        hs.clear();
    }
    int get_hash(){
        return h1*h2;
    }
    int get(int l,int r){
        return ((hs[r].first - ((l-1 >= 0 ? hs[l-1].first : 0) *pw1[r-l+1]) + m1*m1)%m1)
               *((hs[r].second - ((l-1 >= 0 ? hs[l-1].second : 0)*pw2[r-l+1]) + m2*m2)%m2);
    }
};