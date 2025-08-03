vl topo, dist;
bool topsort(ll n, ll source, const vll &adj) {
    ll count = 0;
    vl indegree(n+1, 0);
    dist.assign(n+1, LLONG_MIN);
    dist[source] = 0;

    for(ll u = 0; u < n; u++)       // change for 1 based indexing
        for (int v : adj[u])
            indegree[v]++;

    queue<ll> q;
    for (int i = 0; i < n; ++i)       // change for 1 based indexing
        if (indegree[i] == 0)
            q.push(i);

    while (not q.empty())
    {
        ll u = q.front();
        q.pop();

        for (ll v : adj[u]) {
            // if(dist[u] != LLONG_MIN)
            //     dist[v] = max(dist[v], dist[u] + 1);       // +1 for unweighted edge change for weighted DAG

            if (--indegree[v] == 0)
                q.push(v);
        }
        count++;
    }
    return count != n;        // True means cycle exists
}
