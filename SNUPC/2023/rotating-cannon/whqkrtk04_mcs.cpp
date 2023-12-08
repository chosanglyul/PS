#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll LLINF = (ll)1e15+5;

vector<int> solve(ll s, ll e, int n, vector<int> ans,
                vector<ll> &A, vector<ll> &B,
                vector<int> &C, vector<vector<int>> &D) {
    for(auto i : ans) {
        for(auto j : ans) {
            if(i == j || D[j][i] < 0) continue;
            ll rot = B[j]*C[j];
            A[i] += (s/rot)+(s%rot > B[j]*D[j][i]);
            A[i] -= (e/rot)+(e%rot > B[j]*D[j][i]);
        }
    }

    vector<int> ret;
    for(auto i : ans) if(A[i] > 0LL) ret.push_back(i);
    return ret;
}

vector<int> step(int n, ll &t, vector<int> &ans,
                vector<ll> &A, vector<ll> &B,
                vector<int> &C, vector<vector<int>> &D) {
    ll s = 0LL, e = LLINF;
    while(s+1 < e) {
        ll m = s+e>>1;
        vector<ll> AT(A), BT(B);
        vector<int> tmp = solve(t, t+m-1LL, n, ans, AT, BT, C, D);
        if(tmp.size() < ans.size()) e = m;
        else s = m;
    }
    vector<int> ret = solve(t, t+s, n, ans, A, B, C, D);
    // cout << t << " " << s << " " << ret.size() << endl;
    t += s;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> A(n), B(n);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;

    vector<int> C(n);
    vector<vector<int>> D(n, vector<int>(n, -1));
    for(int i = 0; i < n; i++) {
        int tmp = 1, cnt = 0;
        do {
            if(0 < tmp && tmp < n)
                D[i][(i+tmp)%n] = cnt;
            tmp = (tmp+B[i])%(2*n);
            cnt++;
        } while(tmp != 1);
        C[i] = cnt;
    }

    vector<int> ans;
    for(int i = 0; i < n; i++) ans.push_back(i);
    
    ll t = 0LL;
    while(t < LLINF) ans = step(n, t, ans, A, B, C, D);

    cout << ans.size() << "\n";
    for(auto i : ans) cout << i+1 << " ";
    cout << "\n";
}
