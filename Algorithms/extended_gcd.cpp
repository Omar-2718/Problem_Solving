#include <bits/stdc++.h>
using namespace std;
int gcd_e(int a,int b,int &x,int &y){
    if(a < 0){
        int r = gcd_e(-a,b,x,y);
        x *= -1;
        return r;
    }
    if(b < 0){
        int r = gcd_e(a,-b,x,y);
        y *= -1;
        return r;
    }
    if(b == 0){
        x = 1;y = 0;
        return a;
    }
    int g = gcd_e(b,a%b,y,x);
    y -= (a/b)*x;
    return g;
}