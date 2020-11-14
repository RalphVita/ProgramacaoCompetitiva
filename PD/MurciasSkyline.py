def Horizonte(N, H, W):
    # F[i] é a maior soma de sequencias eté i
    Fc,Fd = W.copy(), W.copy() # i,d => Crescente, Decrescente

    for i in range(N):
        for j in range (i+1,N):
            value = Fc[i] + W[j]
            if H[i] < H[j] and value > Fc[j]:
                Fc[j] = value
            
            value = Fd[i] + W[j]
            if H[i] > H[j] and value > Fd[j]:
                Fd[j] = value

    # print(H)
    # print(W)
    # print(Fc, Fd)
    return Fc, Fd
    

def Read():
    line = input()
    while line == '':
        line = input()
    return line.strip()

T = int(Read())

for t in range(T):
    N = int(Read())        
    H = [int(k) for k in Read().split(' ')]
    while len(H) < N:
        H += [int(k) for k in Read().split(' ')]
    
    W = [int(k) for k in Read().split(' ')]
    while len(W) < N:
        W += [int(k) for k in Read().split(' ')]


    Fc, Fd = Horizonte(N,H,W)
    FcM, FdM = max(Fc),max(Fd)

    _str = 'Case '+str(t+1)+'. '
    if FcM >= FdM:
        _str += 'Increasing ('+str(FcM)+'). Decreasing ('+str(FdM) + ').'
    else:
        _str += 'Decreasing ('+str(FdM)+'). Increasing ('+str(FcM) + ').'
    
    print(_str)
    