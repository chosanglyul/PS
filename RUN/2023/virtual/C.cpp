#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505050;
struct point {
    int x, y;
};
int n; point a[MAXN];

struct fenwick {
    int tree[MAXN];
    void init() {
        fill(tree, tree + MAXN, 0);
    }
    void update(int a, int x) {
        for (; a < MAXN; a += a & -a) tree[a] += x;
    }
    int query(int a) {
        int r = 0;
        for (; a > 0; a -= a & -a) r += tree[a];
        return r;
    }
} t1;
int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        a[i] = {x, y};
    }
    sort(a, a + n, [&](point p, point q) {
        return p.x - p.y < q.x - q.y;
    });
    vector<int> v;
    for (int i = 0; i < n; i++) v.push_back(a[i].x + a[i].y);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        w[i] = lower_bound(v.begin(), v.end(), a[i].x + a[i].y) - v.begin() + 1;
    }
    vector<int> lcnt(n);
    vector<int> rcnt(n);
    for (int i = 0, r = 0; i < n; i = r) {
        while (r < n && a[i].x - a[i].y == a[r].x - a[r].y) ++r;
        for (int j = i; j < r; j++) {
            int p = w[j];
            lcnt[j] = t1.query(p - 1);
            rcnt[j] = i - t1.query(p);
        }
        for (int j = i; j < r; j++) t1.update(w[j], 1);
    }
    t1.init();
    long long ans = 0;
    for (int i = n - 1, r = n - 1; i >= 0; i = r) {
        while (r >= 0 && a[i].x - a[i].y == a[r].x - a[r].y) --r;
        for (int j = i; j > r; j--) {
            int p = w[j];
            ans += (long long)lcnt[j] * (n - 1 - i - t1.query(p));
            ans += (long long)rcnt[j] * t1.query(p - 1);
        }
        for (int j = i; j > r; j--) t1.update(w[j], 1);
    }
    ans = (long long)n * (n - 1) * (n - 2) / 6 - ans;
    cout << ans;
}