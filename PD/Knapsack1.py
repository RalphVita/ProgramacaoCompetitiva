import re
import sys

Weitghts = [0]
Values = [0]
F = []

def Inicializar(N, W):
    global F, Weitghts, Values

    Weitghts = [0]
    Values = [0]
    #F = [[ (0 if x == 0 or y == 0  else 0) for x in range(W+1)] for y in range(N+1)]

def MFKnapsack2(i, j):
    global F, Weitghts, Values
    if F[i][j] < 0:
        if j < Weitghts[i]:
            value = MFKnapsack(i-1, j)
        else:
            value = max(MFKnapsack(i-1, j), Values[i] + MFKnapsack(i-1, j - Weitghts[i]))
        F[i][j] = value
    return F[i][j]

def MFKnapsack3(N, W):
    global F, Weitghts, Values
    i, j = 0, 0
    while i <= N:
        j = W
        while j >= Weitghts[i]:
            value = Values[i] + F[i-1][j-Weitghts[i]]
            if value > F[i-1][j]:
                F[i][j] = value
            else:
                F[i][j] = F[i-1][j]
            j -= 1
        i += 1
    return F[N][W]

def MFKnapsack(N, W):
    global Weitghts, Values
    F = [0 for x in range(W+1)]

    for i in range(N+1):
        for j in range (W,Weitghts[i]-1, -1):
            value = Values[i] + F[j-Weitghts[i]]
            if value > F[j]:
                F[j] = value
        i += 1
    return F[W]

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]

lst = enumerate(regex)
for idx, item in lst:
    N, W = item[0], item[1]
    Inicializar(N, W)

    i = 0
    while i < N:
        line = lst.__next__()[1]
        Weitghts.append(line[0])
        Values.append(line[1])
        i += 1
    print(MFKnapsack(N,W))
    #print(F)