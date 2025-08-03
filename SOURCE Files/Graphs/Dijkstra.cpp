vl parent;
vl dijkstra(ll n, ll source, vvpii &adj)
{
    vl dist(n+1, LLONG_MAX);
    parent.assign(n, -1); // For path reconstruction
    dist[source] = 0;

    priority_queue<pii, vpii, greater<>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u])
            continue;

        for (auto [v, w] : adj[u])
        {
            if(dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
