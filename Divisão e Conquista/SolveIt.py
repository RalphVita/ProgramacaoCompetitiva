import re
import sys
import math
from decimal import Decimal

#Lista de Entradas
lst = []
for line in sys.stdin:
    lst.append(line.rstrip("\n"))


regex = [[int(r) for r in re.findall("(-?\d+)",line)]
            for line in lst]

#p ∗ e^−x + q ∗ sin(x) + r ∗ cos(x) + s ∗ tan(x) + t ∗ x^2 + u = 0
equation = lambda x, p, q, r, s, t, u: p * (math.e**-x) + q * math.sin(x) + r * math.cos(x) + s * math.tan(x) + t*x*x + u

for R in regex:
    if(len(R) == 6):
        x = Decimal('0.5')
        delta = Decimal('0.1')
        minDelta = Decimal('0.0001')
        achou = False
        r = {}
        #Xs = []
        sinal = 1
        while x <= 1.0:
            result = equation(*([x.__float__()]+R))
            if result > -delta*10 and result < delta*10 and delta > minDelta:
                delta /= 10

            if result > -0.001 and result < 0.001:
                r[abs(result)] = x
                #r.append(abs(result))
                #Xs.append(x)
                achou = True
            elif achou and sinal > 0:
                sinal = -1
            elif achou and sinal < 0:
                break
            if not achou:
                x+= (delta if result > 0 else -delta)
            else:
                x+= delta*sinal

        if len(r) > 0:
            v = min([ k for k, v in sorted(r.items(), key=lambda item: item[1])])
            print(r[v])
            #print( Xs[r.index(min(r))])
        else:
            print('No solution')