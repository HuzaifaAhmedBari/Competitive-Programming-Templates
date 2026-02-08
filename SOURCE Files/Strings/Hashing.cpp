using ull = unsigned long long;

ll gen_base(ll l = 257) {
    auto t = chrono::steady_clock::now().time_since_epoch().count();
    mt19937_64 r(t);
    return (l + r() % (ll)(1e9 - l)) | 1;
}

struct PolyHash {
    static const ll M = 1000000007;
    ll n;
    vector<ll> h, p;
    vector<ull> H, P;

    PolyHash(string s, ll b = 0) : n(s.size()) {
        if (!b) b = gen_base();
        h.resize(n + 1);
        p.assign(n + 1, 1);
        H.resize(n + 1);
        P.assign(n + 1, 1);
        for (ll i = 0; i < n; ++i) {
            h[i + 1] = (1LL * h[i] * b + (unsigned char)s[i]) % M;
            p[i + 1] = 1LL * p[i] * b % M;
            H[i + 1] = H[i] * b + (unsigned char)s[i];
            P[i + 1] = P[i] * b;
        }
    }

    // get hash of substring [l, l+len)
    pair<ll, ull> get(ll l, ll len) {
        ll r = l + len;
        ll v = (h[r] - 1LL * h[l] * p[len] % M + M) % M;
        return {v, H[r] - H[l] * P[len]};
    }

    // get hash of string excluding range [L, R]
    pair<ll, ull> exclude(ll L, ll R) {
        if (!n) return {0, 0};
        L = max(0LL, L);
        R = min(n - 1, R);
        if (L > R) return get(0, n);
        auto x = get(0, L);
        auto y = get(R + 1, n - 1 - R);
        ll v = (1LL * x.first * p[n - 1 - R] + y.first) % M;
        return {v, x.second * P[n - 1 - R] + y.second};
    }
};