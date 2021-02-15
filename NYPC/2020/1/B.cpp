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

pii input() {
    int x, y, z;
    scanf("%d:%d:%d", &x, &y, &z);
    return {x, {y, z}};
}

//a <= b
bool cmp(pii a, pii b) {
    if(a.fi == b.fi) {
        if(a.se.fi == b.se.fi) {
            return a.se.se <= b.se.se;
        } else return a.se.fi < b.se.fi;
    } else return a.fi < b.fi;
}

int main() {
    pii a = input(), b = input(), c = input();
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        pii tmp = input();
        if(cmp(tmp, c)) printf("***\n");
        else if(cmp(tmp, b)) printf("**\n");
        else if(cmp(tmp, a)) printf("*\n");
        else printf(":(\n");
    }
    return 0;
}