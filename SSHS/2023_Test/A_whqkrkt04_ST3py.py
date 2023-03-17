import sys
input = sys.stdin.readline

n, q = map(int, input().split())
chk = [0] * n
cnt = (n // 10) * 3
if n % 10 > 0:
    cnt += 1
if n % 10 > 3:
    cnt += 1
if n % 10 > 6:
    cnt += 1
while q > 0:
    cnt -= 1
    print(cnt)
    q -= 1