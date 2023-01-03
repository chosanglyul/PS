import sys
input = sys.stdin.readline
P = 1000000007

n = int(input())
A = map(int, input().split())
B = [0]*n
for i in A: B[i-1] += 1
ans = 1
for i in B: ans = ans*(i+1)%P
print((ans-1+P)%P)