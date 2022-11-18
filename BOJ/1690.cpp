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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)

ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1, y = 0;
    if(b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m) {
    ll x, y; ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> B(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        B[--x] = i;
    }

    // 순열 사이클 분할
    vector<vector<int>> C, cnt(n+1);
    vector<bool> chk(n, false);
    for(int i = 0; i < n; i++) {
        if(chk[i]) continue;
        int tmp = i, idx = C.size();
        C.push_back(vector<int>());
        do {
            chk[tmp] = true;
            C.back().push_back(tmp);
            tmp = B[tmp];
        } while(tmp != i);
        cnt[C.back().size()].push_back(idx);
    }

    // 같은 길이 짝수 cycle이 홀수개면 터짐
    // 홀수 cycle은 그냥 한칸씩 밀기
    // 짝수 cycle은 같은 길이 두개 골라서 교대로 써주기
    vector<int> A(n);
    for(int i = 1; i < cnt.size(); i++) {
        if(i%2 == 1) {
            for(int j = 0; j < cnt[i].size(); j++) {
                vector<int> &V = C[cnt[i][j]];
                for(int k = 0; k < i; k++) A[V[k]] = V[(k+(i+1)/2)%i];
            }
        } else {
            if(cnt[i].size()%2 == 1) {
                cout << 0 << "\n";
                return 0;
            }
            for(int j = 0; j < cnt[i].size(); j += 2) {
                vector<int> &U = C[cnt[i][j]], &V = C[cnt[i][j+1]];
                for(int k = 0; k < i; k++) {
                    A[U[k]] = V[k];
                    A[V[k]] = U[(k+1)%i];
                }
            }
        }
    }

    // 출력하기
    cout << n << "\n";
    for(auto i : A) cout << i+1 << "\n";
    return 0;
}