def f(s):
    return sum(map(int, s.split('+')))

s = input().split('-')
x = f(s[0])
for idx, ss in enumerate(s):
    if idx == 0: continue
    x -= f(ss)
print(x)
