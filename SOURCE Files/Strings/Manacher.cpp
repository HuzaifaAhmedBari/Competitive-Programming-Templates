// 0 is even, 1 is odd
array<vector<ll>, 2> manacher(const string &s) {
    ll n = s.size();
    array<vector<ll>, 2> p = {vector<ll>(n + 1), vector<ll>(n)};
    for (ll z = 0; z < 2; ++z)
        for (ll i = 0, l = 0, r = 0; i < n; i++) {
            ll t = r - i + !z;
            if (i < r) p[z][i] = min(t, p[z][l + t]);
            ll L = i - p[z][i], R = i + p[z][i] - !z;
            while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r) l = L, r = R;
        }
    return p;
}