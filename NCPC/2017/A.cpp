#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

struct SegmentTree {
    int size;
    vector<pair<ll, int>> arr;
    SegmentTree(int _n) : size(_n) {
        arr.resize(4*size);
        init(1, 0, size-1);
    }

    void init(int n, int nl, int nr) {
        if (nl == nr) {
            arr[n] = { LLINF, nl };
            return;
        }
        int mid = (nl + nr) / 2;
        init(2*n, nl, mid);
        init(2*n+1, mid+1, nr);
        arr[n] = { LLINF, nl };
    }

    void update(int pos, ll val) {
        update(pos, val, 1, 0, size-1);
    }

    void update(int pos, ll val, int n, int nl, int nr) {
        if (nl == nr) {
            arr[n] = { val, nl };
            return;
        }
        int mid = (nl + nr) / 2;
        if (pos <= mid) update(pos, val, 2*n, nl, mid);
        else update(pos, val, 2*n+1, mid+1, nr);
        if (arr[2*n].first < arr[2*n+1].first) {
            arr[n] = arr[2*n];
        } else {
            arr[n] = arr[2*n+1];
        }
    }

    pair<ll, int> query(int l, int r) {
        return query(l, r, 1, 0, size-1);
    }

    pair<ll, int> query(int l, int r, int n, int nl, int nr) {
        if (r < nl || nr < l) return { LLINF, -1 };
        if (l <= nl && nr <= r) return arr[n];
        int mid = (nl + nr) / 2;
        pair<ll, int> q1 = query(l, r, 2*n, nl, mid);
        pair<ll, int> q2 = query(l, r, 2*n+1, mid+1, nr);
        return (q1.first < q2.first ? q1 : q2);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll l, a, b, t, r;
    cin >> l >> a >> b >> t >> r;
    int n;
    cin >> n;
    vector<ll> x(n+2, 0);
    for (int i=1; i<=n; ++i) cin >> x[i];
    x[n+1] = l;

    SegmentTree s1(n+2), s2(n+2); // dp2[i]-ax[i], dp2[i]-bx[i]
    vector<int> opt(n+2, -2);
    opt[1] = -1;
    s1.update(1, (b-a)*x[1]);
    s2.update(1, 0);

    pair<ll, int> tmp;
    for (int i=2; i<=n+1; ++i) {
        pair<ll, int> dp2 = { b*x[i], -1 };

        int j1 = lower_bound(x.begin(), x.end(), x[i]-t*a) - x.begin();
        tmp = s2.query(max(1,j1), i-1);
        tmp.first += b*x[i];
        if (dp2.first > tmp.first) dp2 = tmp;

        int j2 = lower_bound(x.begin(), x.end(), x[i]-t*a-r*b) - x.begin();
        tmp = s1.query(max(1,j2), j1-1);
        tmp.first += a*x[i] + a*b*t - a*a*t;
        if (dp2.first > tmp.first) dp2 = tmp;

        tmp = s2.query(1, j2-1);
        tmp.first += b*x[i] + a*b*r - b*b*r;
        if (dp2.first > tmp.first) dp2 = tmp;

        opt[i] = dp2.second;
        s1.update(i, dp2.first - a*x[i]);
        s2.update(i, dp2.first - b*x[i]);
    }
    //for (int x: opt) cout << x << ' ';
    //cout << endl;
    
    int last = n+1;
    vector<int> mids;
    while (opt[last] != -1) {
        mids.push_back(opt[last]-1);
        last = opt[last];
    }
    reverse(mids.begin(), mids.end());
    cout << mids.size() << '\n';
    for (int x: mids) cout << x << ' ';

    return 0;
}