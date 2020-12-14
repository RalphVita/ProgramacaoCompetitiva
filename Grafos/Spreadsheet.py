import re

P = int(input())


#Mapeia as letras das colunas
coluna = {}
count = 0
for i in range(65,91,1):
    coluna[chr(i)] = count
    count += 1

for i in range(65,91,1):
    for j in range(65,91,1):
        coluna[chr(i)+chr(j)] = count
        count += 1

for i in range(65,91,1):
    for j in range(65,91,1):
        for k in range(65,91,1):
            coluna[chr(i)+chr(j)+chr(k)] = count
            count += 1


for p in range(P):
    C,L = tuple([int(x) for x in input().split(' ')])
    M = [[x for x in input().split(' ')] for l in range(L)]

    for l in range(L):
        for c in range(C):
            referencias = [r for r in re.findall("([A-Z]+\d+)",M[l][c])]
    #print(M)