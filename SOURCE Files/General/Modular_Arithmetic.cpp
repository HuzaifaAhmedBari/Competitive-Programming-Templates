const int mod = 1000000007;
template<int M> struct modint {
    int v;
    modint(long long x = 0) : v(x % M) { if (v < 0) v += M; }
    modint& operator+=(const modint& o) { if ((v += o.v) >= M) v -= M; return *this; }
    modint& operator-=(const modint& o) { if ((v -= o.v) < 0) v += M; return *this; }
    modint& operator*=(const modint& o) { v = 1LL * v * o.v % M; return *this; }
    modint& operator/=(const modint& o) { return *this *= o.inv(); }
    modint operator-() const { return modint() - *this; }
    modint pow(long long k) const {
        modint r = 1, x = *this;
        for (; k; k >>= 1) { if (k & 1) r *= x; x *= x; }
        return r;
    }
    modint inv() const { return pow(M - 2); }
    friend modint operator+(modint a, const modint& b) { return a += b; }
    friend modint operator-(modint a, const modint& b) { return a -= b; }
    friend modint operator*(modint a, const modint& b) { return a *= b; }
    friend modint operator/(modint a, const modint& b) { return a /= b; }
    friend bool operator==(const modint& a, const modint& b) { return a.v == b.v; }
    friend bool operator!=(const modint& a, const modint& b) { return a.v != b.v; }
    friend bool operator<(const modint& a, const modint& b) { return a.v < b.v; }
    friend istream& operator>>(istream& i, modint& m) { long long x; i >> x; m = x; return i; }
    friend ostream& operator<<(ostream& o, const modint& m) { return o << m.v; }
};
using mint = modint<mod>;