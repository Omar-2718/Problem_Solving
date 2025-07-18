vector<int> pi_function(string s){
    // PI[i] is the longest suffix from i that is a prefix of s

    vector<int>pi(s.size());

    // [s0 s1 s2 s3] s4 ... si-4 [si-3 si-2  si-1  si] si+1

    // l is current length that match which is 4
    // l = pi[i]
    // if s[l] = si+1 then i can add si+1
    // so pi[i+1] = p[i] + 1

    // A
    // but what if they arent equal ?
    // well in that case i can take a suffix of the substring
    // and append si+1 but that suffix has to also be a prefix in s
    // for example [s0 s1] s1 ....  [si-1 si] si+1
    // ok so i want the next largest suffix of i that is a prefix of itself
    // but wait remember that its equal to the start [s0 s1 s2 s3]

    // ok so i want the next largest suffix of i that is a prefix of s
    // that is just normal pi
    // l = pi[l-1]  l-1 because that is the index
    // so that is pi[3]

    // now my next biggest suffix length if pi[3]
    // if pi[l] = si+1 then this is the answer if not
    // then do A again
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
