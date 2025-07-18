int l=1,r=mx;
while(r>=l){
int mid = (r+l)/2;
int m1 = check(mid);
int m2 = check(mid+1);
if(m1>=m2){
ans = updateAns(and,m1);
r=mid-1;
}
else{
l=mid+1;
ans = updateAns(and,m2);
}
}