ll hilbertOrder(ll x, ll y, ll pow = 21, ll rot = 0) {
    if (pow == 0) return 0;

    ll hpow = 1 << (pow - 1);
    ll seg = (x < hpow) ? ((y < hpow) ? 0 : 3)
                     : ((y < hpow) ? 1 : 2);

    seg = (seg + rot) & 3;
    const ll rotateDelta[4] = {3, 0, 0, 1};
    ll nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    ll nrot = (rot + rotateDelta[seg]) & 3;

    ll subSquareSize = 1LL << (2 * pow - 2);
    ll ord = seg * subSquareSize;

    ll add = hilbertOrder(nx, ny, pow - 1, nrot);
    ord += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);

    return ord;
}

struct Query {
    ll l, r, id;
    ll ord;

    void calcOrder() {
        ord = hilbertOrder(l, r);
    }
};

bool cmp(const Query &a, const Query &b) {
    return a.ord < b.ord;
}

const ll MAXN = 200005;
ll A[MAXN];
ll ans[MAXN];

ll freq[1000005];
ll current_answer = 0;

// ------------ ADD / REMOVE FUNCTIONS ------------

void add(ll idx) {
    ll x = A[idx];
    // Example: number of distinct elements
    if (freq[x] == 0) current_answer++;
    freq[x]++;
}

void remove_(ll idx) {
    ll x = A[idx];
    freq[x]--;
    if (freq[x] == 0) current_answer--;
}

// ------------ Example MAIN ------------
// ll main() {
// 	ll n, q;
// 	cin >> n >> q;
// 	for (ll i = 0; i < n; i++)
// 		cin >> A[i];
// 	vector<Query> queries(q);
// 	for (ll i = 0; i < q; i++) {
// 		cin >> queries[i].l >> queries[i].r;
// 		queries[i].l--;  // convert to 0-based
// 		queries[i].r--;
// 		queries[i].id = i;
// 		queries[i].calcOrder();
// 	}
// 	sort(queries.begin(), queries.end(), cmp);
// 	ll curL = 0, curR = -1;
// 	for (auto &qu : queries) {
// 		while (curL > qu.l) add(--curL);
// 		while (curR < qu.r) add(++curR);
// 		while (curL < qu.l) remove_(curL++);
// 		while (curR > qu.r) remove_(curR--);
//
// 		ans[qu.id] = current_answer;
// 	}
// 	for (ll i = 0; i < q; i++)
// 		cout << ans[i] << "\n";
// 	return 0;
// }