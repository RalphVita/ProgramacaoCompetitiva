n = int(input())
P = [int(x) for x in input().split(' ')]

path = {1,n}
i = n-2
while i > 0:
    path.add(P[i])
    i = P[i]-2


print(' '.join(str(e) for e in  sorted(path)))