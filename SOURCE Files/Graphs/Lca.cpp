struct LCA {
    ll n;
    vl depth;
    vll adj, up;
    const ll LOG = 20;

    LCA(ll nodes) : n(nodes) {
        adj.assign(n, vl());
        depth.assign(n, 0);
        up.assign(n, vl(LOG, -1));
    }

    void add_edge(ll u, ll v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(ll u, ll p) {
        up[u][0] = p;
        fori(1, LOG) {
            if (up[u][i-1] == -1)
                up[u][i] = -1;
            else
                up[u][i] = up[up[u][i-1]][i-1];
        }
        for (ll v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    void init(ll root = 0) {
        depth[root] = 0;
        dfs(root, -1);
    }

    ll lift_node(ll u, ll k) {
        fori(0, LOG) {
            if (k & (1LL << i)) {
                if (u == -1) return -1;
                u = up[u][i];
            }
        }
        return u;
    }

    ll lca(ll u, ll v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = lift_node(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (ll i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
};