const int N = 3e5 + 9;
const int LG = 18;

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
        // change me HELLO
        P[0][j] = s[j] - 'A';
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
struct SuffixArray {
    int n;
    string s;
    vector<int> sa, rank, lcp;
    vector<vector<int>> t;
    vector<int> lg;
    SuffixArray() {}
    SuffixArray(string _s) {
        n = _s.size();
        s = _s;
        sa = build_suffix_array(s);
        rank.resize(n);
        for (int i = 0; i < n; i++) rank[sa[i]] = i;
        costruct_lcp();
        prec();
        build();
    }
    void costruct_lcp() {
        int k = 0;
        lcp.resize(n - 1, 0);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])  k++;
            lcp[rank[i]] = k;
            if (k)  k--;
        }
    }
    void prec() {
        lg.resize(n, 0);
        for (int i = 2; i < n; i++) lg[i] = lg[i / 2] + 1;
    }
    void build() {
        int sz = n - 1;
        t.resize(sz);
        for (int i = 0; i < sz; i++) {
            t[i].resize(LG);
            t[i][0] = lcp[i];
        }
        for (int k = 1; k < LG; ++k) {
            for (int i = 0; i + (1 << k) - 1 < sz; ++i) {
                t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    int query(int l, int r) { // minimum of lcp[l], ..., lcp[r]
        int k = lg[r - l + 1];
        return min(t[l][k], t[r - (1 << k) + 1][k]);
    }
    int get_lcp(int i, int j) { // lcp of suffix starting from i and j
        if (i == j) return n - i;
        int l = rank[i], r = rank[j];
        if (l > r) swap(l, r);
        return query(l, r - 1);
    }
    int lower_bound(string &t) {
        int l = 0, r = n - 1, k = t.size(), ans = n;
        while (l <= r) {
            int mid = l + r >> 1;
            if (s.substr(sa[mid], min(n - sa[mid], k)) >= t) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }
    int upper_bound(string &t) {
        int l = 0, r = n - 1, k = t.size(), ans = n;
        while (l <= r) {
            int mid = l + r >> 1;
            if (s.substr(sa[mid], min(n - sa[mid], k)) > t) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }
    // occurrences of s[p, ..., p + len - 1]
    pair<int, int> find_occurrence(int p, int len) {
        p = rank[p];
        pair<int, int> ans = {p, p};
        int l = 0, r = p - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(mid, p - 1) >= len) ans.first = mid, r = mid - 1;
            else l = mid + 1;
        }
        l = p + 1, r = n - 1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (query(p, mid - 1) >= len) ans.second = mid, l = mid + 1;
            else r = mid - 1;
        }
        return ans;
    }

};