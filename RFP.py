import re
import sys

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))

#Pega os RFP, ou seja, linha no formato: [int int]
rfp = [re.findall("(^\d+\s\d+)",line) 
            for line in lst]

#Pega as proposta, ou seja, linha no formato: [float int]
propostas = [re.findall("([\d+]*[.]\d+\s\d+)",line) 
            for line in lst]


proposta = None
cont = 0
#Varre a lista de entrada, em busca do RFP != None
for index,item in enumerate(rfp, start=0):
    if item:#Quando acha um RFP
        #Se houver uma proposta vencedora, será impressa
        if proposta:
            print('RFP #'+str(cont))
            print(proposta[0])
            if item != ['0 0']:
                print()
        #Pega os parametros do RPF
        n,p = [int(x) for x in item[0].split()]
        #Zera a proposta vencedora
        proposta = None
        cont += 1
    else:
        if propostas[index]:#Quando acha uma linha com proposta
            d,r = propostas[index][0].split()
            d = float(d)
            r = int(r)
            c = r/p #Compliance
            if proposta:# Quando há uma proposta anterior, e está e posta a prova
                if c > proposta[3]:
                    proposta = [lst[index-1],d,r,c]
                elif c == proposta[3] and d < proposta[1]: #Desempate
                    proposta = [lst[index-1],d,r,c]
            else:#Quando ainda não há proposta anterior
                proposta = [lst[index-1],d,r,c]
