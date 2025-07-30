/*
 * z(i) denotes the maximum length of a substring that begins at position i and is a prefix of the string. In addition, z(1)=0.
 * pi(i) denotes the maximum length of a substring that ends at position i, is a prefix of the string, and whose length is at most i-1
 */
vector<int> pi_function(string s){
    // PI[i] is the longest suffix from i that is a prefix of s

    vector<int>pi(s.size());

    pi[0] = 0;
    for(int i =1;i<s.size();i++){
        int l = pi[i-1];
        while (s[l] != s[i] and l){
            l = pi[l-1];
        }
        if(s[l] == s[i])
            pi[i] = l+1;
    }
    return pi;

}

vector<int> kmpSearch(const string& str, const string& ptr) {
    vector<int> pi = pi_function(ptr);

    int i =0,j=0;
    vector<int>idc;
    while (i < str.size()){
        while (str[i] != ptr[j] and j){
            j = pi[j-1];
        }
        if(str[i] == ptr[j])j++;
        if(j == ptr.size()){
            idc.push_back(i+1 -j);
            j = pi[j-1];
        }
        i++;
    }
    return idc;
}
