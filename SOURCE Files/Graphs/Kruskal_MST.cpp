struct Edge {
    ll u, v, w;
    bool operator<(const Edge &e) const {
        return w < e.w;
    }
};

ll kruskal(ll n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll total_weight = 0;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total_weight += e.w;
            // store edge (e.u, e.v) if needed
        }
    }
    return total_weight;
}