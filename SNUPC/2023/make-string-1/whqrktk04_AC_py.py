import sys

n=int(sys.stdin.readline())
s=list(sys.stdin.readline())
s.pop()
ans=[]
a=[]
while s:
    if a and a[-1] == s[-1]:
        ans.append("N")
        a.pop()
        s.pop()
    else:
        if s[-1] == "S":
            ans.append("U")
            a.extend("US")
        else:
            ans.append("S")
            a.extend("SU")
print(len(ans))
print(''.join(ans))
