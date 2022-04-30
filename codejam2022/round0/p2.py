import numpy as np

t = int(input())

for c in range(t):
    print(f'Case #{c+1}: ', end='')

    arr = []
    for i in range(3):
        inp = list(map(int, input().split()))
        arr.append(inp)
    arr = np.array(arr)

    brr = arr.min(axis=0)
    
    diff = brr.sum() - 1e6
    if diff < 0: 
        print("IMPOSSIBLE")
        continue
    
    i = 0
    while diff != 0:
        n = min(brr[i], diff)
        brr[i] = brr[i] - n
        diff -= n
        i += 1

    print(" ".join(list(map(str, brr))))
    


