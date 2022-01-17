#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

double cross(pl a, pl b) { return (double)(a.se-b.se)/(double)(b.fi-a.fi); }

void ins(pl a, vector<pl>& A) {
    while(A.size() && A.back().fi == a.fi && A.back().se < a.se) A.pop_back();
    while(A.size() > 1 && cross(A[A.size()-2], A.back()) > cross(A.back(), a)) A.pop_back();
    A.push_back(a);
}

ll calc(ll x, vector<pl>& A) {
    int l = 0, r = A.size();
    while(l+1 < r) {
        int mi = l+r>>1;
        if(cross(A[mi-1], A[mi]) <= x) l = mi;
        else r = mi;
    }
    return A[l].fi*x+A[l].se;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> A(n), B(n), C(n, 0LL);
    for(auto &i : A) cin >> i;
    for(auto &i : B) cin >> i;
    vector<pl> D;
    ins({B[0], C[0]}, D);
    for(int i = 1; i < n; i++) {
        C[i] = calc(A[i], D);
        ins({B[i], C[i]}, D);
    }
    cout << C.back() << "\n";
    return 0;
}