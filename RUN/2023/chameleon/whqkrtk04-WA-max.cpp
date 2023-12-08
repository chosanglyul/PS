#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<pll, int> plli;
typedef pair<pli, int> plii;
#define fi first
#define se second

const ll LLINF = (ll)1e18+5;

vector<ll> dijk(vector<vector<pli>> &E) {
    int n = E.size();
    vector<ll> D(n, LLINF); D[0] = 0LL;
    priority_queue<pli, vector<pli>, greater<pli>> PQ;
    PQ.push({D[0], 0});
    while(PQ.size()) {
        pli tmp = PQ.top(); PQ.pop();
        if(tmp.fi > D[tmp.se]) continue;
        for(auto &i : E[tmp.se]) {
            if(D[i.se] <= tmp.fi+i.fi) continue;
            D[i.se] = tmp.fi+i.fi;
            PQ.push({D[i.se], i.se});
        }
    }
    return D;
}

void make_edges(vector<vector<pli>> &E, vector<plii> &X) {
    vector<pii> A;
    int n = X.size();
    for(int i = 1, j = 0; i <= n; i++) {
        if(i == n || X[i-1].fi.se != X[i].fi.se) {
            A.push_back({j, i});
            j = i;
        }
    }
    for(int i = 1; i < A.size(); i++) {
        pii x = A[i-1], y = A[i];
        ll z = X[y.fi].fi.fi;
        int idx = E.size();
        E.push_back(vector<pli>());
        int jdx = E.size();
        E.push_back(vector<pli>());
        for(int j = x.fi; j < x.se; j++) {
            ll d = abs(z-X[j].fi.fi);
            E[idx].push_back({d, X[j].se});
            E[X[j].se].push_back({d, jdx});
        }
        for(int j = y.fi; j < y.se; j++) {
            ll d = abs(z-X[j].fi.fi);
            E[jdx].push_back({d, X[j].se});
            E[X[j].se].push_back({d, idx});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<plli> A(n);
    for(auto &i : A) cin >> i.fi.fi >> i.fi.se >> i.se;
    
    vector<vector<pli>> E(n);
    vector<plii> X(n), Y(n);
    for(int i = 0; i < n; i++) {
        X[i] = {{A[i].fi.fi, A[i].se}, i};
        Y[i] = {{A[i].fi.se, A[i].se}, i};
    }
    sort(X.begin(), X.end());
    make_edges(E, X);
    sort(Y.begin(), Y.end());
    make_edges(E, Y);
/*
    for(auto &i : E) {
        for(auto j : i) cout << j.fi << " " << j.se << "  ";
        cout << endl;
    }
*/
    vector<ll> D = dijk(E);
    cout << D[n-1] << "\n";
/*
    for(auto i : D) cout << i << " ";
    cout << endl;
*/
    return 0;
}
