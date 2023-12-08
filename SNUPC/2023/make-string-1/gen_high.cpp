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
    assert(N%2 == 0 && R%2 == 0 && R < N/4);
    int K = (N/2);
    string str;

    N -= 2*R+2;
    K -= R+1;
    int H = K-R/2;

    int tmp = rnd.next(1, 2);
    if(tmp == 1) str += 'U';
    else str += 'S';
    str += make_rand(R, R/2);
    if(rnd.next(1, 2) == 1) {
        for(int i = 0; i < H; i++) str.push_back('U');
        str += make_rand(R, R/2);
        for(int i = 0; i < H; i++) str.push_back('S');
    } else {
        for(int i = 0; i < H; i++) str.push_back('S');
        str += make_rand(R, R/2);
        for(int i = 0; i < H; i++) str.push_back('U');
    }
    str += make_rand(R, R/2);
    if(tmp == 2) str += 'U';
    else str += 'S';

    N += 2*R+2;
    assert((int)str.size() == N);
    println(N);
    println(str);
	return 0;
}
