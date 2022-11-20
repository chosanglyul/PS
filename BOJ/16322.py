import sys
input = sys.stdin.readline

l, m = map(int, input().split())
lawns = [input().split(',') for _ in range(m)]
lawns = [[l[0], *list(map(int, l[1:]))] for l in lawns]

lawn = []
mip = 101010
week = 10080
for s, p, c, t, r in lawns:
    can = True
    rot, lft = week//(t+r), week%(t+r)
    cur_rot, cur_lft = 0, 0
    for cnt in range(week):
        tmp_lft = cur_lft + lft
        cur_rot += rot+tmp_lft//(t+r)
        cur_lft = tmp_lft%(t+r)
        mowe = (cur_rot*t+min(cur_lft, t))*c
        if mowe < (cnt+1)*l:
            break
    else:
        if p < mip:
            lawn = [s]
            mip = p
        elif p == mip:
            lawn.append(s)

if len(lawn) == 0:
    print('no such mower')
else:
    for s in lawn: print(s)
