#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

vector<int> f(int x) {
    vector<int> A;
    for(int i = 1; i*i <= x; i++) {
        if(x%i == 0) {
            A.push_back(i);
            A.push_back(x/i);
        }
    }
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    return A;
}

vector<int> g(int x, int y) {
    vector<int> A = f(x);
    vector<int> B = f(y);
    vector<int> C;
    int i = 0, j = 0;
    while(i < A.size() && j < B.size()) {
        if(A[i] == B[j]) {
            C.push_back(A[i]);
            i++, j++;
        }
        else if(A[i] < B[j]) i++;
        else j++;
    }
    return C;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int a, b; cin >> a >> b;
        vector<int> A = g(a-2, b), B = g(a, b-2), C = g(a-1, b-1);
        vector<int> D = {1, 2};
        for(auto i : A) D.push_back(i);
        for(auto i : B) D.push_back(i);
        for(auto i : C) D.push_back(i);
        sort(D.begin(), D.end());
        D.erase(unique(D.begin(), D.end()), D.end());
        cout << D.size() << " ";
        for(auto i : D) cout << i << " ";
        cout << "\n";
    }
    return 0;
}
