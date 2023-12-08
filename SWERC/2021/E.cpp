#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

pair<string, int> f(string s) {
    int cnt = 0;
    string t;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'B') cnt++;
        else {
            if(t.size() && t.back() == s[i]) t.pop_back();
            else t.push_back(s[i]);
        }
    }
    return {t, cnt%2};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        string u, v; cin >> u >> v;
        auto A = f(u), B = f(v);
        if(A == B) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}