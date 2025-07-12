int lcm(int x,int y){
    return (x/__gcd(x,y)) * y ;
}