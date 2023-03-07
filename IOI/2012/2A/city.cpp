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
const int P = 1000000000;
const ll LLINF = (ll)1e18+1;
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
ll mod(ll a, ll b) { return ((a%b) + b) % b; }

vector<int> compact(int N, int *arr) {
    vector<int> ret(arr, arr+N);
    int mi = *min_element(ret.begin(), ret.end()); mi--;
    for(int i = 0; i < N; i++) ret[i] -= mi;
    return ret;
}

plll dfs(int x, vector<int> &cnt, vector<vector<int>> &E, vector<bool> &chk) {
    if(chk[x]) return {0LL, {0LL, 0LL}};
    chk[x] = true;
    plll ret = {0LL, {cnt[x], 0LL}};
    for(auto i : E[x]) {
        plll tmp = dfs(i, cnt, E, chk);
        ret = {(ret.fi+tmp.fi+(ret.se.fi*(tmp.se.fi+tmp.se.se))%P+ret.se.se*tmp.se.fi)%P,
                {(tmp.se.fi+ret.se.fi)%P, (tmp.se.se+ret.se.se+tmp.se.fi)%P}};
    }
    //cout << x << "   " << ret << "\n";
    return ret;
}


int solve(int N, vector<int> X, vector<int> Y) {
    vector<vector<int>> P(101010);
    vector<vector<piii>> V(P.size());
    vector<int> cnt;
    for(int i = 0; i < N; i++) P[X[i]].push_back(Y[i]);
    for(int i = 0; i < P.size(); i++) {
        if(P[i].empty()) continue;
        sort(P[i].begin(), P[i].end());
        V[i].push_back({P[i][0], {0, cnt.size()}});
        for(int j = 1; j < P[i].size(); j++) {
            ++V[i].back().se.fi;
            if(P[i][j] > P[i][j-1]+1) {
                cnt.push_back(V[i].back().se.fi);
                V[i].push_back({P[i][j], {0, cnt.size()}});
            }
        }
        cnt.push_back(++V[i].back().se.fi);
    }
    //cout << cnt << " " << V;
    vector<vector<int>> E(cnt.size());
    for(int i = 1; i < P.size(); i++) {
        for(int j = 0, k = 0; j < P[i].size(); j++) {
            if(k+1 < V[i].size() && P[i][j] == V[i][k+1].fi) k++;
            piii tmp = {P[i][j], {INF, INF}};
            auto iter = upper_bound(V[i-1].begin(), V[i-1].end(), tmp);
            if(iter == V[i-1].begin()) continue;
            int x = V[i][k].se.se, y = (--iter)->se.se;
            if(iter->fi+iter->se.fi <= P[i][j]) continue;
            if(E[x].empty() || E[x].back() != y) {
                E[x].push_back(y);
                E[y].push_back(x);
            }
        }
    }
    //cout << " " << E;
    vector<bool> chk(cnt.size(), false);
    plll ret = dfs(0, cnt, E, chk);
    //cout << ret.fi << "\n";
    return ret.fi;
}

int DistanceSum(int N, int *X, int *Y) {
    vector<int> A = compact(N, X), B = compact(N, Y);
    int xx = solve(N, A, B), yy = solve(N, B, A);
    return (xx+yy)%P;
}