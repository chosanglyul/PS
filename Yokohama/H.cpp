#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const ll LLINF = (ll)1e18+5;

struct Node {
    int cnt;
    vector<pair<int, array<int, 3>>> x;
    Node() { cnt = 0; }
};

Node operator*(const Node& a, const Node& b) {
    Node ret;
    ret.cnt = a.cnt + b.cnt;
    int i1 = 0, i2 = 0;
    while (i1 < a.x.size() && i2 < b.x.size()) {
        int p1 = a.x[i1].first;
        int p2 = b.x[i2].first;
        if (p1 < p2) {
            auto tmp = a.x[i1].second;
            i1++;
            if (b.cnt == 1) {
                tmp[2] = tmp[1];
                tmp[1] = tmp[0];
                tmp[0] = 0;
                ret.x.push_back({ p1, tmp });
            } else if (b.cnt == 2) {
                tmp[2] = tmp[0];
                tmp[0] = tmp[1] = 0;
                ret.x.push_back({ p1, tmp });
            }
        } else if (p1 > p2) {
            auto tmp = b.x[i2].second;
            i2++;
            if (a.cnt == 1) {
                tmp[2] = tmp[1];
                tmp[1] = tmp[0];
                tmp[0] = 0;
                ret.x.push_back({ p2, tmp });
            } else if (a.cnt == 2) {
                tmp[2] = tmp[0];
                tmp[0] = tmp[1] = 0;
                ret.x.push_back({ p2, tmp });
            }
        } else {
            int j1 = 0, j2 = 0;
            array<int, 3> tmp;
            for (int i=0; i<3; ++i) {
                if (a.x[i1].second[j1] < b.x[i2].second[j2]) {
                    tmp[i] = a.x[i1].second[j1];
                    j1++;
                } else {
                    tmp[i] = b.x[i2].second[j2];
                    j2++;
                }
            }
            i1++;
            i2++;
            ret.x.push_back({ p1, tmp });
        }
    }
    while (i1 < a.x.size() && b.cnt < 3) {
        int p1 = a.x[i1].first;
        auto tmp = a.x[i1].second;
            i1++;
            if (b.cnt == 1) {
                tmp[2] = tmp[1];
                tmp[1] = tmp[0];
                tmp[0] = 0;
                ret.x.push_back({ p1, tmp });
            } else if (b.cnt == 2) {
                tmp[2] = tmp[0];
                tmp[0] = tmp[1] = 0;
                ret.x.push_back({ p1, tmp });
            }
    }
    while (i2 < b.x.size() && a.cnt < 3) {
        int p2 = b.x[i2].first;
        auto tmp = b.x[i2].second;
            i2++;
            if (a.cnt == 1) {
                tmp[2] = tmp[1];
                tmp[1] = tmp[0];
                tmp[0] = 0;
                ret.x.push_back({ p2, tmp });
            } else if (a.cnt == 2) {
                tmp[2] = tmp[0];
                tmp[0] = tmp[1] = 0;
                ret.x.push_back({ p2, tmp });
            }
    }
    return ret;
}

const int INF = 0x3f3f3f3f;

struct SegmentTree {
    int n, h;
    vector<Node> arr;
    SegmentTree(int _n): n(_n) {
        h = Log2(n);
        n = 1 << h;
        arr.resize(2*n);
    }

    void update(int x, const vector<pii>& v) {
        x += n;
        arr[x].cnt = 1;
        arr[x].x.clear();
        for (auto[p, e]: v) arr[x].x.push_back({ p, { e, INF, INF } });
        // for (auto[p, e]: v) cout << x << ' ' << p << ' ' << e << endl;
        for (x/=2; x>0; x/=2) {
            arr[x] = arr[2*x] * arr[2*x+1];
        }
    }

    Node query(int l, int r) {
        l += n, r += n;
        Node ret;
        bool init = false;
        for (; l<=r; l/=2, r/=2) {
            // cout << "lr " << l << " " << r << endl;
            if (l & 1) {
                if (init) ret = ret * arr[l++];
                else ret = arr[l++], init = true;
            }
            if (~r & 1) {
                if (init) ret = ret * arr[r--];
                else ret = arr[r--], init = true;
            }
        }
        return ret;
    }

    static int Log2(int x) {
        int ret = 0;
        while ((1 << ret) < x) ret++;
        return ret;
    }
};

const int MAX_A = 1e6 + 1;
int sieve[MAX_A];
vector<pii> fact[MAX_A]; // 12 => (2, 2), (3, 1)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int i = 2; i < MAX_A; i++) {
        if(!sieve[i])
            for(int j = i*2; j < MAX_A; j += i)
                if(!sieve[j]) sieve[j] = i;
    }
    for(int i = 2; i < MAX_A; i++) {
        int tmp = i;
        while(sieve[tmp]) {
            if(fact[i].empty() || fact[i].back().fi != sieve[tmp])
                fact[i].push_back({sieve[tmp], 1});
            else
                fact[i].back().se++;
            tmp /= sieve[tmp];
        }
        if(fact[i].empty() || fact[i].back().fi != tmp)
            fact[i].push_back({tmp, 1});
        else
            fact[i].back().se++;
    }

    int n, m;
    cin >> n >> m;
    vector<int> a(n+1);
    for (int i=1; i<=n; ++i) cin >> a[i];

    SegmentTree seg(n+1);
    for (int i=1; i<=n; ++i) seg.update(i, fact[a[i]]);
    for (int i=0; i<m; ++i) {
        char ch;
        cin >> ch;
        if (ch == 'U') {
            int j, x;
            cin >> j >> x;
            seg.update(j, fact[x]);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            auto ret = seg.query(l, r);
            ll ans = 1;
            // cout << "Qq " << ret.x.size() << '\n';
            for (auto[p, tup]: ret.x) {
                // cout << p << ' ' << tup[0] << ' ' << tup[1] << ' ' << tup[2] << '\n';
                for (int j=0; j<tup[k]; ++j) ans *= p;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}