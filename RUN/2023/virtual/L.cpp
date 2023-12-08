#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef tuple<long long, long long, int> tlli;
#define ff first
#define ss second

const int MAXN = 101010;
const long long INF = (long long)1e18 + 7;
int X[MAXN];
int Y[MAXN];
int C[MAXN];
vector<int> prX, prY;

vector<pii> gph[MAXN * 5];
pll D[MAXN * 5];
long long E[MAXN * 5]; 

void pressX(int s, int e, vector<int> V)
{
    if(s + 1 == e)
    {
        for(auto x : V) gph[x].push_back({s + 2 * MAXN, 0}), gph[s + 2 * MAXN].push_back({x, 0});
        return;
    }

    int mid = s + e >> 1;
    vector<int> L, R;
    for(auto x : V)
    {
        if(X[x] < mid) L.push_back(x), gph[x].push_back({mid + MAXN, prX[mid] - prX[X[x]]})
                                    , gph[mid + MAXN].push_back({x, prX[mid] - prX[X[x]]});
        else R.push_back(x), gph[x].push_back({mid + MAXN, prX[X[x]] - prX[mid]})
                                    , gph[mid + MAXN].push_back({x, prX[X[x]] - prX[mid]});
    }
    pressX(s, mid, L);
    pressX(mid, e, R);
}
void pressY(int s, int e, vector<int> V)
{
    if(s + 1 == e)
    {
        for(auto x : V) gph[x].push_back({s + 4 * MAXN, 0}), gph[s + 4 * MAXN].push_back({x, 0});
        return;
    }

    int mid = s + e >> 1;
    vector<int> L, R;
    for(auto x : V)
    {
        if(Y[x] < mid) L.push_back(x), gph[x].push_back({mid + 3 * MAXN, prY[mid] - prY[Y[x]]})
                                    , gph[mid + 3 * MAXN].push_back({x, prY[mid] - prY[Y[x]]});
        else R.push_back(x), gph[x].push_back({mid + 3 * MAXN, prY[Y[x]] - prY[mid]})
                                    , gph[mid + 3 * MAXN].push_back({x, prY[Y[x]] - prY[mid]});
    }
    pressY(s, mid, L);
    pressY(mid, e, R);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; ++i)
    cin >> X[i] >> Y[i] >> C[i], prX.push_back(X[i]), prY.push_back(Y[i]);

    long long walk = max(abs(X[0] - X[n - 1]), abs(Y[0] - Y[n - 1]));

    sort(prX.begin(), prX.end());
    sort(prY.begin(), prY.end());
    prX.resize(unique(prX.begin(), prX.end()) - prX.begin());
    prY.resize(unique(prY.begin(), prY.end()) - prY.begin());
    for(int i = 0; i < n; ++i) X[i] = lower_bound(prX.begin(), prX.end(), X[i]) - prX.begin();
    for(int i = 0; i < n; ++i) Y[i] = lower_bound(prY.begin(), prY.end(), Y[i]) - prY.begin();

    int Xn = prX.size(), Yn = prY.size();
    vector<int> V;
    for(int i = 0; i < n; ++i) V.push_back(i);
    pressX(0, Xn, V);
    pressY(0, Yn, V);

    // for(int i = 0; i < n; ++i)
    // {
    //     for(auto [x, y] : gph[i]) cout << "(" << x << ", " << y << ") ";
    //     cout << endl;
    // }

    priority_queue<tlli, vector<tlli>, greater<tlli>> Q;
    Q.push({0, 0, -1});
    fill(D, D + MAXN * 5, pll{-1, -1});
    fill(E, E + MAXN * 5, -1);
    while(Q.size())
    {
        auto [d, x, col] = Q.top(); Q.pop();
        // cout << d << ' ' << x << endl;
        if(x < MAXN)
        {
            if(D[x].ff != -1) continue;
            D[x].ff = d;
            if(x == n - 1) return !(cout << min(d, walk));
            for(auto [y, c] : gph[x]) Q.push({c + d, y, C[x]});
        }
        else
        {
            if(D[x].ff == -1) D[x] = { d, col };
            else if(E[x] == -1 && D[x].ss != col) E[x] = d;
            else continue;
            for(auto [y, c] : gph[x]) if(C[y] != col) Q.push({c + d, y, -1});
        }
    }
    cout << walk;
    return 0;
}