import sys
input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    A = list(map(int, input().split()))
    x, y, mex = 0, 0, 1
    for i in range(30):
        y += 2**i
        B = sorted(list(set([a&y for a in A])))
        tmp = 0
        for j in range(len(B)):
            if tmp != B[j]: break
            else: tmp += 1
        if mex < tmp: x, mex = y, tmp
    print(x)
