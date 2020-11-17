n = int(input())
A = [int(a) for a in input().split(' ')]
m = int(input())
Q = [int(q) for q in input().split(' ')]

size = sum(A)
F = [0]*size
N = 0
for i in range(size):
    if(A[N] == 0):
        N += 1
    A[N] -=1
    F[i] = N+1
    

[print(F[q-1]) for q in Q]