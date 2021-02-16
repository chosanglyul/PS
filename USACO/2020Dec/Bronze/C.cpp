#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<pi, pi> pii;
#define fi first
#define se second
const int INF = 1e9+1;

int su(pi a) { return a.fi+a.se; }

bool cmp(pii a, pii b) {
    if(su(a.se) == su(b.se)) return a.fi.se < b.fi.se;
    else return su(a.se) < su(b.se);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pii> A(n);
    vector<int> B(n, INF), C(n);
    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        if(c == 'E') A[i].fi.fi = 0;
        else A[i].fi.fi = 1;
        A[i].fi.se = i;
        cin >> A[i].se.fi >> A[i].se.se;
    }
    sort(A.begin(), A.end(), cmp);
    /*
    cout << endl;
    for(auto &i : A) cout << i.fi.fi << " " << i.fi.se << " " << i.se.fi << " " << i.se.se << endl;
    cout << endl;
    */
    for(int i = n-1; i >= 0; i--) {
        for(int j = i+1; j < n; j++) {
            if(su(A[i].se) == su(A[j].se)) continue;
            pi tar = {-1, -1};
            if(A[i].fi.fi) tar = {A[i].se.fi, A[j].se.se};
            else tar = {A[j].se.fi, A[i].se.se};
            if(A[j].fi.fi) {
                if(tar.fi != A[j].se.fi) continue;
                if(tar.se > A[j].se.se+B[j] || tar.se < A[j].se.se) continue;
            } else {
                if(tar.se != A[j].se.se) continue;
                if(tar.fi > A[j].se.fi+B[j] || tar.fi < A[j].se.fi) continue;
            }
            if(A[i].fi.fi) B[i] = min(B[i], tar.se-A[i].se.se);
            else B[i] = min(B[i], tar.fi-A[i].se.fi);
            if(B[i] <= 0) exit(1);
        }
    }
    for(int i = 0; i < n; i++) C[A[i].fi.se] = i;
    for(int i = 0; i < n; i++) {
        if(B[C[i]] == INF) cout << "Infinity\n";
        else cout << B[C[i]] << "\n";
    }
    return 0;
}