// Precompute factorials and inverse factorials for nCr and nPr
const ll MoD = 1e9+7;
vl fact, invfact;

ll modpow(ll a, ll b, ll m = MoD) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

void build_fact(ll n) {
    fact.assign(n+1, 1);
    invfact.assign(n+1, 1);

    for (ll i = 1; i <= n; i++)
        fact[i] = (fact[i-1] * i) % MoD;

    invfact[n] = modpow(fact[n], MoD-2, MoD); // Fermat's inverse

    for (ll i = n-1; i >= 0; i--)
        invfact[i] = (invfact[i+1] * (i+1)) % MoD;
}

ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return (((fact[n] * invfact[r]) % MoD) * invfact[n-r]) % MoD;
}

ll nPr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return (fact[n] * invfact[n-r]) % MoD;
}