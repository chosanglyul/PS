#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
    int size;
    vector<ll> arr;
    SegmentTree(int size) : size(size) {
        arr.resize(4 * size, 0);
    }

    void update(int pos, ll val, int n, int nl, int nr) {
        if (nr < pos || pos < nl) return;
        if (nl == nr) {
            arr[n] = val;
            return;
        }
        int mid = (nl + nr) / 2;
        update(pos, val, 2*n, nl, mid);
        update(pos, val, 2*n+1, mid+1, nr);
        arr[n] = arr[2*n] + arr[2*n+1];
    }

    void update(int pos, ll val) {
        update(pos, val, 1, 0, size-1);
    }   

    ll query(int l, int r, int n, int nl, int nr) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return arr[n];
        int mid = (nl + nr) / 2;
        return query(l, r, 2*n, nl, mid) + query(l, r, 2*n+1, mid+1, nr);
    }

    ll query(int l, int r) {
        return query(l, r, 1, 0, size-1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    SegmentTree seg(n);
    for (int i=0; i<n; ++i) {
        ll x;
        cin >> x;
        seg.update(i, x);
    }

    for (int i=0; i<m+k; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int b;
            ll c;
            cin >> b >> c;
            seg.update(b-1, c);
        } else {
            int b, c;
            cin >> b >> c;
            cout << seg.query(b-1, c-1) << '\n';
        }
    }
}