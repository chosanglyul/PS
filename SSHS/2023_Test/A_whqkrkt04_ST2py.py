import sys
input = sys.stdin.readline

n, q = map(int, input().split())
Q = []
for i in range(q):
    x = int(input()) - 1
    Q.append(x)
    chk = [j % 10 == 0 or j % 10 == 3 or j % 10 == 6 for j in range(n)]
    for j in range(i + 1):
        chk[Q[j]] = 1 - chk[Q[j]]
    ans = sum(chk)
    print(ans)