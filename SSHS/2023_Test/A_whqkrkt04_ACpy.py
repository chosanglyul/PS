import sys
input = sys.stdin.readline

n, q = map(int, input().split())
chk = [0] * n
cnt = 0

for i in range(n):
    chk[i] = i % 10 == 0 or i % 10 == 3 or i % 10 == 6
    cnt += chk[i]

while q > 0:
    x = int(input()) - 1
    cnt -= chk[x]
    chk[x] = 1 - chk[x]
    cnt += chk[x]
    print(cnt)
    q -= 1