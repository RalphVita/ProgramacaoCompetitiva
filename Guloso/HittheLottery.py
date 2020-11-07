import re
import sys


#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]

for r in regex:
    notas = [100, 20, 10, 5, 1]
    valor = r[0]
    count = 0
    while(valor > 0):
        while valor < notas[0]:
            notas.pop(0)
        count += int(valor/notas[0])
        valor = valor % notas[0]        
    print(count)