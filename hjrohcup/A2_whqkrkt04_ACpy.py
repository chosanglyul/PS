import sys
input = sys.stdin.readline
n, m = map(int, input().split())
print(n*m-((n*m)%2))
for i in range(1, m+1): print(f'1 {i}')
if n%2 == 1:
    for j in range(2, n-2, 2):
        for i in range(m, 1, -1): print(f'{j} {i}')
        for i in range(2, m+1): print(f'{j+1} {i}')
    for i in range(m, 1, -2):
        print(f'{n-1} {i}')
        print(f'{n} {i}')
        print(f'{n} {i-1}')
        print(f'{n-1} {i-1}')
    if m%2 == 1: print(f'{n-1} {1}')
    for j in range(n-2, 1, -1): print(f'{j} {1}')
else:
    for j in range(2, n, 2):
        for i in range(m, 1, -1): print(f'{j} {i}')
        for i in range(2, m+1): print(f'{j+1} {i}')
    for i in range(m, 0, -1): print(f'{n} {i}')
    for j in range(n-1, 1, -1): print(f'{j} {1}')