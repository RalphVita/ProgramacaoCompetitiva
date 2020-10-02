import re
import sys

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Tranforma tudo em lista de inteiro
regex = [[int(r) for r in re.findall("(\d+)",line)]
            for line in lst]

#Pega os salários que não são nem o minimo nem o maximo
cases = [ [r2 for r2 in r if r2 not in [max(r),min(r)]] for r in regex[1:]]

#Imprime
for i in range(0,regex[0][0]):
    print('Case',str(i+1)+":",cases[i][0])