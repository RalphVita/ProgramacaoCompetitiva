import re
import sys

def array_to_string(l):
    s = ''
    for i in l:
        s += str(i)
    return s

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]


for r in regex:
    size = r[0]
    soma = r[1]
    s = soma
    i = 0
    n=[]
    decimal = 9
    while i < size:
        while decimal > s:
            decimal -= 1
        n.append(decimal)
        i += 1
        s -= decimal
    if(sum(n) != soma or (soma == 0 and len(n) > 1)):
        print(-1, -1)     
    else:
        menor = n[::-1]
        naoZero = next((i for i, x in enumerate(menor) if x != 0), None)
        if naoZero and naoZero > 0:
            menor[0] = menor[naoZero]
            menor[naoZero] = 0

        print(array_to_string(menor), array_to_string(n))