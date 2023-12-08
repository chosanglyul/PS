#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    int d, s;
    cin >> d >> s;
    
    int sum_solved = s*k;
    int cond = n*d;
    int remain = cond - sum_solved;
    double avg_unsolved = (double)remain / (n-k);
    if (remain < 0 || remain > 100*(n-k)) {
        cout << "impossible";
    } else {
        cout << fixed << setprecision(15) << avg_unsolved;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
}