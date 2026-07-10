struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n = 0) {
        init(n);
    }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    // add delta at index i (0-based)
    void update(int i, long long delta) {
        for (++i; i <= n; i += i & -i)
            bit[i] += delta;
    }

    // prefix sum [0..i]
    long long query(int i) {
        long long s = 0;
        for (++i; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    // sum in [l..r]
    long long rangeQuery(int l, int r) {
        if (l > r) return 0;
        return query(r) - (l ? query(l - 1) : 0);
    }

    // find smallest index with prefix sum >= k
    // assumes all frequencies are non-negative
    int kth(long long k) {
        int pos = 0;
        long long sum = 0;
        int logn = 31 - __builtin_clz(n);
        for (int i = 1 << logn; i > 0; i >>= 1) {
            if (pos + i <= n && sum + bit[pos + i] < k) {
                sum += bit[pos + i];
                pos += i;
            }
        }
        return pos; // 0-based index
    }
};