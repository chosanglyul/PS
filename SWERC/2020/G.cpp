#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

void dfs(int x, vector<pii> &V, vector<int> &E) {
    if(V[x].fi) return;
    dfs(E[x], V, E);
    V[x] = {V[E[x]].fi,  V[E[x]].se+1};
}

vector<bool> topo(vector<int> &E) {
    int n = E.size();
    vector<int> I(n, 0);
    for(auto i : E) I[i]++;
    queue<int> Q;
    vector<bool> chk(n, true);
    for(int i = 0; i < n; i++)
        if(!I[i]) Q.push(i), chk[i] = false;
    while(Q.size()) {
        int i = Q.front(); Q.pop();
        if(--I[E[i]] == 0) Q.push(E[i]), chk[E[i]] = false;
    }
    return chk;
}

vector<pii> solve(vector<int> E) {
    int n = E.size();
    vector<pii> V(n, {0, 0});
    vector<bool> cyc = topo(E), chk(n, false);
    for(int i = 0; i < n; i++) {
        if(cyc[i] && !chk[i]) {
            int tmp = i;
            vector<int> T;
            while(!chk[tmp]) {
                T.push_back(tmp);
                chk[tmp] = true;
                tmp = E[tmp];
            }
            for(auto j : T) V[j] = {(int)T.size(), 0};
        }
    }
    for(int i = 0; i < n; i++) dfs(i, V, E);
    return V;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> E(n, 0);
    for(int i = 1; i < n; i++)
        for(int j = i; j < n; j += i) E[j]++;
    for(int i = 0; i < n; i++) E[i] += i;
    for(auto &i : E) i %= n;
    // for(auto i : E) cout << i << " ";
    // cout << "\n" << endl;
    vector<pii> V = solve(E);
    // cout << "V = " << endl;
    // for(auto i : V) cout << i.fi << " " << i.se << endl;
    vector<vector<pli>> S(21, vector<pli>(n));
    for(int j = 0; j < n; j++) S[0][j] = {j, E[j]};
    for(int i = 1; i <= 20; i++)
        for(int j = 0; j < n; j++)
            S[i][j] = {S[i-1][j].fi+S[i-1][S[i-1][j].se].fi, S[i-1][S[i-1][j].se].se};
    ll ans = LLINF; int miidx;
    for(int i = 0; i < n; i++) {
        if(V[i].fi+V[i].se < k) continue;
        int tmp = k, hre = i;
        ll su = 0LL;
        for(int j = 20; j >= 0; j--) {
            int tnp = 1<<j;
            if(tmp >= tnp) {
                pii mov = S[j][hre];
                hre = mov.se;
                tmp -= tnp;
                su += mov.fi;
            }
        }
        if(su < ans) {
            ans = su;
            miidx = i;
        }
    }
    if(ans == LLINF) {
        cout << -1 << "\n";
    } else {
        for(int i = 0; i < k; i++) {
            cout << miidx << " ";
            miidx = E[miidx];
        }
        cout << "\n";
    }
    return 0;
}