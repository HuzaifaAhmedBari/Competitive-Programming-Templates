struct HopcroftKarp {
    ll n, m;                // n = size of left set, m = size of right set
    vll adj;                // adjacency list from left to right
    vl dist, matchL, matchR;

    HopcroftKarp(ll n, ll m) : n(n), m(m) {
        adj.resize(n);
        dist.resize(n);
        matchL.assign(n, -1);
        matchR.assign(m, -1);
    }

    void addEdge(ll u, ll v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<ll> q;
        for (ll u = 0; u < n; u++) {
            if (matchL[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INT_MAX;
            }
        }

        bool found = false;

        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (ll v : adj[u]) {
                ll w = matchR[v];
                if (w == -1) {
                    found = true;
                } else if (w != -1 && dist[w] == INT_MAX) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }
        return found;
    }

    bool dfs(ll u) {
        for (ll v : adj[u]) {
            ll w = matchR[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = INT_MAX;
        return false;
    }

    ll maxMatching() {
        ll matching = 0;
        while (bfs()) {
            for (ll u = 0; u < n; u++) {
                if (matchL[u] == -1 && dfs(u))
                    matching++;
            }
        }
        return matching;
    }
};