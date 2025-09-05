// 0/1 Knapsack (Space Optimized)
// n = number of items
// W = maximum capacity
// wt[i] = weight of item i
// val[i] = value of item i
ll knapsack(const vl &wt, const vl &val, ll W) {
    ll n = wt.size();
    vl dp(W + 1, 0);

    fori(0,n)
    {
        for(ll w = W; w >= wt[i]; w--)
        {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }
    return dp[W];
}