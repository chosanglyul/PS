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
    cin.tie(0);
    ll a, b, c;
    cin >> a >> b >> c;
    if((a+b-c)%2 || (abs(a)+abs(b)) > c) cout << "NO\n";
    else cout << "YES\n";
    return 0;
}