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
const int P = 1e9+7;
const ll LLINF = 1e18+1;

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int solve(string& s, char c) {
    vector<int> A;
    vector<pii> B;
    for(int i = 0; i < s.size(); i++)
        if(s[i] == c) A.push_back(i);
    if(A.empty()) return 0;
    A.push_back(INF);

    int res = 0;
    for(int i = 0, l = 0, cnt = 0; i < A.size(); i++, cnt++) {
        if(i > 0 && A[i] != A[i-1]+1) {
            if(cnt%3) res += (cnt/3)*2+(cnt%3)-1;
            else res += (cnt/3)*2;
            if(cnt%3 == 1) B.push_back({0, {A[l], A[i-1]}});
            else B.push_back({1, {A[l], A[i-1]}});
            l = i, cnt = 0;
        }
    }

    B.push_back({0, {INF, INF}});

    //cout << res << " ";

    for(int i = 0, l = 0, cnt1 = 0, su = 0; i < B.size(); i++) {
        if(B[i].se.fi == B[i].se.se) cnt1++;
        if(i > 0 && B[i].se.fi != B[i-1].se.se+2) {
            res += max(0, (l-i)-su-cnt1);
            l = i, cnt1 = 0, su = 0;
        }
        su += B[i].fi;
    }

    cout << res << "  ";
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        int res = 0;
        for(int i = 0; i < 26; i++) {
            res += solve(s, 'a'+i);
        }
        cout << endl;
        cout << res << "\n";
    }
    return 0;
}