struct node{
    int lazy = 0;
    bool is_lazy = 0;
    int val = 0;
    node (){
    }
    void add(int lx,int rx,int x){
        val += x*(rx-lx);
        lazy += x;
        is_lazy = 1;
    }
};
class lazy_seg{
public:
    int sz;
    vector<node>arr_nodes;
    lazy_seg(int _sz){
        sz = 1;
        while (sz <= _sz){
            sz*=2;
        }
        arr_nodes.assign(sz*2,{});
    }
    node merge(node lft,node rt){
        // change here
        node ans = node();
        ans.val = lft.val + rt.val;
        return ans;
    }
    void init(vector<int>&arr,int lx,int rx,int ni){
        int mid = (rx+lx)/2;
        if(rx - lx == 1){
            // change here
            if(lx < arr.size())
                arr_nodes[ni].val = arr[lx];
            return;
        }
        init(arr,lx,mid,2*ni+1);
        init(arr,mid,rx,2*ni+2);
        arr_nodes[ni] = merge(arr_nodes[2*ni+1],arr_nodes[2*ni+2]);
    }
    void init(vector<int>&arr){
        init(arr,0,sz,0);
    }
    void propagate(int lx,int rx,int ni){
        if(rx - lx == 1 or not arr_nodes[ni].is_lazy)return;
        int mid = (rx+lx)/2;
        arr_nodes[2*ni+1].add(lx,mid,arr_nodes[ni].lazy);
        arr_nodes[2*ni+2].add(mid,rx,arr_nodes[ni].lazy);
        arr_nodes[ni].lazy = arr_nodes[ni].is_lazy = 0;
    }
    void set(int l,int r,int x,int lx,int rx,int ni){
        propagate(lx,rx,ni);
        int mid = (rx+lx)/2;
        if(lx >= r or rx <= l)return;
        if(lx >= l and rx <= r){
            arr_nodes[ni].add(lx,rx,x);
            return;
        }
        set(l,r,x,lx,mid,2*ni+1);
        set(l,r,x,mid,rx,2*ni+2);
        arr_nodes[ni] = merge(arr_nodes[2*ni+1],arr_nodes[2*ni+2]);
    }
    void set(int l,int r,int x){
        set(l,r,x,0,sz,0);
    }
    node get(int l,int r,int lx,int rx,int ni){
        propagate(lx,rx,ni);
        int mid = (rx+lx)/2;
        if(lx >= l and rx <= r)return arr_nodes[ni];
        if(lx >= r or rx <= l)return {};
        node lft = get(l,r,lx,mid,2*ni+1);
        node rt = get(l,r,mid,rx,2*ni+2);
        return merge(lft,rt);
    }
    node get(int l,int r){
        return get(l,r,0,sz,0);
    }
};