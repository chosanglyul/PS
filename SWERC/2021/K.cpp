#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
#define fi first
#define se second

const int INF = (int)1e9+5;
const ll LLINF = (ll)1e18+5;

// multiply: input format - [x^0 coeff, x^1 coeff, ...], [same], [anything]
typedef complex<double> base;
const double PI = acos(-1);
void fft(vector<base>& a, bool inv) {
    int n = a.size();
    for (int dest=1, src=0; dest<n; ++dest) {
        int bit = n / 2;
        while (src >= bit) {
            src -= bit;
            bit /= 2;
        }
        src += bit;
        if (dest < src) { swap(a[dest], a[src]); }
    }
    for (int len=2; len <= n; len *= 2) {
        double ang = 2 * PI / len * (inv ? -1 : 1);
        base unity(cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w(1, 0);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= unity;
            }
        }
    }
    if (inv) {
        for (int i=0; i<n; ++i) { a[i] /= n; }
    }
}

void multiply(const vector<int>& a, const vector<int>& b, vector<int>& result) {
    int n = 2;
    while (n < a.size() + b.size()) { n *= 2; }

    vector<base> p(a.begin(), a.end());
    p.resize(n);
    for (int i=0; i<b.size(); ++i) { p[i] += base(0, b[i]); }
    fft(p, false);

    result.resize(n);
    for (int i=0; i<=n/2; ++i) {
        base u = p[i], v = p[(n-i) % n];
        p[i] = (u * u - conj(v) * conj(v)) * base(0, -0.25);
        p[(n-i) % n] = (v * v - conj(u) * conj(u)) * base(0, -0.25);
    }
    fft(p, true);
    for (int i=0; i<n; ++i) { result[i] = (int)round(p[i].real()); }
}

pil dfs(int x, vector<bool> &vis, vector<int> &S, vector<vector<pil>> &E) {
    if(vis[x]) return {0, 0LL};
    vis[x] = true;
    ll cnt = 0LL;
    int ans = 1;
    for(auto &i : E[x]) {
        pil tmp = dfs(i.fi, vis, S, E);
        i.se = tmp.se;
        cnt += tmp.se;
        ans += tmp.fi;
    }
    cnt += ans;
    S[x] = ans;
    return {ans, cnt};
}

void dfs2(int x, int p, ll tmp, vector<int> &S, vector<vector<pil>> &E) {
    ll cnt = tmp;
    for(auto i : E[x]) cnt += i.se;
    for(auto &i : E[x]) {
        if(i.fi == p) i.se = tmp;
        else dfs2(i.fi, x, cnt+((int)E.size()-S[i.fi])-i.se, S, E);
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr);
    int n; cin >> n;
    vector<int> S(n);
    vector<vector<pil>> E(n);
    vector<int> p(n, -1);
    for(int i = 1; i < n; i++) {
        int j; cin >> j; --j;
        p[i] = j;
        E[i].push_back({j, 0LL});
        E[j].push_back({i, 0LL});
    }
    vector<bool> vis(n, false);
    dfs(0, vis, S, E);
    fill(vis.begin(), vis.end(), false);
    dfs2(0, -1, 0LL, S, E);

    ll ans = 0;
    for (int i=0; i<n; ++i) {
        vector<int> sub_sz;
        for (auto[j, _]: E[i]) {
            if (j != p[i]) {
                sub_sz.push_back(S[j]);
            }
        }
        int sum = accumulate(sub_sz.begin(), sub_sz.end(), 0);
        if (i != 0) sub_sz.push_back(n-1-sum);
        
        int M = *max_element(sub_sz.begin(), sub_sz.end());
        if (M >= n/2) {
            ll tmp = 0;
            for (auto[j, C]: E[i]) tmp += C;
            tmp += (ll)(M+1) * (n-M);
            ans = max(ans, tmp);
        } else {
            ll tmp = 0;
            for (auto[j, C]: E[i]) tmp += C;
            vector<vector<int>> polys;
            priority_queue<pii> pq;
            int single_cnt = 0;
            for (int w: sub_sz) {
                if (w == 1) {
                    single_cnt++;
                    continue;
                }
                vector<int> p(w+1, 0);
                p[0] = p[w] = 1;
                pq.push({ -w, polys.size() });
                polys.push_back(p);
            }

            while (pq.size() >= 2) {
                int a = pq.top().second;
                pq.pop();
                int b = pq.top().second;
                pq.pop();
                vector<int> p;
                multiply(polys[a], polys[b], p);
                while (!p.empty() && p.back() == 0) p.pop_back();
                pq.push({ -(p.size()+1), polys.size() });
                polys.push_back(p);
            }

            int min_diff = 1e9;
            if (polys.empty()) {
                min_diff = (n & 1 ? 0 : 1);
            } else {
            for (int i=0; i<polys.back().size(); ++i) {
                // cout << i << ' ' << polys.back()[i] << endl;
                if (polys.back()[i] > 0) {
                    if (abs(i - (n-1-single_cnt-i)) <= single_cnt) {
                        min_diff = (n & 1 ? 0 : 1);
                        break;
                    } else {
                        int a = i;
                        int b = n-1-single_cnt-i;
                        if (a > b) swap(a, b);
                        min_diff = min(min_diff, b-a-single_cnt);
                    }
                }
            }
            }
            int x = (n-1-min_diff) / 2;
            ans = max(ans, tmp + (ll)(x+1) * (x+min_diff+1));
        }
    }
    cout << ans;

    return 0;
}