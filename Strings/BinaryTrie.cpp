struct Trie{

    struct Node{
        // lower case
        Node* child[2];
        int ends,prefix;
        Node(){
            memset(child,0,sizeof child);
            ends = prefix = 0;
        }
    };
    Node *root = new Node();
    string to_bin(int num){
        string ans;
        for(int bit =0;bit<32;bit++) {
            ans += to_string(num & 1);
            num >>= 1;
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
    void insert(int num){
        Node* cur = root;
        string s = to_bin(num);
        for(auto e : s){
            int idx = e - '0';
            if(!cur->child[idx])cur->child[idx]= new Node();
            cur = cur->child[idx];
            cur->prefix++;
        }
        cur->ends++;
    }
    void erase(int num){
        Node* cur = root;
        string s = to_bin(num);
        stack<Node*>st;
        for(auto e : s){
            int idx = e - '0';
            if(!cur->child[idx])return;
            cur = cur->child[idx];
            cur->prefix--;
            st.push(cur);
        }
        cur->ends--;
    }
    int countWord(int num){
        Node* cur = root;
        string s = to_bin(num);
        for(auto e : s){
            int idx = e - '0';
            if(!cur->child[idx])return 0;
            cur = cur->child[idx];
        }

        return cur->ends;
    }
    int countPrefix(int num){
        Node* cur = root;
        string s = to_bin(num);
        for(auto e : s){
            int idx = e - '0';
            if(!cur->child[idx])return 0;
            cur = cur->child[idx];
        }
        return cur->prefix;
    }
    int mx(int num){
        int ans = 0;
        Node* cur = root;
        string x = to_bin(num);
        for(int idx=0;idx<x.size();idx++) {
            if (x[idx] == '1') {
                if (cur->child[0]) {
                    cur = cur->child[0];
                    ans |= 1 << (32-idx-1);
                } else if (cur->child[1]) {
                    cur = cur->child[1];
                }
            }
            else {
                if (cur->child[1]) {
                    cur = cur->child[1];
                    ans |= 1 << (32-idx-1);
                } else if (cur->child[0]) {
                    cur = cur->child[0];
                }
            }
        }
        return ans;
    }
};