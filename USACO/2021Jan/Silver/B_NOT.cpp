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

void solve(vector<int>& A, string& s) {
    stack<char> S;
    set<char> chk;
    for(int i = 0; i < s.size(); i++) {
        if(!i) {
            A[i+1] = 1;
            S.push(s[i]);
        } else if(s[i-1] < s[i]) {
            A[i+1] = A[i]+1;
            S.push(s[i]);
        } else if(s[i-1] > s[i]) {
            if(chk.find(s[i]) != chk.end())
                while(S.size() && S.top() != s[i]) S.pop();
            if(S.empty() || S.top() != s[i]) {
                A[i+1] = A[i]+1;
                S.push(s[i]);
            } else A[i+1] = A[i];
        } else A[i+1] = A[i];
        chk.insert(s[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<int> A(n+1, 0), B(n+1, 0);
    solve(A, s);
    reverse(s.begin(), s.end());
    solve(B, s);
    /*
    for(auto &i : A) cout << i << " ";
    cout << "\n";
    for(auto &i : B) cout << i << " ";
    cout << "\n";
    */
    while(q--) {
        int a, b; cin >> a >> b;
        cout << A[a-1]+B[n-b] << "\n";
    }
    return 0;
}