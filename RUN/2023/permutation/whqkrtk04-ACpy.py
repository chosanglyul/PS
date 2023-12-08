import sys
input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    A = [a-1 for a in list(map(int, input().split()))]
    chk = [False for _ in range(n)]
    cnt = 0
    B = list()
    for i in range(n-1):
        if A[i] <= i: cnt += 1
        else: chk[A[i]] = True
        cnt += (chk[i] == True)
        if cnt == i+1: B.append(cnt)
    print(len(B))
    print(*B)
