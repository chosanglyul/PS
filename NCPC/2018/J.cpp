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
ll getsqrt(ll a){
    ll re = (int)sqrt(a);
    if(re*re==a)
        return re;
    if((re+1)*(re+1)==a)
        return re+1;
    return -1;
} 
ll getn(ll a){
    ll re = getsqrt(8*a+1);
    if(re==-1||re%2==0)
        return -1;
    return (re+1)/2;
}
int dap[10000000];
int main() {
    ll a,b,c,d;
    ll n,m;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b >> c >> d;
    if(a==0&&b==0&&c==0&d==0){
        cout << "0";
        return 0;
    }
    if(a==0&&d==0){
        if(b+c==1){
            if(b)
                cout << "01";
            else
                cout << "10";
            return 0;
        }
        cout << "impossible";
        return 0;
    }
    if(a==0){
        m=getn(d);
        if(m==-1||b+c!=0&&b+c!=m){
            cout << "impossible";
            return 0;
        }
        if(b+c==0){
            for(int i=0;i<m;i++)
                cout << "1";
        }
        if(b+c==m){
            for(int i=0;i<=m;i++)
                cout << !(i==c);
        }
        return 0;
    }
    if(d==0){
        m=getn(a);
        if(m==-1||b+c!=0&&b+c!=m){
            cout << "impossible";
            return 0;
        }
        if(b+c==0){
            for(int i=0;i<m;i++)
                cout << "0";
        }
        if(b+c==m){
            for(int i=0;i<=m;i++)
                cout << (i==b);
        }
        return 0;
    }
    n=getn(a);
    m=getn(d);
    if(n==-1||m==-1||n*m!=b+c){
        cout << "impossible";
        return 0;
    }
    for(int i=1;i<=c/n;i++){
        dap[i]=1;
    }
    dap[c/n+n-c%n+1]=1;
    for(int i=c/n+n+2;i<=n+m;i++)
        dap[i]=1;
    for(int i=1;i<=n+m;i++)
        cout <<dap[i];
    return 0;
}