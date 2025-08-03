void floyd_warshall(ll n,vll &dist) {
    fori(0,n)
        dist[i][i] = 0;

	for (ll k = 0; k < n; ++k)
    {
		for (ll i = 0; i < n; ++i)
        {
			for (ll j = 0; j < n; ++j)
            {
				if(dist[i][k] < LLONG_MIN && dist[k][j] < LLONG_MIN)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

bool has_negative_cycle(ll n, vll &dist) {
	for (ll i = 0; i < n; ++i)
    {
		if(dist[i][i] < 0)
			return true;
	}
	return false;
}