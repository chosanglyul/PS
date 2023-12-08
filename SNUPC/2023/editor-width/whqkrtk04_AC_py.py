n, k = list(map(int, input().split()))
s = input()
idx = [0]
for i in range(1, n):
    if s[i-1] != s[i]:
        idx.append(i)
idx.append(n)
ran = []
for i in range(1, len(idx)):
    if idx[i]-idx[i-1] >= k:
        ran.append((idx[i-1], idx[i]))
for j in range(n, 0, -1):
    ans = 0
    for s, e in ran:
        if s//j == e//j: ans = max(ans, e-s)
        elif s//j+1 == e//j: ans = max(ans, e%j, j-s%j)
        else: ans = max(ans, j)
        if ans >= k: break
    if ans < k:
        print(j)
        break
