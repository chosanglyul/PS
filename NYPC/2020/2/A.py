n = int(input())
code = ['+', '-', '/', '*', '.']
for i in range(n):
    ok = False
    a, b, c, d = map(int, input().split())
    for j in code:
        for k in code:
            if j == k or ok: continue
            ans = eval('{}{}{}{}{}'.format(a, j, b, k, c))
            if ans == d :
                print('{}{}{}{}{}={}'.format(a, j, b, k, c, d))
                ok = True