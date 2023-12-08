#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define gibon ios::sync_with_stdio(false); cin.tie(0);
#define fi first
#define se second
#define pdd pair<long double, long double>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define ppi pair<pii, pii>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;
const int mxN=100003;
const int mxM=10004;
const int mxK=65;
const int MOD=1e9+7;
const ll INF=8e18;
int dx[4]={1, 0, -1, 0}, dy[4]={0, 1, 0, -1};
int N, K;
char S[mxN];
vector <pii> v;
bool Chk[mxN];
void input()
{
    cin >> N >> K >> S;
}
void make_v()
{
    char now=S[0];
    int cnt=1, s=0;
    for(int i=1;i<N;i++)
    {
        if(now==S[i])   cnt++;
        else
        {
            if(cnt>=K)  v.emplace_back(s, s+K-1), v.emplace_back(i-K, i-1);
            s=i;
            now=S[i];
            cnt=1;
        }
    }
    if(cnt>=K)  v.emplace_back(s, s+K-1), v.emplace_back(N-K, N-1);
}
int main()
{
    gibon
    input();
    make_v();
    for(int i=N;i>=1;i--)
    {
        if((N-1)/i*2<v.size())    continue;
        bool ok=true;
        for(auto [a, b] : v)    if(a/i==b/i)    ok=false;
        if(ok)
        {
            cout << i << '\n';
            return 0;
        }
    }
}
