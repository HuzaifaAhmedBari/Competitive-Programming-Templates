vl topo, dist;
bool topsort(ll n, const vll &adj, ll source = 0) {
    ll count = 0;
    vl indegree(n+1, 0);
    dist.assign(n+1, LLONG_MIN);
    dist[source] = 0;

    for(ll u = 0; u < n; u++)       // change for 1 based indexing
        for (int v : adj[u])
            indegree[v]++;

    queue<ll> q;
    fori(0,n)       // change for 1 based indexing
        if(indegree[i]==0)
            q.push(i);

    while (not q.empty())
    {
        ll u = q.front();
        q.pop();
        topo.push_back(u);

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
