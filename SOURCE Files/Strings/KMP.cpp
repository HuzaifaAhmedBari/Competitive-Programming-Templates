vl build_lps(const string &pat) {
    ll m = pat.size();
    vl lps(m, 0);

    for (ll i = 1, len = 0; i < m; ) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
    }
    return lps;
}

vl kmp(const string &text, const string &pat) {
    ll n = text.size(), m = pat.size();
    vl lps = build_lps(pat);
    vl occurrences;

    for (ll i = 0, j = 0; i < n; ) {
        if (text[i] == pat[j]) {
            i++; j++;
        }

        if (j == m) {
            occurrences.push_back(i - j); // match found (0-based index)
            j = lps[j - 1];
        } else if (i < n && text[i] != pat[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return occurrences;
}