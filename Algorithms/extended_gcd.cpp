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
int inv(int a,int m){
    int x,y;
    int g= gcd_e(a,m,x,y);
    if (g != 1) {
        // Inverse doesn't exist
        // You can throw an error, return -1, or handle as needed
        return -1;
    }
    return (x % m + m) % m;
}