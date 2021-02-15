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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    int cursor = 0;
    for(auto c : s) {
        if(c == 'S') cursor++;
        else cursor = (cursor/4+1)*4;
    }
    cout << cursor << endl;
    return 0;
}