#include <bits/stdc++.h>
using namespace std;

struct NOD {
    NOD *lef;
    NOD *rig;
    int mx;

    NOD(NOD *lef, NOD *rig, int mx) : lef(lef), rig(rig), mx(mx) {}
};

typedef pair<NOD *, int> pni;

#define eb emplace_back
#define fi first
#define se second

const int MAXN = 250010;

int N;
int A[MAXN];
vector<int> ed[2][MAXN];
int dfn[MAXN], dn, drng[MAXN];
int ans[MAXN];
NOD *nil;

void dfsord(int x, int p) {
    dfn[x] = ++dn;
    for(auto a : ed[1][x]) if(a != p) dfsord(a, x);
    drng[x] = dn;
}

NOD *mknod(int l, int r, int x, int z) {
    NOD *n = new NOD(nil, nil, z);
    if(l != r) {
        int m = (l + r) / 2;
        if(x <= m) n->lef = mknod(l, m, x, z);
        else n->rig = mknod(m + 1, r, x, z);
    }
    return n;
}

void merge(NOD *n, NOD *nt, int l, int r) {
    n->mx = max(n->mx, nt->mx);
    int m = (l + r) / 2;
    if(nt->lef->mx) {
        if(n->lef->mx == 0) n->lef = new NOD(nil, nil, 0);
        merge(n->lef, nt->lef, l, m);
    }
    if(nt->rig->mx) {
        if(n->rig->mx == 0) n->rig = new NOD(nil, nil, 0);
        merge(n->rig, nt->rig, m + 1, r);
    }
}

int gseg(NOD *n, int l, int r, int x, int y) {
    if(x <= l && r <= y) return n->mx;
    if(r < x || y < l) return 0;
    int m = (l + r) / 2;
    return max(gseg(n->lef, l, m, x, y), gseg(n->rig, m + 1, r, x, y));
}

void fre(NOD *s) {
    if(s->lef->mx) fre(s->lef);
    if(s->rig->mx) fre(s->rig);
    free(s);
}

pni dfs(int x, int p) {
    NOD *s = mknod(1, N, dfn[x], A[x]);
    int c = 1;
    for(auto a : ed[0][x]) if(a != p) {
        pni r = dfs(a, x);
        NOD *st = r.fi;
        int ct = r.se;
        if(c < ct) {
            swap(c, ct);
            swap(s, st);
        }
        merge(s, st, 1, N);
        c += ct;
        fre(st);
    }
    ans[x] = gseg(s, 1, N, dfn[x], drng[x]);
    return pni(s, c);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 0; i < 2; i++) for(int j = 0; j < N - 1; j++) {
        int u, v;
        cin >> u >> v;
        ed[i][u].eb(v);
        ed[i][v].eb(u);
    }

    nil = (NOD *)malloc(sizeof(NOD));
    nil->lef = nil->rig = nil;
    nil->mx = 0;

    dfsord(1, 0);
    dfs(1, 0);

    for(int i = 1; i <= N; i++) cout << ans[i] << "\n";
    return 0;
}