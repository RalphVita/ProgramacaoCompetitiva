#Inpirado em:
#https://zhuanlan.zhihu.com/p/103796326
n, m = tuple([int(x) for x in input().split(' ')])
P = [[int(x) for x in input().split(' ')] for i in range(m)]


G = [[0]*n]*n
N = [0]*n
count = 0


for i in range(m):
    G[P[i][0]-1][P[i][1]-1] = 1
    G[P[i][1]-1][P[i][0]-1] = 1
    N[P[i][0]-1] += 1
    N[P[i][1]-1] += 1

while True:

    key = 0
    for i in range(n):
        if N[i] == 1:
            key = 1
            for j in range(n):
                G[i][j] = 0
                G[j][i] = 0

    for i in range(n):
        N[i] = 0
        for j in range(n):
            N[i] += G[i][j]

    if key > 0: 
        count += 1
    else: 
        break

print(count)
