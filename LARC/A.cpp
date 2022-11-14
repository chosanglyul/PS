#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> pll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll s;
    int n;
    cin >> s >> n;
    vector<pll> points(n);
    for (auto&[x,y]: points) cin >> x >> y;

    ll ans = 0;
    for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            vector<ll> a,b;
            for (int k=0; k<n; ++k) {
                
            }
        }
    }

    return 0;
}