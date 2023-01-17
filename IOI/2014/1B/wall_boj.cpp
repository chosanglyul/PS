#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

class segtree {
    private:
    int n;
    vector<pii> seg, lazy;

    const pii inf = {0, INF};
    pii mer_lazy(pii a, pii b) {
        return {min(b.se, max(a.fi, b.fi)), max(b.fi, min(a.se, b.se))};
    }
    pii mer_seg(pii a, pii b) {
        return {min(a.fi, b.fi), max(a.se, b.se)};
    }
    
    void prop(int i, int s, int e) {
        if(s+1 != e) {
            seg[i<<1] = mer_lazy(seg[i<<1], lazy[i]);
            seg[i<<1|1] = mer_lazy(seg[i<<1|1], lazy[i]);
            lazy[i<<1] = mer_lazy(lazy[i<<1], lazy[i]);
            lazy[i<<1|1] = mer_lazy(lazy[i<<1|1], lazy[i]);
        }
        lazy[i] = inf;
    }

    void update(int i, int s, int e, int l, int r, pii x) {
        prop(i, s, e);
        if(e <= l || r <= s) return;
        if(l <= s && e <= r) {
            seg[i] = mer_lazy(seg[i], x);
            lazy[i] = mer_lazy(lazy[i], x);
        } else {
            update(i<<1, s, s+e>>1, l, r, x);
            update(i<<1|1, s+e>>1, e, l, r, x);
            seg[i] = mer_seg(seg[i<<1], seg[i<<1|1]);
        }
    }

    int query(int i, int s, int e, int j) {
        prop(i, s, e);
        if(s+1 == e) return seg[i].fi;
        int mi = s+e>>1;
        if(j < mi) return query(i<<1, s, mi, j);
        else return query(i<<1|1, mi, e, j);
    }

    public:
    segtree(int n) {
        this->n = n;
        seg = vector<pii>(4*n, {0, 0});
        lazy = vector<pii>(4*n, inf);
    }

    void update(int op, int l, int r, int h) {
        r++, op--;
        if(!op) update(1, 0, n, l, r, {h, INF});
        else update(1, 0, n, l, r, {0, h});
    }

    void query(int height[]) {
        for(int i = 0; i < n; i++) height[i] = query(1, 0, n, i);
    }
};

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
    segtree S(n);
    for(int i = 0; i < k; i++) S.update(op[i], left[i], right[i], height[i]);
    S.query(finalHeight);
    return;
}

int main()
{
  int n;
  int k;

  int i, j;  
  int status = 0;

  status = scanf("%d%d", &n, &k);
  assert(status == 2);

  int* op = (int*)calloc(sizeof(int), k);
  int* left = (int*)calloc(sizeof(int), k);
  int* right = (int*)calloc(sizeof(int), k);
  int* height = (int*)calloc(sizeof(int), k);
  int* finalHeight = (int*)calloc(sizeof(int), n);

  for (i = 0; i < k; i++){
    status = scanf("%d%d%d%d", &op[i], &left[i], &right[i], &height[i]);
    assert(status == 4);
  }

  buildWall(n, k, op, left, right, height, finalHeight);

  for (j = 0; j < n; j++)
    printf("%d\n", finalHeight[j]);
  
  return 0;
}
