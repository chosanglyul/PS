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
const ll P = 20150523LL;
const ll LLINF = 1e18+1;
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto &i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

ll mod(ll a, ll b) { return ((a%b) + b) % b; }

vector<vector<vector<ll>>> A(2, vector<vector<ll>>(10, vector<ll>(3, 0LL)));
vector<ll> B(100000, 1LL);

ll solve(string& s) {
    int tmp = 0;
    ll ret = 0LL;
    for(int i = 0; i < s.size(); i++) {
        int x = s[i]-'0';
        for(int j = 0; j < x; j++) {
            if(j && j%3 == 0) ret = mod(ret+B[s.size()-i-1], P);
            else ret = mod(ret+A[s.size()-i-1][j][mod(-tmp, 3LL)], P);
        }
        if(x && x%3 == 0) {
            for(int j = i+1; j < s.size(); j++)
                ret = mod(ret+(s[j]-'0')*B[s.size()-j-1], P);
            break;
        }
        tmp += x;
    }
    return ret;
}

ll chk(string& s) {
    int tmp = 0;
    for(auto i : s) {
        if(i == '3' || i == '6' || i == '9') return 1LL;
        tmp += i-'0';
    }
    return tmp%3 == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    for(int i = 1; i < B.size(); i++) B[i] = mod(10LL*B[i-1], P);
    for(int j = 0; j < A[0].size(); j++)
        for(int x = 0; x < A[0][j].size(); x++)
            A[0][j][x] = (j%3 == x);
    for(int i = 1; i < A.size(); i++) {
        for(int j = 0; j < A[i].size(); j++) {
            if(j && j%3 == 0) continue;
            else {
                for(int k = 0; k < A[i-1].size(); k++)
                    for(int x = 0; x < A[i][j].size(); x++)
                        A[i][j][x] = mod(A[i][j][x]+A[i-1][k][mod(x-j, 3LL)], P);
            }
        }
    }
    cout << " " << A;
    int tmp = 0;
    string a, b; cin >> a >> b;
    cout << solve(a) << "\n" << solve(b) << "\n" << chk(b) << "\n";
    cout << mod(solve(b)-solve(a)+chk(b), P) << "\n";
    return 0;
}