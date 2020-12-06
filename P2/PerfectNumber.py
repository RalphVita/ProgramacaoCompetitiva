n = int(input())


soma_digitos = lambda a : sum([int(i) for i in list(str(a))])

n = 1
while n < 100:
    i = 0
    count = 0
    while count < n:
        i+=1
        if soma_digitos(i) == 10:
            count += 1



    #PA com a0 = 19 e razão 9
    an = 19 + (n-1)*9
    #print(an)

    print(n,i,an, i-an)
    n+=1