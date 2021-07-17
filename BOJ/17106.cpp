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
const int P = 1000000007;
const ll LLINF = (ll)1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) { //return x when ax mod m = 1, fail -> -1
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

vector<vector<bool>> C(5, vector<bool>(5, false));
set<pi> D, H;
int E = 0, F = 0, G = 0;
bool inflag = false;

bool getB(pi x, pi y) {
    int i = x.fi, j = x.se;
    for(int k = 0; k < 5; k++) {
        if(!C[i][j]) return false;
        if(x.fi < y.fi) i++;
        if(x.fi > y.fi) i--;
        if(x.se < y.se) j++;
        if(x.se > y.se) j--;
    }
    if(inflag) {
        i = x.fi, j = x.se;
        for(int k = 0; k < 5; k++) {
            D.insert({i, j});
            if(x.fi < y.fi) i++;
            if(x.fi > y.fi) i--;
            if(x.se < y.se) j++;
            if(x.se > y.se) j--;
        }
    }
    return true;
}

bool A1() { return !getB({4, 0}, {0, 4}); }
bool B1() { return D.find({0, 1}) == D.end(); }
bool C1() { return getB({0, 0}, {4, 4}); }
bool D1() { return C[3][3]; }
bool E1() { return D.find({0, 4}) != D.end(); }
bool A2() { return !C[3][0]; }
bool B2() { return E && F && G; }
bool C2() { return C[1][3]; }
bool D2() { return H.size() <= 17; }
bool E2() { return !(D.size()%2); }
bool A3() { return D.find({2, 0}) != D.end(); }
bool B3() { return H.size()-D.size() >= 5; }
bool C3() { return (!C[2][2]) || (D.find({2, 2}) != D.end()); }
bool D3() { return F >= 2; }
bool E3() { return D.size() <= 15; }
bool A4() { return !C[1][0]; }
bool B4() { return getB({1, 0}, {1, 4}) || getB({0, 3}, {4, 3}); }
bool C4() {
    int cnt = 0;
    for(int i = 0; i < 5; i++) if(C[i][2]) cnt++;
    return cnt <= 3;
}
bool D4() { return C[0][3]; }
bool E4() { return G > 0; }
bool A5() { return C[4][4]; }
bool B5() { return C[4][1]; }
bool C5() { return C[4][2]; }
bool D5() { return E+F+G >= 3; }
bool E5() { return C[4][0]; }
int main() {
    vector<int> A, B;
    vector<function<bool()>> fu = {A1, B1, C1, D1, E1, A2, B2, C2, D2, E2, A3, B3, C3, D3, E3, A4, B4, C4, D4, E4, A5, B5, C5, D5, E5};
    for(int i = 0; i < (1<<25); i++) {
    //for(int i = 15349361; i <= 15349361; i++) {
        for(int j = 0, k = 1; j < 25; j++, k <<= 1) {
            if(i&k) {
                C[j/5][j%5] = true;
                H.insert({j/5, j%5});
            } else C[j/5][j%5] = false;
        }
        inflag = true;
        for(int i = 0; i < 5; i++) {
            if(getB({i, 0}, {i, 4})) E++;
            if(getB({0, i}, {4, i})) F++;
        }
        if(getB({0, 0}, {4, 4})) G++;
        if(getB({4, 0}, {0, 4})) G++;
        /*
        for(auto &i : D) cout << i.fi << " " << i.se << "  ";
        cout << "\n";
        for(auto &i : H) cout << i.fi << " " << i.se << "  ";
        cout << "\n";
        */
        inflag = false;
        bool flag = true;
        for(int j = 0; j < fu.size(); j++)
            if(fu[j]() != C[j/5][j%5])
                flag = false;
        if(!flag) {
            D.clear(); H.clear(); E = F = G = 0;
            continue;
        }
        cout << i << "\n";
        for(int j = 0; j < 25; j++) {
            cout << (C[j/5][j%5] ? '#':'.');
            if((j+1)%5 == 0) cout << "\n";
        }
        for(auto &i : D) cout << i.fi << " " << i.se << "  ";
        cout << "\n";
        for(auto &i : H) cout << i.fi << " " << i.se << "  ";
        cout << "\n";

        if(C[4][1]) A.push_back(i);
        else B.push_back(i);
        D.clear(); H.clear(); E = F = G = 0;
    }
    cout << A.size() << " " << B.size() << "\n";
    int ans = 0;
    if(A.size() != 1) ans = A[0];
    else ans = B[0];
    cout << ans << "\n";
    for(int j = 0, k = 1; j < 25; j++, k <<= 1) {
        cout << ((ans&k) ? '#' : '.');
        if((j+1)%5 == 0) cout << "\n";
    }
    return 0;
}