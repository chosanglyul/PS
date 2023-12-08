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

// 0-base index
// return: pmt[i] = s[0..i]의 prefix, suffix가 모두 가능한 문자열의 최대 길이
// return: KMP[i] = ith matched begin position
// Helper: b means begin, m means matched
vector<int> get_pmt(const string& s) {
    int n = s.size();
    vector<int> pmt(n, 0);
    // except finding itself by searching from s[0]
    int b = 1, m = 0;
    // s[b + m]: letter to compare
    while (b + m < n) {
        if (s[b+m] == s[m]) {
            pmt[b+m] = m + 1;
            m++;
        } else {
            if (m > 0) {
                b += m - pmt[m-1];
                m = pmt[m-1];
            } else {
                b++;
            }
        }
    }
    return pmt;
}

// 0-base index
// sa[i]: lexicographically (i+1)'th suffix (of d letters)
// lcp[i]: lcp between sa[i] and sa[i+1]
// r[i]: rank of s[i..n-1] when only consider first d letters
// nr: temp array for next rank
// cnt[i]: number of positions which has i of next rank
// rf[r]: lexicographically first position which suffixes (of d letters) has rank r
// rdx[i]: lexicographically (i+1)'th suffix when only consider (d+1)'th ~ 2d'th letters
void suffix_array(string S, vector<int> &sa, vector<int> &lcp) {
    int n = S.size();
    vector<int> r(n), nr(n), rf(n), rdx(n);
    sa.resize(n); lcp.resize(n);

    for (int i = 0; i < n; i++) sa[i] = i;
    sort(sa.begin(), sa.end(), [&](int a, int b) { return S[a] < S[b]; });
    for (int i = 1; i < n; i++) r[sa[i]] = r[sa[i - 1]] + (S[sa[i - 1]] != S[sa[i]]);

    for (int d = 1; d < n; d <<= 1) {
        for (int i = n - 1; i >= 0; i--) {
            rf[r[sa[i]]] = i;
        }
        int j = 0;
        for (int i = n - d; i < n; i++) rdx[j++] = i;
        for (int i = 0; i < n; i++) {
            if (sa[i] >= d) rdx[j++] = sa[i] - d;
        }
        for (int i = 0; i < n; i++) {
            sa[rf[r[rdx[i]]]++] = rdx[i];
        }
        nr[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (r[sa[i]] != r[sa[i - 1]]) {
                nr[sa[i]] = nr[sa[i - 1]] + 1;
            }
            else {
                int prv = (sa[i - 1] + d >= n ? -1 : r[sa[i - 1] + d]);
                int cur = (sa[i] + d >= n ? -1 : r[sa[i] + d]);
                nr[sa[i]] = nr[sa[i - 1]] + (prv != cur);
            }
        }
        swap(r, nr);
        if (r[sa[n-1]] == n-1) break;
    }
    for (int i = 0, len = 0; i < n; ++i, len = max(len - 1, 0)) {
        if (r[i] == n - 1) continue;
        for (int j = sa[r[i] + 1]; S[i + len] == S[j + len]; ++len);
        lcp[r[i]] = len;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    vector<int> pi = get_pmt(s);
    int n = s.size(), m; cin >> m;
    for(int i = 1; i <= min(n, m); i++) {
        string tmp(s.begin()+pi[i-1], s.begin()+i);
        string ans(s.begin(), s.begin()+i);
        // cout << pi[i-1] << " " << i << " " << tmp << " " << ans << endl;
        while(ans.size() < m) ans.append(tmp);
        while(ans.size() > m) ans.pop_back();
        cout << ans << endl;
        /*
        vector<int> sa, lcp, sainv;
        suffix_array(ans+"$"+s, sa, lcp);
        for(auto i : lcp) cout << i << " ";
        cout << endl;
        sainv.resize(sa.size());
        for(int i = 0; i < sa.size(); i++) sainv[sa[i]] = i;
        int score = 0;
        for(int j = 0; j < m; j++) {
            // sa[j] .. sa[m+1]
            int x = min(sainv[j], sainv[m+1]), y = max(sainv[j], sainv[m+1]);
            int cnt = INF;
            for(int k = x; k < y; k++) cnt = min(cnt, lcp[k]);
            score += cnt;
        }
        cout << score << endl;
        */
        int score = 0;
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < min(n, m-j); k++) {
                if(s[k] != ans[j+k]) break;
                else score++;
            }
        }
        cout << score << endl;
    }
    return 0;
}