struct ranking {
    int index;
    int first;
    int second;
};
vector<ranking> ranks;

// P[i][j] holds the ranking of the j-th suffix
// after comparing the first 2^i characters
// of that suffix
int P[20][1000000];

bool comp(ranking a, ranking b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}
vector<int> build_suffix_array(string s) {
    const int n = s.length();
    const int lgn = ceil(log2(n));
    ranks.assign(n,{});
    // vector to hold final suffix array result
    vector<int> sa(n);

    // vector to store ranking tuples of suffixes

    int i, j, step = 1;
    for(j = 0; j < n; j++) {
        P[0][j] = s[j] - 'a';
    }

    for(i = 1; i <= lgn; i++, step++) {
        for(j = 0; j < n; j++) {
            ranks[j].index = j;
            ranks[j].first = P[i-1][j];
            ranks[j].second = (j + pow(2,i-1) < n) ? P[i-1][j + (int)(pow(2,i-1))] : -1;
        }

        sort(ranks.begin(), ranks.end(), comp);

        for(j = 0; j < n; j++) {
            P[i][ranks[j].index] = (j > 0 && ranks[j].first == ranks[j-1].first && ranks[j].second == ranks[j-1].second) ? P[i][ranks[j-1].index] : j;
        }
    }

    step -= 1;

    for(i = 0; i < n; i++) {
        sa[P[step][i]] = i;
    }

    return sa;
}

vector<int> build_lcp(vector<int> &sa, int n) {

    vector<int> lcp(n,0);
    int k, i, j , x, delta, step = ceil(log2(n));
    for (k = 1; k < n; k++) {
        i = k;
        j = k - 1;
        for (x = step; x >= 0; x--) {
            if (P[x][sa[i]] == P[x][sa[j]]) {
                delta = pow(2,x);
                lcp[i] += delta;
                i += delta;
                j += delta;
            }
        }
    }
    return lcp;
}
