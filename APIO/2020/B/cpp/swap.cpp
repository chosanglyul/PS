#include "swap.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+50;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }

struct UF {
    vector<int> A;
    vector<vector<pii>> P, B, C;
    vector<vector<int>> elements;

    int get(int t, vector<pii> &T) {
        auto iter = upper_bound(T.begin(), T.end(), pii(t, INF));
        return (--iter)->se;
    }

    int fin(int t, int x) {
        return get(t, P[x]);
    }

    int max_deg(int t, int x) {
        return get(t, B[fin(t, x)]);
    }

    int has_cyc(int t, int x) {
        return get(t, C[fin(t, x)]);
    }

    void mer(int t, int x, int y) {
        int xx = P[x].back().se, yy = P[y].back().se;
        if(xx != yy) {
            if(elements[xx].size() < elements[yy].size()) swap(xx, yy), swap(x, y);
            B[xx].push_back({t, max(max(B[xx].back().se, B[yy].back().se), max(++A[x], ++A[y]))});
            C[xx].push_back({t, C[xx].back().se || C[yy].back().se});
            for(auto i : elements[yy]) {
                P[i].push_back({t, xx});
                elements[xx].push_back(i);
            }
            elements[yy].clear();
        } else {
            B[xx].push_back({t, max(B[xx].back().se, max(++A[x], ++A[y]))});
            C[xx].push_back({t, 1});
        }
    }

    UF(int n) {
        A.resize(n, 0), B.resize(n, {{0, 0}}), C.resize(n, {{0, 0}});
        elements.resize(n), P.resize(n);
        for(int i = 0; i < n; i++) {
            elements[i].push_back(i);
            P[i].push_back({0, i});
        }
    }
};

int n, m;
vector<piii> E;
UF uf(0);

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
    uf = UF(N), n = N, m = M, E.resize(M);
    for(int i = 0; i < M; i++) E[i] = {W[i], {U[i], V[i]}};
    sort(E.begin(), E.end());
    for(auto &i : E) uf.mer(i.fi, i.se.fi, i.se.se);
}

int getMinimumFuelCapacity(int X, int Y) {
    int s = 0, e = INF-5;
    while(s+1 < e) {
        int mi = s+e>>1;
        //cout << s << " " << e << " " << mi << " " << X << " " << Y << " " << mi-1 << "\n";
        if(uf.fin(mi-1, X) == uf.fin(mi-1, Y) && (uf.max_deg(mi-1, X) >= 3 || uf.has_cyc(mi-1, X))) e = mi;
        else s = mi;
    }
    if(s == INF-6) return -1;
    else return s;
}
