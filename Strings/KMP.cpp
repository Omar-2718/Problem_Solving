vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> pi = buildPi(pattern);
    vector<int> matchPositions;

    int n = text.size();
    int m = pattern.size();
    int j = 0;  // index for pattern

    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];

        if (text[i] == pattern[j])
            j++;

        if (j == m) {
            matchPositions.push_back(i - m + 1); // match found
            j = pi[j - 1]; // prepare for next possible match
        }
    }

    return matchPositions;
}
