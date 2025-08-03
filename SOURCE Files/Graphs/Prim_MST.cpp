vb visited;
vl min_edge, parent;

ll prim(ll n, vector<vector<pii>> &adj) {
	visited.assign(n+1, false);
	min_edge.assign(n+1, LLONG_MIN);
	parent.assign(n+1, -1);

	ll total_weight = 0;
	priority_queue<pii, vector<pii>, greater<>> pq;

	min_edge[0] = 0;        // Change for 1-based indexing
	pq.push({0, 0});        // {weight, node}

	while (!pq.empty())
    {
		auto [w, u] = pq.top();
        pq.pop();
		if(visited[u])
            continue;

		visited[u] = true;
		total_weight += w;

		for (auto [v, weight] : adj[u])
        {
			if (!visited[v] && weight < min_edge[v])
            {
				min_edge[v] = weight;
				parent[v] = u;
				pq.push({weight, v});
			}
		}
	}
	return total_weight;
}