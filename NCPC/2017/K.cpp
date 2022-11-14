#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;
int b, n, e;
int C[110000];
int p, q, r, m;
bool chk(int aa, int md, int ind){
    return aa*C[ind]>=md;
}
bool f(int md, int nb, int nn, int ne){
    for(int i=0;i<m;i++){
        if(chk(2*p, md, i)&&nb>=2){
            nb-=2;
            continue;
        }
        if(chk(p+q, md, i)&&nb>=1&&nn>=1){
            nb--;
            nn--;
            continue;
        }
        if(p+r<2*q){
            if(chk(p+r, md, i)&&nb>=1&&ne>=1){
                nb--;
                ne--;
                continue;
            }
        }
        if(chk(2*q, md, i)&&nn>=2){
            nn-=2;
            continue;
        }
        if(chk(p+r, md, i)&&nb>=1&&ne>=1){
            nb--;
            ne--;
            continue;
        }
        if(chk(q+r, md, i)&&nn>=1&&ne>=1){
            nn--;
            ne--;
            continue;
        }
        if(chk(r*2, md, i)&&ne>=2){
            ne-=2;
            continue;
        }
//        cout << i << " " << md  << " " << nb << " " << nn << " " << ne << "\n";
        return false;
    }
    return true;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> b >> n >> e;
    cin >> p >> q >> r;

    m = (b+n+e)/2;

    for(int i=0;i<m;i++)
        cin >> C[i];
    sort(C, C+m);
    int st=1, fin=200000000, mid;
    while(st<=fin){
        mid = (st+fin)/2;
        if(f(mid, b, n, e))
            st = mid+1;
        else
            fin = mid-1;
    }
    cout << st - 1;

    return 0;
}