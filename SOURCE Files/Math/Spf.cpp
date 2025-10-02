vl spf;
void build_spf(ll n) {
    spf.assign(n + 1, 0);
    iota(spf.begin(), spf.end(), 0LL);
    for (ll i = 2; i * i <= n; i++) {
        if (spf[i] == i) {
            for (ll j = i * i; j <= n; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

vl factorize(ll x) {
    vl factors;
    while (x > 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }
    return factors;
}
