struct Edge {
    ll to, rev;
    ll cap;
    Edge(ll to, ll rev, ll cap) : to(to), rev(rev), cap(cap) {}
};

struct Dinic {
    ll n;
    vector<vector<Edge>> adj;
    vl level, ptr;

    Dinic(ll n) : n(n) {
        adj.assign(n, vector<Edge>());
        level.assign(n, -1);
        ptr.assign(n, 0);
    }

    void add_edge(ll u, ll v, ll cap) {
        adj[u].emplace_back(v, (ll)adj[v].size(), cap);
        adj[v].emplace_back(u, (ll)adj[u].size() - 1, 0); // reverse edge
    }

    void print_all_edges() {
        for (ll u = 0; u < n; u++) {
            for (ll i = 0; i < (ll)adj[u].size(); i++) {
                Edge &e = adj[u][i];

                bool is_backward = false;
                is_backward = (adj[e.to][e.rev].to == u) && (i % 2 == 1);

                cout << "Edge from " << u << " to " << e.to 
                    << " | cap = " << e.cap
                    << " | " << (is_backward ? "Backward edge" : "Forward edge") << "\n";
            }
        }
    }

    bool bfs(ll s, ll t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<ll> q; q.push(s);
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    ll dfs(ll u, ll t, ll flow) {
        if (u == t || flow == 0) return flow;
        for (ll &i = ptr[u]; i < (ll)adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (level[e.to] == level[u] + 1 && e.cap > 0) {
                ll pushed = dfs(e.to, t, min(flow, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    adj[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }

    vb min_cut_reachable(ll s) {
        vb visited(n, false);
        queue<ll> q; q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap > 0 && !visited[e.to]) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return visited;
    }

    vpii get_min_cut_edges(ll s) {
        vpii cut_edges;
        vb visited = min_cut_reachable(s);

        for (ll u = 0; u < n; u++) {
            if (visited[u]) {
                for (auto &e : adj[u]) {
                    if (!visited[e.to] && e.cap == 0) {
                        cut_edges.emplace_back(u, e.to);
                    }
                }
            }
        }
        return cut_edges;
    }
};