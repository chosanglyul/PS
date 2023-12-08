#include <bits/stdc++.h>
using namespace std;

#define eb emplace_back
#define all(v) (v).begin(),(v).end()

const int MAXN = 400010;

int N, Q;
int A[MAXN];
vector<int> P[MAXN];
bool know[MAXN];
int seg[4 * MAXN][2], ov[4 * MAXN][2];

void mknod(int idx, int l, int r) {
    if(l == r) {
        if(know[l]) seg[idx][0] = 1, ov[idx][0] = 0;
        else {
            ov[idx][0] = 1;
            if(!know[l] && know[l + 1] && A[l] != A[l + 1]) seg[idx][0] = 2;
            else seg[idx][0] = 1;
        }

        seg[idx][1] = 0;
        ov[idx][1] = 0;
    }
    else {
        for(int i = 0; i < 2; i++) {
            seg[idx][i] = seg[idx * 2][i] + seg[idx * 2 + 1][ov[idx * 2][i]];
            ov[idx][i] = ov[idx * 2 + 1][ov[idx * 2][i]];
        }
    }
}

void mkseg(int idx, int l, int r) {
    if(l < r) {
        int m = (l + r) / 2;
        mkseg(idx * 2, l, m);
        mkseg(idx * 2 + 1, m + 1, r);
    }
    mknod(idx, l, r);
}

void updseg(int idx, int l, int r, int x) {
    if(l < r) {
        int m = (l + r) / 2;
        if(x <= m + 1) updseg(idx * 2, l, m, x);
        if(x >= m) updseg(idx * 2 + 1, m + 1, r, x);
    }
    mknod(idx, l, r);
}
void updseg(int x) {
    updseg(1, 0, 2 * N - 1, x);
}

int f(int x) {
    return P[A[x]][0] == x ? 0 : 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N >> Q;
    for(int i = 0; i < 2 * N; i++) cin >> A[i];

    for(int i = 0; i < 2 * N; i++) {
        know[i] = !P[A[i]].empty();
        P[A[i]].eb(i);
    }

    mkseg(1, 0, 2 * N - 1);

    cout << seg[1][0] << "\n";

    while(Q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;

        if(A[l] != A[r]) {
            P[A[l]][f(l)] = r;
            sort(all(P[A[l]]));
            know[P[A[l]][0]] = false;
            know[P[A[l]][1]] = true;

            P[A[r]][f(r)] = l;
            sort(all(P[A[r]]));
            know[P[A[r]][0]] = false;
            know[P[A[r]][1]] = true;

            swap(A[l], A[r]);

            updseg(P[A[l]][0]);
            updseg(P[A[l]][1]);
            updseg(P[A[r]][0]);
            updseg(P[A[r]][1]);
        }

        cout << seg[1][0] << "\n";
    }
}