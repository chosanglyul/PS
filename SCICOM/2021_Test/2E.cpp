#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 505050;
const int P = 100003;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T1, typename T2>
void addo(pair<T1, T2>& L, const pair<T1, T2>& R) { L.fi += R.fi; L.se += R.se; }
int mod(ll a, int b) { return ((a%b) + b) % b; }
int mod(ll a) { return mod(a, P); }

class segtree {
    private:
    int n;
    vector<int> A;
    vector<vector<pi>> sparse;
    vector<pi> lazy;
    void prop(int i) {
        addo(lazy[i<<1], lazy[i]);
        addo(lazy[i<<1|1], lazy[i]);
        lazy[i] = {0, 0};
    }
    void update(int i, int s, int e, int l, int r, pi x) {
        //cout << i << " " << s << " " << e << " " << l << " " << r << " " << x << "\n";
        if(r <= s || e <= l) return;
        else if(l <= s && e <= r) addo(lazy[i], x);
        else {
            prop(i);
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
        }
    }
    void query(int i, int s, int e, int j) {
        //cout << i << " " << s << " " << e << " " << j << "\n";
        if(j < s || j >= e) {
            return;
        } else if(s+1 == e) {
            for(int j = 0, k = 1; k < INF; k <<= 1, j++) {
                if(lazy[i].fi & k) A[s] = sparse[A[s]][j].fi;
                if(lazy[i].se & k) A[s] = sparse[A[s]][j].se;
            }
            lazy[i] = {0, 0};
        } else {
            prop(i);
            query(i<<1, s, s+e>>1, j);
            query(i<<1|1, s+e>>1, e, j);
        }
    }
    
    public:
    segtree(vector<int>& B) {
        n = B.size();
        A = B;
        sparse = vector<vector<pi>>(P);
        lazy = vector<pi>(4*n, {0, 0});
        for(ll i = 0; i < P; i++)
            sparse[i].push_back({mod(2LL*i*i-1), mod(4LL*i*i*i-3LL*i)});
        for(int j = 1, k = 2; k < INF; k <<= 1, j++)
            for(int i = 0; i < P; i++)
                sparse[i].push_back({sparse[sparse[i][j-1].fi][j-1].fi, sparse[sparse[i][j-1].se][j-1].se});
    }
    int query(int j) {
        query(1, 0, n, --j);
        return A[j];
    }
    void update(int l, int r, pi x) { update(1, 0, n, --l, r, x); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> A(n);
    for(auto &i : A) cin >> i;
    segtree s(A);
    while(q--) {
        int t; cin >> t;
        switch(t) {
            case 1:
            case 2:
            int l, r; cin >> l >> r;
            s.update(l, r, {t == 1, t == 2});
            break;

            default:
            int j; cin >> j;
            cout << s.query(j) << "\n";
            break;
        }
    }
    return 0;
}