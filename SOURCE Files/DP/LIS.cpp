pair<ll,vl> lis(const vl &a) {
    ll n = a.size();
    vl d, idx(n), parent(n, -1);

    fori(0,n)
    {
        auto it = lower_bound(d.begin(), d.end(), a[i]);
        ll j = it - d.begin();

        if(it == d.end())
            d.push_back(a[i]);
        else
            *it = a[i];

        idx[j] = i;
        if(j > 0)
            parent[i] = idx[j - 1];
    }

    // Reconstruct LIS
    vl lis_seq;
    for(ll i = idx[d.size() - 1]; i >= 0; i = parent[i])
        lis_seq.push_back(a[i]);

    reverse(all(lis_seq));
    return {d.size(), lis_seq};
}