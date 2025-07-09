#include <bits/stdc++.h>
using namespace std;
struct node{
    // set variables of nodes here
    node(){
    }
    void change(int _val,int _tp){

    }
};
class seg_tree{
public:
    int sz;
    vector<node>arr_nodes;
    seg_tree(int _sz){
        sz = 1<<(msb(_sz)+1);
        arr_nodes.assign(2*sz,{});
    }
    node merge(node lft,node rt){
        node ans;
        // merge here
        
        return ans;
    }
    node get(int tl,int tr,int l,int r,int ni){

        if(tl >= r or tr <= l){
            return {};
        }
        if(tl <= l and tr >= r){
            return arr_nodes[ni];
        }

        int mid = (r+l)/2;
        return merge( get(tl,tr,l,mid,2*ni+1),
                      get(tl,tr,mid,r,2*ni+2));
    }

    void set(int idx,int val,int l,int r,int ni){
        int mid = (r+l)/2;
        if(idx < l or idx >= r)return;
        if(l == r-1){
            arr_nodes[ni].change(val,0);
            return;
        }
        set(idx,val,l,mid,2*ni+1);
        set(idx,val,mid,r,2*ni+2);
        arr_nodes[ni] = merge(arr_nodes[2*ni+1],arr_nodes[2*ni+2]);
    }
    node get(int tl,int tr){
        return get(tl,tr,0,sz,0);
    }
    void set(int idx,int val){
        set(idx,val,0,sz,0);
    }
    void init(vector<int>&arr,int l,int r,int ni){
        if(l >= arr.size())return;
        int mid = (r+l)/2;
        if(l == r-1){
            arr_nodes[ni].change(arr[l],0);
            return;
        }
        init(arr,l,mid,2*ni+1);
        init(arr,mid,r,2*ni+2);
        arr_nodes[ni] = merge(arr_nodes[2*ni+1],arr_nodes[2*ni+2]);
    }
    void init(vector<int>&arr){
        init(arr,0,sz,0);
    }
};
