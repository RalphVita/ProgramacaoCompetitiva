
N = 3
S = [1,2,3]

i = 0
while i < (1 << N):
    s = "{ "
    j = 0
    while j < N:
        if (i & (1 << j)):
            s += str(S[j]) + ' '
        j +=1
    s += '}'
    print(s)
    i += 1

