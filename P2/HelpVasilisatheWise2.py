r1, r2 = tuple([int(x) for x in input().split(' ')])
c1, c2 = tuple([int(x) for x in input().split(' ')])
d1, d2 = tuple([int(x) for x in input().split(' ')])

v = [0,0,0,0]
for i in range(1,10):
    v[0] = i
    v[1] = r1 - v[0]
    v[2] = c1 - v[0]
    v[3] = r2 - v[2]
    if v[0]+v[1] == r1 and v[2] + v[3] == r2 and v[0]+v[2] == c1 and v[1] + v[3] == c2 and v[0]+v[3] == d1 and v[1] + v[2] == d2:
        if(min(v) > 0 and max(v) < 10):
            break
print(v[0],v[1])
print(v[2],v[3])