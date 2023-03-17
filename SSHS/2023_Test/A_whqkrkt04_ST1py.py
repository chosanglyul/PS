import sys
input = sys.stdin.readline

n, q = map(int, input().split())
x = int(input())
print((n // 10) * 3 - 1)