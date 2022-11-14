#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
#define fi first
#define se second

class score {
    public:
    int b, p, q, r;

    int gop() { return p*q*r; }
    int hap() { return p+q+r; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<score> A(n);
    for(auto &i : A) cin >> i.b >> i.p >> i.q >> i.r;
    sort(A.begin(), A.end(), [&](score& a, score& b) {
        if(a.gop() == b.gop()) {
            if(a.hap() == b.hap()) return a.b < b.b;
            else return a.hap() < b.hap();
        } else return a.gop() < b.gop();
    });
    cout << A[0].b << " " << A[1].b << " " << A[2].b << "\n";
    return 0;
}