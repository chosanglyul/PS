#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+1;
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

double diffx(int arr[500][500], int i, int j) {
    if(!j) return 0;
    return abs(arr[i][j]-arr[i][j-1]);
}

double diffy(int arr[500][500], int i, int j) {
    if(!i) return 0;
    return abs(arr[i][j]-arr[i-1][j]);
}

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]) {
    double a = 0, b = 0, d = 0, e = 0, f = 0;
    int c = 0;
    vector<double> A(W);
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            A[j] += (double)(G[i][j]+R[i][j]+B[i][j])/H;
            double xx = diffx(R, i, j)+diffx(G, i, j)+diffx(B, i, j);
            double yy = diffy(R, i, j)+diffy(G, i, j)+diffy(B, i, j);
            a += xx/H/(W-1)/2;
            a += yy/(H-1)/W/2;
            d += xx/H/(W-1)/2;
            b += (double)G[i][j]/H/W;
            e += (double)R[i][j]/H/W;
            f += (double)B[i][j]/H/W;
            if(R[i][j] < 5 || G[i][j] < 5 || B[i][j] < 5
            || R[i][j] > 250 || G[i][j] > 250 || B[i][j] > 250) c++;
        }
    }
    double w = 0;
    for(int i = 1; i < W; i++) w += abs(A[i]-A[i-1])/(W-1);
    //cout << w << "\n";
    double z = a+5*d;
    if(z < 25 || a < 7.5 || d < 2.5 || w < 2) return 4;
    if(a < 40) {
        //cout << "1 or 2 : " << c << " " << z << " " << f << "\n";
        if(c > 30000 || z < 70 || f > 90 || w > 6) return 1;
    } else {
        //cout << "2 or 3 : " << a << " " << d << "\n";
        if(a > 70 || d > 30 || f > 90 || w > 6) return 3;
    }
    //cout << a << " " << b << " " << c << " " << d << " " << z << " " << e << " " << f << "\n";
    return 2;
}

int R[500][500];
int G[500][500];
int B[500][500];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int H, W; cin >> H >> W;
    for(int i = 0; i < H; i++)
        for(int j = 0; j < W; j++)
            cin >> R[i][j];
    for(int i = 0; i < H; i++)
        for(int j = 0; j < W; j++)
            cin >> G[i][j];
    for(int i = 0; i < H; i++)
        for(int j = 0; j < W; j++)
            cin >> B[i][j];
    cout << style(H, W, R, G, B) << "\n";
    return 0;
}
