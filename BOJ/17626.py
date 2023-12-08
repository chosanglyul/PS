import sys
from math import sqrt

def is_square(n):
    return int(sqrt(n)) ** 2 == n

def min_squares(n):
    if is_square(n):
        return 1

    # Checking if the number can be represented as sum of two squares
    for i in range(1, int(sqrt(n)) + 1):
        if is_square(n - i * i):
            return 2

    # Checking if the number can be represented as sum of three squares
    for i in range(1, int(sqrt(n)) + 1):
        for j in range(i, int(sqrt(n - i * i)) + 1):
            if is_square(n - i * i - j * j):
                return 3

    # If it's not any of the cases above, then it's a sum of four squares
    return 4

n = int(sys.stdin.readline().strip())
result = min_squares(n)
sys.stdout.write(str(result) + '\n')
