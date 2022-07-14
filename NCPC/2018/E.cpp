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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(x, y) uniform_int_distribution<int>(x, y)(rng)
typedef vector<int> vi;

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

int d;
int health_init = 0;
map<vi, int> mp;
vi recover[500];
int health_sum[500];

long double dp[500][500];
long double solve(int ms, int es) {
    if (health_sum[ms] + health_sum[es] == health_init - d) {
        return (es == 462 - 1) ? 1.0 : 0.0;
    }
    long double& ans = dp[ms][es];
    if (ans > -0.5) return ans;

    vector<int> mine = recover[ms];
    vector<int> enemy = recover[es];
    int alive_cnt = 0;
    for (int x: mine) alive_cnt += (x > 0);
    for (int x: enemy) alive_cnt += (x > 0);
    long double p = 1.0 / alive_cnt;
    //cout << mine << enemy << '\n';

    ans = 0.0;
    for (int i=0; i<5; ++i) {
        if (mine[i] > 0) {
            vector<int> copy(mine);
            copy[i]--;
            sort(copy.begin(), copy.end(), greater<int>());
            ans += p * solve(mp[copy], mp[enemy]);
        }
    }
    for (int i=0; i<5; ++i) {
        if (enemy[i] > 0) {
            vector<int> copy(enemy);
            copy[i]--;
            sort(copy.begin(), copy.end(), greater<int>());
            ans += p * solve(mp[mine], mp[copy]);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int state_cnt = 0;
    for (int i=6; i>=0; --i) {
        for (int j=i; j>=0; --j) {
            for (int k=j; k>=0; --k) {
                for (int l=k; l>=0; --l) {
                    for (int m=l; m>=0; --m) {
                        mp[{i,j,k,l,m}] = state_cnt;
                        recover[state_cnt] = {i,j,k,l,m};
                        health_sum[state_cnt] = i+j+k+l+m;
                        state_cnt++;
                    }
                }
            }
        }
    }
    for (int i=0; i<500; ++i) {
        for (int j=0; j<500; ++j) {
            dp[i][j] = -1.0;
        }
    }
    
    int n, m;
    cin >> n >> m >> d;
    vi mine(5,0), enemy(5,0);
    for(int i=0;i<n;i++) cin >> mine[i];
    for(int i=0;i<m;i++) cin >> enemy[i];
    sort(mine.begin(), mine.end());
    reverse(mine.begin(), mine.end());
    sort(enemy.begin(), enemy.end());
    reverse(enemy.begin(), enemy.end());
    //cout << mine << enemy << mp[mine] << ' ' << mp[enemy] << '\n';
    health_init += accumulate(mine.begin(), mine.end(), 0) + accumulate(enemy.begin(), enemy.end(), 0);
    if(health_init <= d) cout << "1.000000000\n";
    else cout << solve(mp[mine], mp[enemy]) << "\n";
    return 0;
}