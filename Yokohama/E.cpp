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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> x(n);
    for (int& y: x) cin >> y;
    auto it = max_element(x.begin(), x.end());
    int d = it - x.begin();
    for (int i=0; i<d; ++i) x.push_back(x[i]);

    int M = x[d];
    double r = (double)M / 2;
    double ang_sum = 0;
    for (int i=d+1; i<d+n; ++i) {
        ang_sum += 2.0 * asin((double)x[i] / (2*r));
    }
    // cout << ang_sum << endl;

    cout << fixed << setprecision(15);
    const double PI = acos(-1);
    if (ang_sum > PI) {
        double low = r, high = 1e7;
        for (int it=0; it<100; ++it) {
            double m = (low + high) / 2;
            double ang_sum = 0;
            for (int i=d; i<d+n; ++i) {
                ang_sum += 2.0 * asin((double)x[i] / (2*m));
                // cout << i << ' ' << x[i] << ' ' << ang_sum << endl;
            }
            // cout << m << ' ' << ang_sum << endl;
            if (ang_sum > 2*PI) {
                low = m;
            } else {
                high = m;
            }
        }
        cout << low;
    } else {
        double low = r, high = 1e7;
        for (int it=0; it<100; ++it) {
            double m = (low + high) / 2;
            double crit_ang = 2.0 * asin((double)x[d] / (2*m));
            double ang_sum = 0;
            for (int i=d+1; i<d+n; ++i) {
                ang_sum += 2.0 * asin((double)x[i] / (2*m));
            }
            if (ang_sum > crit_ang) {
                high = m;
            } else {
                low = m;
            }
        }
        cout << low;
    }

    return 0;
}