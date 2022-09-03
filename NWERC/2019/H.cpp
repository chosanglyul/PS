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

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& arr) {
    out << '[';
    for (auto i: arr) {
        out << i << ' ';
    }
    out << ']';
    return out;
}

struct MaxSeg {
    int size;
    vector<int> arr;
    MaxSeg(int _size) : size(_size) {
        arr.resize(4*size);
        clear();
    }

    void clear() {
        fill(arr.begin(), arr.end(), numeric_limits<int>::min());
    }

    void update(int l, int r, int val, int n, int nl, int nr) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            arr[n] = max(arr[n], val);
            return;
        }
        int mid = (nl + nr) / 2;
        update(l, r, val, 2*n, nl, mid);
        update(l, r, val, 2*n+1, mid+1, nr);
    }

    void update(int l, int r, int val) {
        update(l, r, val, 1, 0, size-1);
    }

    int query(int pos, int n, int nl, int nr) {
        if (nl == nr) return arr[n];
        int mid = (nl + nr) / 2;
        if (pos <= mid) {
            return max(arr[n], query(pos, 2*n, nl, mid));
        } else {
            return max(arr[n], query(pos, 2*n+1, mid+1, nr));
        }
    }

    int query(int pos) {
        return query(pos, 1, 0, size-1);
    }
};

struct MinSeg {
    int size;
    vector<int> arr;
    MinSeg(int _size) : size(_size) {
        arr.resize(4*size);
    }

    void clear() {
        fill(arr.begin(), arr.end(), numeric_limits<int>::max());
    }

    void update(int l, int r, int val, int n, int nl, int nr) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            arr[n] = min(arr[n], val);
            return;
        }
        int mid = (nl + nr) / 2;
        update(l, r, val, 2*n, nl, mid);
        update(l, r, val, 2*n+1, mid+1, nr);
    }

    void update(int l, int r, int val) {
        update(l, r, val, 1, 0, size-1);
    }

    int query(int pos, int n, int nl, int nr) {
        if (nl == nr) return arr[n];
        int mid = (nl + nr) / 2;
        if (pos <= mid) {
            return min(arr[n], query(pos, 2*n, nl, mid));
        } else {
            return min(arr[n], query(pos, 2*n+1, mid+1, nr));
        }
    }

    int query(int pos) {
        return query(pos, 1, 0, size-1);
    }
};

MaxSeg maxseg(100001);
MinSeg minseg(100001);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout << fixed << setprecision(13);

    int n, k;
    cin >> n >> k;
    vector<int> h_orig(n+1);
    for (int& x: h_orig) cin >> x;

    for (int i=0; i<k; ++i) {
        double tmp;
        cin >> tmp;
        int g = floor(tmp * 10.0 + 0.2);

        vector<int> hs;
        vector<int> height(n+1);
        for (int i=0; i<=n; ++i) {
            height[i] = h_orig[i] - g*i;
            hs.push_back(height[i]);
        }
        sort(hs.begin(), hs.end());
        hs.erase(unique(hs.begin(), hs.end()), hs.end());
        vector<int> hcomp(n+1);
        for (int i=0; i<=n; ++i) hcomp[i] = lower_bound(hs.begin(), hs.end(), height[i]) - hs.begin();
        //cout << hs << endl << height << endl;

        minseg.clear();
        maxseg.clear();
        for (int i=0; i<n; ++i) {
            int a = hcomp[i];
            int b = hcomp[i+1];
            if (a > b) swap(a, b);
            //cout << a << ' ' << b << endl;
            minseg.update(a, b, i);
            maxseg.update(a, b, i);
        }

        double ans = -1.0;
        for (int i=0; i<=n; ++i) {
            int newh = hcomp[i];
            int l = minseg.query(newh);
            int r = maxseg.query(newh);
            //cout << newh << ' ' << l << ' ' << r << endl;

            if (height[l] == height[l+1]) {
                if (l > 0 && height[l-1] > height[l]) ans = max(ans, (double)i-l);
                else ans = max(ans, (double)i);
            } else if (height[l] < height[l+1]) {
                ans = max(ans, (double)i);
            } else {
                 ans = max(ans, (double)(i - l- (double)(height[i]-height[l]) / (height[l+1]-height[l])));
            }

            //cout << ans << endl;
            if (height[r] == height[r+1]) {
                if (r+1 < n && height[r+2] > height[r+1]) ans = max(ans, (double)n-i);
                else ans = max(ans, (double)r+1-i);
            } else if (height[r] < height[r+1]) {
                ans = max(ans, (double)n-i);
            } else {
                ans = max(ans, (double)(height[i]-height[r]) / (height[r+1]-height[r]) + r - i);
            }
            
            //cout << ans << endl;
        }

        if (ans < 1e-7) cout << -1;
        else cout << ans;
        cout << '\n';
    }

    return 0;
}