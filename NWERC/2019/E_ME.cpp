#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;

int input() {
    int x, y; char c;
    cin >> x >> c >> y;
    return x*100+y;
}

void output(int x) {
    cout << x/100 << '.';
    int tmp = x%100;
    if(tmp < 10) cout << '0' << tmp;
    else cout << tmp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> A(4);
    for(auto &i : A) i = input();
    sort(A.begin(), A.end());
    int x = 3*input() - A[1] - A[2];
    if(x < A.front()) cout << "impossible\n";
    else if(x >= A.back()) cout << "infinite\n";
    else output(x);
    return 0;
}