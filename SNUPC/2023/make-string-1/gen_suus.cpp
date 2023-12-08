#include "testlib.h"
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

string make_rand(int N, int K) {
    string str = "";
    int cur = 0;
    for(int i = 0; i < N; i++) {
        cur = rnd.next(N-i);
        if(cur < K) {
            str += "S";
            K--;
        } else str += "U";
    }
    return str;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int N = opt<int>("N");
    int R = opt<int>("R");
    int T = opt<int>("T");
    assert(N%2 == 0 && R%2 == 0 && R < N/4);

    string str;
    N -= 3*R+4;
    assert(N%4 == 0);

    int tmp = rnd.next(1, 2);
    if(tmp == 1) str += "UU";
    else str += "SS";
    str += make_rand(R, R/2);
    
    vector<char> SU = {'S', 'U'};
    if(T&1) swap(SU[0], SU[1]);
    
    
    for(int i = 0; i < N/4; i++) {
        if(T&2) {
            str += SU[0];
            str += SU[1];
            str += SU[1];
        } else str += SU[0];
    }
    
    str += make_rand(R, R/2);

    for(int i = 0; i < N/4; i++) {
        if(!(T&2)) {
            str += SU[1];
            str += SU[1];
            str += SU[0];
        } else str += SU[0];
    }
    
    str += make_rand(R, R/2);
    if(tmp == 2) str += "UU";
    else str += "SS";

    N += 3*R+4;
    assert((int)str.size() == N);
    println(N);
    println(str);
	return 0;
}
