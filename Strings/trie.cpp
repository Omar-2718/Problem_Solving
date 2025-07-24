struct Trie{

    struct Node{
        // lower case
        Node* child[26];
        int ends,prefix;
        Node(){
            memset(child,0,sizeof child);
            ends = prefix = 0;
        }
    };
    Node *root = new Node();
    void insert(string &s){
        Node* cur = root;
        for(auto e : s){
            int idx = e - 'a';
            if(!cur->child[idx])cur->child[idx]= new Node();
            cur = cur->child[idx];
            cur->prefix++;
        }
        cur->ends++;
    }
    int countWord(string &s){
        Node* cur = root;
        for(auto e : s){
            int idx = e - 'a';
            if(!cur->child[idx])return 0;
            cur = cur->child[idx];
        }
        return cur->ends;
    }
    int countPrefix(string &s){
        Node* cur = root;
        for(auto e : s){
            int idx = e - 'a';
            if(!cur->child[idx])return 0;
            cur = cur->child[idx];
        }
        return cur->prefix;
    }
};