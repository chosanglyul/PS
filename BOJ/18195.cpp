#include "findVertices.h"
#include <bits/stdc++.h>
using namespace std;

void mktree(vector<int>& A, vector<int>& B, vector<int>& C){ 
	for(int i = 1; i < C.size(); i++) {
		A.push_back(C[i-1]+1);
		B.push_back(C[i]+1);
	}
}

int call(int n, int k) {
	vector<int> A, B, C, D;
	for(int i = 0; i < n; i++) {
		if((i&k) == k) C.push_back(i);
		else D.push_back(i);
	}
	mktree(A, B, C); mktree(A, B, D);
	return query(A, B, 1, k+1);
}

int solve(int n, int k, int diff, bool s) {
	vector<int> A, B, C, D, E, F;
	for(int i = 0; i < n; i++) {
		bool x = ((i&k) == k), y = ((i&diff) == diff);
		if(x && y) C.push_back(i);
		else if(x) D.push_back(i);
		else if(y) E.push_back(i);
		else F.push_back(i);
	}
	mktree(A, B, C); mktree(A, B, D);
	mktree(A, B, E); mktree(A, B, F);
	return query(A, B, (s ? k+1 : 1), diff+1);
}

void find(int n) {
    int diff = 0;
    vector<bool> A;
    for(int k = 1; k < n; k <<= 1) {
        bool x = call(n, k);
        A.push_back(x);
        if(x && diff == 0) diff = k;
    }
    int a = diff, b = 0;
    for(int i = 0, k = 1; k < n; i++, k <<= 1) {
        if(k == diff) continue;
        bool x = !solve(n, k, diff, A[i]);
		if(A[i]) {
            if(x) a += k;
            else b += k;
        } else {
            if(x) {
                a += k;
                b += k;
            }
        }
    }
	answer(a+1, b+1);
}