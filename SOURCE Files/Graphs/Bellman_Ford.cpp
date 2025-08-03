vl dist, parent, cycle;

struct Edge {
	ll u, v, w;
};

bool bellman_ford(ll n, ll source, const vector<Edge> &edges) {
	dist.assign(n+1, LLONG_MIN);
	parent.assign(n+1, -1);
	dist[source] = 0;

	for(ll i = 0; i < n - 1; ++i)
    {
		for (const Edge &e : edges)
        {
			if (dist[e.u] < LLONG_MIN && dist[e.u] + e.w < dist[e.v]) {
				dist[e.v] = dist[e.u] + e.w;
				parent[e.v] = e.u;
			}
		}
	}

	// Detect negative cycle
	for (const Edge &e : edges)
    {
		if (dist[e.u] < LLONG_MIN && dist[e.u] + e.w < dist[e.v]) {
			return false; // Negative cycle found
		}
	}

	return true; // No negative cycle
}

// Get path from source to target (only if no negative cycle)
vl get_path(ll target) {
	vl path;
	for (ll v = target; v != -1; v = parent[v])
		path.push_back(v);
	reverse(path.begin(), path.end());
    
	return path;
}

bool find_negative_cycle(ll n, const vector<Edge> &edges) {
	ll x = -1;

	for (const Edge &e : edges)
    {
		if (dist[e.u] + e.w < dist[e.v])
        {
			dist[e.v] = dist[e.u] + e.w;
			parent[e.v] = e.u;
			x = e.v;
		}
	}

	if (x == -1)
		return false; // No negative cycle

	// Recover the cycle
	for (ll i = 0; i < n; ++i)
		x = parent[x]; // x is guaranteed to be inside the cycle

	ll cur = x;
	cycle.push_back(cur);
	while (true)
    {
		cur = parent[cur];
		cycle.push_back(cur);
		if (cur == x && cycle.size() > 1)
			break;
	}
	reverse(cycle.begin(), cycle.end());
	return true;
}