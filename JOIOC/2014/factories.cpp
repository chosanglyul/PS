#include "factories.h"
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
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

vector<vector<int>> S, E;
vector<int> P, L, I, O;
vector<ll> D;
vector<bool> U, V;

int lca(int x, int y) {
    if(L[x] < L[y]) swap(x, y);
    for(int i = 19; i >= 0; i--)
        if(L[S[x][i]] >= L[y])
            x = S[x][i];
    if(x == y) return x;
    for(int i = 19; i >= 0; i--)
        if(S[x][i] != S[y][i])
            x = S[x][i], y = S[y][i];
    return S[x][0];
}

void make_sparse() {
    S.resize(P.size(), vector<int>(20));
    for(int i = 0; i < P.size(); i++) S[i][0] = P[i];
    for(int i = 0; i < P.size(); i++)
        for(int j = 1; j < 20; j++)
            S[i][j] = S[S[i][j-1]][j-1];
}

void dfs(int x, int p, int &cnt, vector<vector<pii>> &E) {
    I[x] = cnt++;
    for(auto &i : E[x]) {
        if(i.fi == p) continue;
        L[cnt] = L[I[x]]+1;
        D[cnt] = D[I[x]]+i.se;
        P[cnt] = I[x];
        dfs(i.fi, x, cnt, E);
    }
    O[x] = cnt;
}

plll solve(int x) {
    plll ans = {LLINF, {LLINF, LLINF}};
    if(U[x]) ans.se.fi = 0LL;
    if(V[x]) ans.se.se = 0LL;
    U[x] = V[x] = false;
    for(auto i : E[x]) {
        plll tmp = solve(i);
        ans.fi = min(ans.fi, tmp.fi);
        ans.se.fi = min(ans.se.fi, tmp.se.fi + D[i] - D[x]);
        ans.se.se = min(ans.se.se, tmp.se.se + D[i] - D[x]);
    }
    ans.fi = min(ans.fi, ans.se.fi+ans.se.se);
    return ans;
}

void sort_vertex(vector<int> &vertex) {
    sort(vertex.begin(), vertex.end());
    vertex.erase(unique(vertex.begin(), vertex.end()), vertex.end());
}

void make_tree(vector<int> &M) {
    int tmpsize = M.size();
    for(int i = 1; i < tmpsize; i++) M.push_back(lca(M[i-1], M[i]));
    sort_vertex(M);
    for(int i = 1; i < M.size(); i++) E[lca(M[i-1], M[i])].push_back(M[i]);
}

void Init(int N, int A[], int B[], int X[]) {
    vector<vector<pii>> T(N);
    for(int i = 0; i < N-1; i++) {
        T[A[i]].push_back({B[i], X[i]});
        T[B[i]].push_back({A[i], X[i]});
    }
    I.resize(N); O.resize(N); P.resize(N);
    D.resize(N, 0LL); L.resize(N, 0);
    int cnt = 0;
    dfs(0, 0, cnt, T);
    make_sparse();
    U.resize(N, false); V.resize(N, false); E.resize(N);
}

ll Query(int S, int X[], int T, int Y[]) {
    //cout << "query " << S << " " << T << "\n";
    vector<int> XX(X, X+S), YY(Y, Y+T), M;
    for(auto i : XX) { M.push_back(I[i]); U[I[i]] = true; }
    for(auto i : YY) { M.push_back(I[i]); V[I[i]] = true; }
    sort_vertex(M);
    make_tree(M);
    plll ans = solve(M[0]);
    assert(ans.se.fi < LLINF && ans.se.se < LLINF);
    for(auto i : M) E[i].clear();
    return ans.fi;
}
