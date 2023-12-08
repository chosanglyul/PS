#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define all(v) (v).begin(),(v).end()

const int MAXN = 400010;

int N[2], W[2][MAXN], H[2][MAXN];
int A[2][MAXN];
int idx[MAXN];
bool b[MAXN];
vector<int> high;
vector<int> ans;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    for(int i = 0; i < 2; i++) {
        cin >> N[i];
        for(int j = 0; j < N[i]; j++) cin >> W[i][j] >> H[i][j];
    }

    vector<int> xs;
    xs.eb(0);
    for(int i = 0; i < 2; i++) {
        int x = 0;
        for(int j = 0; j < N[i]; j++) {
            x += W[i][j];
            xs.eb(x);
        }
    }

    sort(all(xs));
    xs.resize(unique(all(xs)) - xs.begin());

    for(int i = 0; i < 2; i++) {
        int x = 0;
        int k = 0;
        for(int j = 0; j < N[i]; j++) {
            x += W[i][j];
            for(; xs[k] < x; k++) {
                A[i][k] = H[i][j];
                //printf("A[%d][%d] = %d\n", i, k, A[i][k]);
                if(i == 0) idx[k] = j;
            }
        }
    }

    for(int i = 0; i < xs.size() - 1; i++) if(A[0][i] == A[1][i]) high.eb(i);
    sort(all(high), [&](const int a, const int b) { return A[0][a] > A[0][b]; });

    for(auto x : high) {
        if(b[x]) continue;
        ans.eb(idx[x]);
        b[x] = true;

        //printf("x = %d\n", x);

        int h = A[0][x];
        for(int y = x - 1; y >= 0; y--) {
            h = min(h, A[0][y]);
            if(A[1][y] < h) {
                cout << "-1\n";
                return 0;
            }
            if(b[y] || A[1][y] > h) break;
            b[y] = true;
        }
        
        h = A[0][x];
        for(int y = x + 1; y < xs.size() - 1; y++) {
            h = min(h, A[0][y]);
            if(A[1][y] < h) {
                cout << "-1\n";
                return 0;
            }
            if(b[y] || A[1][y] > h) break;
            b[y] = true;
        }
    }

    for(int i = 0; i < xs.size() - 1; i++) if(!b[i]) {
        cout << "-1\n";
        return 0;
    }

    cout << ans.size() << "\n";
    for(auto a : ans) cout << (a + 1) << " ";
    cout << "\n";
    return 0;
}