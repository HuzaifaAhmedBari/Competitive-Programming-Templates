pair<ll, string> lcs(const string &a, const string &b) {
	ll n = a.size(), m = b.size();
	vll dp(n+1,vl(m+1, 0));

	// Build DP table
	fori(1,n+1)
    {
		forj(1,m+1)
        {
			if(a[i-1] == b[j-1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	// Reconstruct LCS string
	string lcs_str;
	ll i = n, j = m;
	while(i > 0 && j > 0)
    {
		if (a[i - 1] == b[j - 1])
        {
			lcs_str.push_back(a[i - 1]);
			i--;
            j--;
		}
        else if(dp[i - 1][j] >= dp[i][j - 1])
        {
			i--;
        }
		else
        {
			j--;
		}
	}
	reverse(all(lcs_str));

	return {dp[n][m], lcs_str};
}