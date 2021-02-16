#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    ll m; cin >> m;
    vector<pi> A(k);
    vector<int> B(n), C(n);
    vector<vector<pi>> V(n);
    for(auto &i : A) {
        cin >> i.fi >> i.se;
        i.fi--, i.se--;
    }
    for(int i = 0; i < n; i++) {
        B[i] = i;
        V[i].emplace_back(i, 0);
    }
    for(int i = 0; i < k; i++) {
        V[B[A[i].fi]].emplace_back(A[i].se, i+1);
        V[B[A[i].se]].emplace_back(A[i].fi, i+1);
        swap(B[A[i].fi], B[A[i].se]);
    }
    for(int i = 0; i < n; i++) C[B[i]] = i;
    /*
    cout << endl;
    for(auto &i : B) cout << i << " ";
    cout << endl;
    for(auto &i : C) cout << i << " ";
    cout << endl;
    for(auto &i : V) {
        for(auto &j : i) cout << j.fi << " " << j.se << "  ";
        cout << endl;
    }
    cout << endl;
    */
    for(int i = 0; i < n; i++) {
        set<int> S;
        for(int cycle = 0, tmp = i; (cycle == 0 || (tmp != i)) && ((ll)cycle*k <= m); cycle++, tmp = C[tmp]) {
            //cout << "    " << V[tmp].size() << endl;
            for(auto &j : V[tmp]) {
                //cout << j.fi << " " << j.se << endl;
                if((ll)cycle*k+j.se > m) break;
                S.insert(j.fi);
            }
        }
        cout << S.size() << "\n";
    }
    return 0;
}