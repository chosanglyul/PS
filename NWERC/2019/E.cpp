#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = 1e9+5;
const int P = 1000000007;
const ll LLINF = (ll)1e18+5;
int t[4], T;
int main() {
    int a,b;
    for(int i=0;i<4;i++){
        scanf("%d.%d",&a,&b);
        t[i] = a*100+b;
    }
    scanf("%d.%d",&a,&b);
    T = a*100+b;
    sort(t, t+4);
    int x = 3*T-t[1]-t[2];
    if(x>=t[3])
        cout << "infinite";
    else if(x<t[0])
        cout << "impossible"; 
    else
        printf("%d.%02d",x/100, x%100);
 
    return 0;
}