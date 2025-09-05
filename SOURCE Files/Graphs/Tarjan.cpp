struct Tarjan {
    ll n, timer;
    vll adj;
    vl tin, low, isArticulation;
    vpii bridges;

    Tarjan(ll n) : n(n) {
        adj.assign(n, {});
        tin.assign(n, -1);
        low.assign(n, -1);
        isArticulation.assign(n, 0);
        timer = 0;
    }

    void add_edge(ll u, ll v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    void dfs(ll v, ll p = -1) {
        tin[v] = low[v] = timer++;
        ll children = 0;

        for (ll u : adj[v])
        {
            if(u==p)
                continue;

            if(tin[u] != -1)
            {
                // back edge
                low[v] = min(low[v], tin[u]);
            }
            else
            {
                // tree edge
                dfs(u, v);

                low[v] = min(low[v], low[u]);

                if (low[u] > tin[v])
                {
                    // v-u is a bridge
                    bridges.push_back({v, u});
                }
                if(low[u] >= tin[v] && p != -1)
                {
                    // v is an articulation point (not root)
                    isArticulation[v] = 1;
                }
                children++;
            }
        }

        if (p==-1 && children>1)
        {
            // root articulation point
            isArticulation[v] = 1;
        }
    }

    void run() {
        fori(0,n)
        {
            if (tin[i] == -1)
                dfs(i);
        }
    }
};