struct Edge {
    ll to, rev;
    ll cap, cost;
    Edge(ll to, ll rev, ll cap, ll cost) : to(to), rev(rev), cap(cap), cost(cost) {}
};

struct MinCostMaxFlow {
    ll n;
    vector<vector<Edge>> adj;
    vl dist, potential, parentNode, parentEdge;
    const ll INF = 1e15;

    MinCostMaxFlow(ll n) : n(n) {
        adj.assign(n, vector<Edge>());
        dist.assign(n, INF);
        potential.assign(n, 0);
        parentNode.assign(n, -1);
        parentEdge.assign(n, -1);
    }

    void add_edge(ll u, ll v, ll cap, ll cost) {
        adj[u].emplace_back(v, (ll)adj[v].size(), cap, cost);
        adj[v].emplace_back(u, (ll)adj[u].size() - 1, 0, -cost);
    }

    bool bellman_ford(ll s) {
        fill(potential.begin(), potential.end(), INF);
        potential[s] = 0;
        bool updated;
        for (ll iter = 0; iter < n - 1; iter++) {
            updated = false;
            for (ll u = 0; u < n; u++) {
                if (potential[u] == INF) continue;
                for (auto &e : adj[u]) {
                    if (e.cap > 0 && potential[u] + e.cost < potential[e.to]) {
                        potential[e.to] = potential[u] + e.cost;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
        // Optional: check for negative cycle here if needed.
        return true;
    }

    bool dijkstra(ll s, ll t) {
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;

        using pli = pair<ll, ll>;
        priority_queue<pli, vector<pli>, greater<pli>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            if (u == t) return true;

            for (ll i = 0; i < (ll)adj[u].size(); i++) {
                Edge &e = adj[u][i];
                if (e.cap > 0) {
                    ll cost_with_pot = e.cost + potential[u] - potential[e.to];
                    if (dist[u] + cost_with_pot < dist[e.to]) {
                        dist[e.to] = dist[u] + cost_with_pot;
                        parentNode[e.to] = u;
                        parentEdge[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
        }
        return false;
    }

    pii min_cost_max_flow(ll s, ll t) {
        ll flow = 0, cost = 0;

        // If Negative Costs Run Bellman-Ford once to properly Initialize Potentials for Dijkstra
        // bellman_ford(s);

        // If Positive Costs Initializing Potentials Zero for Dijkstra
        fill(potential.begin(), potential.end(), 0);

        while (dijkstra(s, t)) {
            for (ll i = 0; i < n; i++) {
                if (dist[i] < INF)
                    potential[i] += dist[i];
            }

            ll pushed = LLONG_MAX;
            for (ll v = t; v != s; v = parentNode[v]) {
                ll u = parentNode[v];
                ll idx = parentEdge[v];
                pushed = min(pushed, adj[u][idx].cap);
            }

            for (ll v = t; v != s; v = parentNode[v]) {
                ll u = parentNode[v];
                ll idx = parentEdge[v];
                adj[u][idx].cap -= pushed;
                adj[v][adj[u][idx].rev].cap += pushed;
                cost += pushed * adj[u][idx].cost;
            }

            flow += pushed;
        }
        return {flow, cost};
    }
};