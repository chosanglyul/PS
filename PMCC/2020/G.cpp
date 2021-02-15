#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef pair<ll, ll> pl;
typedef pair<ll, pl> pll;
#define fi first
#define se second

int n;
int g() {
    int x; cin >> x;
    n -= x;
    return x;
}
void f(int x) {
    cout << x << endl;
    n -= x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    if(n%5 == 1 || n%5 == 4) cout << "YES" << endl;
    else {
        cout << "NO" << endl;
        return 0;
    }
    f(1);
    if(n%5 != 0) f(3-g());
    while(n) {
        int x = g();
        if(x == 1) {
            f(1);
            f(3-g());
        } else f(5-x);
    }
    return 0;
}