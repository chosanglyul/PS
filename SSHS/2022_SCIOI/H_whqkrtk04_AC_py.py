import sys
input = sys.stdin.readline
P = 1000000007

n, s = map(int, input().split())
s -= 1
A = list(map(int, input().split()))

B = []
tmp = [0, 0]
for i in range(s, -1, -1):
    tmp[0] += A[i]
    tmp[1] = min(tmp[0], tmp[1])
    if tmp[0] > 0:
        B.append(tmp)
        tmp = [0, 0]

su, ans, j = 0, 0, 0
for i in range(s, n):
    su += A[i]
    if su < 0: break
    while j < len(B) and -B[j][1] <= su:
        su += B[j][0]
        j += 1
    ans = max(ans, su)
print(ans)