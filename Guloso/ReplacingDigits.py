import re
import sys

def to_matrix(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

def array_to_string(l):
    s = ''
    for i in l:
        s += str(i)
    return s

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))


matrix = to_matrix(lst,2)
digitos = [0,0,0,0,0,0,0,0,0,0,0]

for m in matrix:
    n = [int(i) for i in list(m[0])]
    _min = min(n)
    #util = sorted([int(i) for i in list(m[1]) if int(i) > min(n)],reverse=True)[0:len(n)]
    #util = sorted(set([j for j in [int(i) for i in list(m[1])] if j > _min]),reverse=True)
    for i in m[1]:
        digitos[int(i)] += 1
    i = 0
    j = 9
    while i < len(n) and j > 0:
        while i < len(n) and j > 0 and digitos[j] > 0:
            if j > n[i]:
                n[i] = j
                digitos[j] -= 1
            i += 1
        j -= 1
        
    print(array_to_string(n))
