struct HLD {
    ll n, cur_pos = 0;
    vector<vector<ll>> g;
    vector<ll> parent, depth, heavy, head, pos, sz;
    vector<ll> value; // node values

    HLD(ll n) : n(n), g(n), parent(n), depth(n),
             heavy(n, -1), head(n), pos(n), sz(n), value(n) {}

    void addEdge(ll u, ll v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll dfs(ll u, ll p) {
        parent[u] = p;
        sz[u] = 1;
        ll max_sz = 0;

        for (ll v : g[u]) if (v != p) {
            depth[v] = depth[u] + 1;
            ll sub = dfs(v, u);
            sz[u] += sub;
            if (sub > max_sz) {
                max_sz = sub;
                heavy[u] = v;
            }
        }
        return sz[u];
    }

    void decompose(ll u, ll h) {
        head[u] = h;
        pos[u] = cur_pos++;

        if (heavy[u] != -1)
            decompose(heavy[u], h);

        for (ll v : g[u]) {
            if (v != parent[u] && v != heavy[u])
                decompose(v, v);
        }
    }

    void init(ll root = 0) {
        dfs(root, -1);
        decompose(root, root);
    }
};

// ll n;
// cin >> n;

// HLD hld(n);

// //  If Nodes had Values
// {
// 	for (ll i = 0; i < n; i++)
// 		cin >> hld.value[i];

// 	for (ll i = 0; i < n-1; i++) {
// 		ll u, v;
// 		cin >> u >> v;
// 		--u; --v;
// 		hld.addEdge(u, v);
// 	}

// 	hld.init(0);  // assuming root = 0

// //  If Edges had Values
// {
// 	vector<Edge> edges(n - 1);
// 	for (ll i = 0; i < n - 1; i++) {
// 		ll u, v;
// 		ll w;
// 		cin >> u >> v >> w;
// 		--u; --v;
// 		edges[i] = {u, v, w};
// 		hld.addEdge(u, v);
// 	}

// 	hld.init(0);  // assuming root = 0

// 	// Initialize all node values to 0
// 	for (ll i = 0; i < n; i++) {
// 		hld.value[i] = 0;
// 	}

// 	// Assign edge weights to the deeper node
// 	for (auto &e : edges) {
// 		ll u = e.u, v = e.v;
// 		ll w = e.w;

// 		if (hld.depth[u] > hld.depth[v])
// 			swap(u, v);  // Now v is deeper

// 		hld.value[v] = w;
// 	}
// }

// 	Build base array
// 	vector<ll> base(n);
// 	for (ll i = 0; i < n; i++) {
// 		base[hld.pos[i]] = hld.value[i];
// }

// SegTree seg(base);

void update_node(ll u, ll new_val, HLD &hld, SegmentTree &seg) {
    hld.value[u] = new_val;
    seg.update(hld.pos[u], new_val);
}
void update_edge(ll u, ll v, ll new_val, HLD &hld, SegmentTree &seg) {
    if (hld.depth[u] > hld.depth[v]) 
        swap(u, v);  // now v is deeper node

    // Update the value at the deeper node v
    hld.value[v] = new_val;

    // Update the segment tree at position pos[v]
    seg.update(hld.pos[v], new_val);
}

void update_path(ll u, ll v, ll new_val, HLD &hld, SegmentTree &seg) {
    while (hld.head[u] != hld.head[v]) {
        if (hld.depth[hld.head[u]] < hld.depth[hld.head[v]])
            swap(u, v);
        ll top = hld.head[u];
        seg.update(hld.pos[top], hld.pos[u], new_val); // range set on segment tree
        u = hld.parent[top];
    }
    if (hld.depth[u] > hld.depth[v]) swap(u, v);
    seg.update(hld.pos[u], hld.pos[v], new_val);
}
ll query_path(ll a, ll b, HLD &hld, SegTree &seg) {
    ll res = 0;

    while (hld.head[a] != hld.head[b]) {
        if (hld.depth[hld.head[a]] < hld.depth[hld.head[b]])
            swap(a, b);

        ll top = hld.head[a];
        res += seg.query(hld.pos[top], hld.pos[a]);
        a = hld.parent[top];
    }

    if (hld.depth[a] > hld.depth[b])
        swap(a, b);

    // If nodes have values
    res += seg.query(hld.pos[a], hld.pos[b]);

    // If edges have values
    //res += seg.query(hld.pos[a] + 1, hld.pos[b]);

    return res;
}