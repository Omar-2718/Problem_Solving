#define ul unsigned long long
ul rndVal[100001];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
static void init(){
    for(int i =1;i<=100000;i++){
        rndVal[i] = rng();
    }
}
class multiset_hash{
public:
    vector<ul>hs;

    void build(vector<int>&arr){
        hs.assign(arr.size(),0);
        hs[0] = rndVal[arr[0]];
        for(int i =1;i<arr.size();i++){
            hs[i] = hs[i-1] + rndVal[arr[i]];
        }
    }
    ul get(int l,int r){
        return (hs[r] - (l-1>=0 ? hs[l-1] : 0));
    }
    ul get_hash(){
        return hs.back();
    }
};