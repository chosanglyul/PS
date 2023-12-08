#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5000 + 1;

int rp[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i=1; i<MAX_N; ++i) fill(rp[i]+1, rp[i]+MAX_N, 1);
    for (int d=2; d<=n; ++d) {
        for (int i=d; i<=n; i+=d) {
            for (int j=d; j<=n; j+=d) {
                rp[i][j] = 0;
            }
        }
    }
    for (int i=1; i<MAX_N; ++i) {
        for (int j=1; j<MAX_N; ++j) rp[i][j] += rp[i][j-1];
    }

    double low = 0, high = 1;
    for (int it=0; it<100; ++it) {
        double mid = (low + high) / 2;
        int cnt = 1;
        for (int i=1; i<=n; ++i) {
            cnt += rp[i][(int)floor(mid * i)];
        }
        if (cnt >= k) {
            high = mid;
        } else {
            low = mid;
        }
    }
    low += 1e-9;

    pair<int, int> mx = { 0, 1 };
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            if (rp[i][j] == rp[i][j-1] + 1 && j <= low * i) {
                if (mx.second * j > mx.first * i) {
                    mx = { j, i };
                }
            }
        }
    }
    cout << mx.first << ' ' << mx.second;

    return 0;
}