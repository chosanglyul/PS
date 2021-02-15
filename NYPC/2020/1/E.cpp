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
const int P = 1e9+7;
const ll LLINF = 1e18+1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    unordered_set<int> S;
    int n, k; cin >> n >> k;
    vector<int> A(k), B;
    for(auto &i : A) cin >> i;
    B.push_back(A[0]);
    for(int i = 1; i <= n; i++) {
        if(i == A[0]) continue;
        bool can = false;
        for(int j = 0; j < k; j++) {
            if(A[j] == i) {
                if(can) {
                    B.push_back(i);
                    break;
                }
                can = true;
                S.clear();
            } else {
                if(S.find(A[j]) == S.end()) S.insert(A[j]);
                else can = false;
            }
        }
    }
    cout << B.size() << "\n";
    sort(B.begin(), B.end());
    for(auto &i : B) cout << i << " ";
    return 0;
}