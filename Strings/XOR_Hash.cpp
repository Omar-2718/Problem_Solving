mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rndVal[71];

struct num{
    signed short bits[64];
    signed short base = 2;
    num(){

    }
    num(int val){
        for(int i =0;i<64;i++){
            bits[i] = ((val>>i)&1);
        }
    }
    num inverse(){
        num inv{};
        for(int j =0;j<64;j++){
            inv.bits[j] = base - bits[j];
            if(inv.bits[j] >= base)inv.bits[j]-= base;
        }
        return inv;
    }
    num operator^(const num& n){
        num ret{};
        for(int i=0;i<64;i++){
            ret.bits[i] = bits[i] + n.bits[i];
            if(ret.bits[i] >= base){
                ret.bits[i] -= base;
            }
        }
        return ret;
    }
};
bool operator<(const num& a, const num& b) {
    for(int i = 63; i >= 0; i--) {
        if (a.bits[i] != b.bits[i]) return a.bits[i] < b.bits[i];
    }
    return false;
}
for(int i=1;i<=70;i++){
rndVal[i] = uniform_int_distribution<int>(1,LLONG_MAX)(rng);
}