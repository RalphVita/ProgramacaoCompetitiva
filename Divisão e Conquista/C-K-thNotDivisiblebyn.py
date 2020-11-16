def Baixaria(n,k):
    if k < n:
        return k
    #Cresce de (n-1) em (n-1)
    i = int(k/(n-1))*n
    k -= (n-1)*int(k/(n-1))
    while k > 0:
        if i % n != 0:
            k -= 1
        i += 1
    return i-1

#https://codeforces.com/blog/entry/77161
need = lambda n,k : int((k - 1) / (n - 1))


N = int(input())        
I = [[int(k) for k in input().split(' ')] for _ in range(N)]

[print(need(i[0],i[1]) + i[1]) for i in I]
