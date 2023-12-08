#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 49;
    cout << n << "\n";
    vector<piii> E;
    for(int i = 0; i < (n-1)/2; i++) {
        int idx = (n-1)/2-i;
        E.push_back({((1<<idx)+idx-1), {2*i, 2*i+1}});
        E.push_back({-((1<<idx)+idx-1), {2*i+1, 2*i+2}});
        E.push_back({(1<<(idx-1)), {2*i, 2*i+2}});
    }
    cout << E.size() << "\n";
    for(auto &i : E) cout << i.se.fi << " " << i.se.se << " " << i.fi << "\n";
    return 0;
}