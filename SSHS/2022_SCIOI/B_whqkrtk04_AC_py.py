import sys
input = sys.stdin.readline
P = 998244353
MAX = 202020

n, x, y = map(int, input().split())
A = list(map(int, input().split()))
B = [[0]*x for _ in range(MAX//x+1)]
C = [0]*MAX
for i in A:
    B[i//x][i%x] += 1
    C[i//x] += 1

ans = 0
for i in range(len(B)):
    for j in range(x):
        cnt = 0
        if i > 0: cnt += B[i-1][j]
        if j > 0: cnt += B[i][j-1]
        if i > 0 and j > 0: cnt -= B[i-1][j-1]
        ans = (ans+B[i][j]*cnt)%P
        B[i][j] += cnt

tmp, su = 0, 0
C = C[::-1]
for i in range(MAX):
    ans = (ans+tmp*C[i])%P
    su = (su+C[i])%P
    tmp = (tmp+su)%P
print((ans*y)%P, end=' ')

ans = 0
for i in range(1, n):
    if A[i] > A[0]:
        ans += (A[i]-A[0])//x+1
print((ans*y)%P)