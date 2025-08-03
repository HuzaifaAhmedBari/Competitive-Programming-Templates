class DSU {
private:
    ll n, components;
    vl parent, size;

public:
    DSU(int n) : n(n), components(n) {
        parent.resize(n+1);
        size.resize(n+1, 1);
        iota(all(parent),1);
    }

    ll find(ll x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(ll a, ll b) {
        a = find(a);
        b = find(b);
        if(a==b)
            return false;

        if(size[a] < size[b])
            swap(a,b);
        parent[b] = a;
        size[a] += size[b];
        components--;
        return true;
    }

    bool connected(ll a, ll b) {
        return find(a) == find(b);
    }

    ll getSize(ll x) {
        return size[find(x)];
    }
};