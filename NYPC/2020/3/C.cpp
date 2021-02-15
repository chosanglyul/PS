#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pl;
#define fi first
#define se second

int n; ll l, r;

ll ccw(pl a, pl b, pl c) { return a.fi*b.se + b.fi*c.se + c.fi*a.se - a.se*b.fi - b.se*c.fi - c.se*a.fi; }
bool cmp(pl a, pl b) { return ccw(a, {l, 0}, b) < 0; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> l >> r;
    vector<pl> A(n), B;
    for(auto &i : A) cin >> i.fi >> i.se;
    sort(A.begin(), A.end(), cmp);
    for(auto &i : A)
        if(B.empty() || ccw(B.back(), {r, 0}, i) < 0)
            B.push_back(i);
    cout << B.size() << endl;
    return 0;
}