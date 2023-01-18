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
    int c = L[x] - L[y];
    for(int i = 19; i >= 0; i--)
        if((c>>i)&1)
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

#define MAX_N          500000
#define MAX_Q          100000
#define MAX_SUM_ST    1000000
#define MAX_VALUE  1000000000

static int N, Q;
static int A[MAX_N], B[MAX_N], DD[MAX_N];
static int SS[MAX_N];
static int T[MAX_N];
static int X[MAX_SUM_ST];
static int Y[MAX_SUM_ST];

static int Qx[MAX_N];
static int Qy[MAX_N];

int main() {
  int i, j, k;
  int STop, TTop;

  if (2 != scanf("%d%d", &N, &Q)) {
    fprintf(stderr, "error: cannot read N and Q.\n");
    exit(1);
  }
  if (!(2 <= N && N <= MAX_N)) {
    fprintf(stderr, "error: N is out of bounds.\n");
    exit(1);
  }
  if (!(1 <= Q && Q <= MAX_Q)) {
    fprintf(stderr, "error: Q is out of bounds.\n");
    exit(1);
  }
  for (i = 0; i < N - 1; ++i) {
    if (1 != scanf("%d", &A[i])) {
      fprintf(stderr, "error: cannot read A[%d].\n", i);
      exit(1);
    }
    if (!(0 <= A[i] && A[i] <= N - 1)) {
      fprintf(stderr, "error: A[%d] is out of bounds.\n", i);
      exit(1);
    }
    if (1 != scanf("%d", &B[i])) {
      fprintf(stderr, "error: cannot read B[%d].\n", i);
      exit(1);
    }
    if (!(0 <= B[i] && B[i] <= N - 1)) {
      fprintf(stderr, "error: B[%d] is out of bounds.\n", i);
      exit(1);
    }
    if (A[i] == B[i]) {
      fprintf(stderr, "error: B[%d] is equal to A[%d].\n", i, i);
      exit(1);
    }
    if (1 != scanf("%d", &DD[i])) {
      fprintf(stderr, "error: cannot read DD[%d].\n", i);
      exit(1);
    }
    if (!(1 <= DD[i] && DD[i] <= MAX_VALUE)) {
      fprintf(stderr, "error: DD[%d] is out of bounds.\n", i);
      exit(1);
    }
  }

  STop = 0;
  TTop = 0;

  for (j = 0; j < Q; ++j) {
    if (2 != scanf("%d%d", &SS[j], &T[j])) {
      fprintf(stderr, "error: cannot read L[%d] and R[%d].\n", j, j);
      exit(1);
    }

    if(STop + SS[j] > MAX_SUM_ST) {
      fprintf(stderr, "error: SS[0] + SS[1] + ... + SS[%d] is out of bounds.\n", j);
      exit(1);
    }

    if(TTop + T[j] > MAX_SUM_ST) {
      fprintf(stderr, "error: T[0] + T[1] + ... + T[%d] is out of bounds.\n", j);
      exit(1);
    }

    for (k = 0; k < SS[j]; ++k, ++STop) {
      if (1 != scanf("%d", &X[STop])) {
        fprintf(stderr, "error: cannot read X[%d][%d].\n", j, k);
        exit(1);
      }

      if (!(0 <= X[STop] && X[STop] <= N - 1)) {
        fprintf(stderr, "error: cannot read X[%d][%d].\n", j, k);
        exit(1);
      }
    }

    for (k = 0; k < T[j]; ++k, ++TTop) {
      if (1 != scanf("%d", &Y[TTop])) {
        fprintf(stderr, "error: cannot read Y[%d][%d].\n", j, k);
        exit(1);
      }

      if (!(0 <= Y[TTop] && Y[TTop] <= N - 1)) {
        fprintf(stderr, "error: cannot read Y[%d][%d].\n", j, k);
        exit(1);
      }
    }
  }

  STop = 0;
  TTop = 0;
  Init(N, A, B, DD);

  for (j = 0; j < Q; ++j) {
    for (k = 0; k < SS[j]; k++) {
        Qx[k] = X[STop++];
    }
    for (k = 0; k < T[j]; k++) {
        Qy[k] = Y[TTop++];
    }

    printf("%lld\n", Query(SS[j], Qx, T[j], Qy));
  }


  return 0;
}
