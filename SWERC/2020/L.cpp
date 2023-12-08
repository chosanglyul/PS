#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pii;
#define fi first
#define se second
const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> capacity(m);
    for(auto &i : capacity) cin >> i;

    string s;
    getline(cin, s);
    set<int> S;
    vector<deque<int>> A(n);
    for(int i = 0; i < n; i++) {
        getline(cin, s);
        stringstream ss; ss << s;
        int x;
        while(ss >> x) A[i].push_back(--x);
        if(A[i].size()) S.insert(i);
    }
    vector<map<int, int>> B(m);
    for(int i = 0; i < m; i++) {
        getline(cin, s);
        stringstream ss; ss << s;
        int x;
        while(ss >> x) B[i].insert({--x, B[i].size()});
    }

    vector<priority_queue<pii, vector<pii>, less<pii>>> PQ(m);
    while(S.size()) {
        vector<int> SS;
        for(auto i : S) SS.push_back(i);
        for(auto i : SS) {
            int tmp = A[i].front();
            A[i].pop_front();
            S.erase(i);
            PQ[tmp].push({B[tmp][i], i});
            if(PQ[tmp].size() > capacity[tmp]) {
                pii cnt = PQ[tmp].top();
                PQ[tmp].pop();
                if(A[cnt.se].size()) S.insert(cnt.se);
            }
        }
    }

    set<int> M;
    for(int i = 0; i < m; i++) {
        while(PQ[i].size()) {
            M.insert(PQ[i].top().se);
            PQ[i].pop();
        }
    }
    for(auto i : M) cout << i+1 << "\n";
    return 0;
}