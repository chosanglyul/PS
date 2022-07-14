n, s = list(map(int,input().split()))
par = []
for i in range(n):
    t, b = input().split()
    par.append((int(b), t))
par.sort(reverse=True)
ind = 0
dap = []

while s>0 and ind<len(par):
    while ind<len(par) and par[ind][0]>s:
        ind+=1
    if ind<len(par):
        s-=par[ind][0]
        dap.append(par[ind][1])
        ind+=1
if s>0:
    dap.clear()

print(len(dap))
for x in dap:
    print(x)
 