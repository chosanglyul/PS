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
ostream& operator<<(ostream& os, const vector<T>& v) { for(auto i : v) os << i << " "; os << "\n"; return os; }
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& p) { os << p.fi << " " << p.se; return os; }

/* https://github.com/justiceHui/AlgorithmImplement/blob/master/Math/ExtendGCD.cpp */
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

/* https://blog.myungwoo.kr/57 */

#define MAXN 500005

int N,SA[MAXN],lcp[MAXN];
char S[MAXN];

void SuffixArray()
{
    int i,j,k;
    int m = 26; // 처음 알파벳 개수
    vector <int> cnt(max(N,m)+1,0),x(N+1,0),y(N+1,0);
    for (i=1;i<=N;i++) cnt[x[i] = S[i]-'a'+1]++;
    for (i=1;i<=m;i++) cnt[i] += cnt[i-1];
    for (i=N;i;i--) SA[cnt[x[i]]--] = i;
    for (int len=1,p=1;p<N;len<<=1,m=p){
        for (p=0,i=N-len;++i<=N;) y[++p] = i;
        for (i=1;i<=N;i++) if (SA[i] > len) y[++p] = SA[i]-len;
        for (i=0;i<=m;i++) cnt[i] = 0;
        for (i=1;i<=N;i++) cnt[x[y[i]]]++;
        for (i=1;i<=m;i++) cnt[i] += cnt[i-1];
        for (i=N;i;i--) SA[cnt[x[y[i]]]--] = y[i];
        swap(x,y); p = 1; x[SA[1]] = 1;
        for (i=1;i<N;i++)
            x[SA[i+1]] = SA[i]+len <= N && SA[i+1]+len <= N && y[SA[i]] == y[SA[i+1]] && y[SA[i]+len] == y[SA[i+1]+len] ? p : ++p;
    }
}

void LCP()
{
    int i,j,k=0;
    vector <int> rank(N+1,0);
    for (i=1;i<=N;i++) rank[SA[i]] = i;
    for (i=1;i<=N;lcp[rank[i++]]=k)
        for (k?k--:0,j=SA[rank[i]-1];S[i+k]==S[j+k];k++);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin >> t;
    for(int _t = 0; _t < t; _t++) {
        cout << "Case #" << _t+1 << endl;
        string r, p; cin >> r >> p;
        if(r[0] != p[0]) {
            cout << -1 << endl;
            continue;
        }
        int n = r.size();
        N = n;
        for(int i = 1; i <= N; i++) S[i] = r[i-1];
        S[N+1] = 0;
        SuffixArray();
        LCP();
        vector<int> A(n);
        for(int i = 0, x = 0; i < n; i++) {
            if(i) x = min(x, lcp[i+1]);
            while(x < p.size() && SA[i+1]+x-1 < n && r[SA[i+1]+x-1] == p[x]) x++;
            A[SA[i+1]-1] = x;
        }
        priority_queue<pi, vector<pi>, greater<pi>> PQ;
        vector<int> dp(n+1, INF); dp[0] = 0;
        for(int i = 1; i <= n; i++) {
            PQ.push({dp[i-1]+1, i+A[i-1]});
            while(PQ.size() && PQ.top().se <= i) PQ.pop();
            if(PQ.empty()) break;
            dp[i] = PQ.top().fi;
        }
        if(dp.back() == INF) cout << -1;
        else cout << dp.back();
        cout << endl;
    }
    return 0;
}
