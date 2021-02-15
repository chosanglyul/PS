#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef pair<pi, pi> piii;
#define fi first
#define se second

piii input() {
    piii tmp;
    cin >> tmp.fi.fi >> tmp.fi.se >> tmp.se.fi >> tmp.se.se;
    return tmp;
}

int sumv(piii a) { return a.fi.fi + a.fi.se + a.se.fi + a.se.se; }
int maxv(piii a) { return max(max(a.fi.fi, a.fi.se), max(a.se.fi, a.se.se)); }
int item(piii a, piii b) {
    int ta = maxv(a), tb = maxv(b);
    if(ta > tb) return 1;
    else if(ta == tb) return 0;
    else return -1;
}
int speed(piii a, piii b) {
    int ta = sumv(a), tb = sumv(b);
    if(ta > tb) return 1;
    else if(ta == tb) return 0;
    else return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    piii a, b;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        a = input(), b = input();
        int I = item(a, b);
        int S = speed(a, b);
        if(I > 0 && S <= 0) cout << "I\n";
        else if(S > 0 && I <= 0) cout << "S\n";
        else cout << "R\n";
    }
    return 0;
}