if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n = int(input())
        w = list(map(int, input().split()))
    
        l = 0
        r = n-1

        resl = 0 
        resr = 0

        sl = w[l] 
        sr = w[r] 
        #  print()
        while l < r:
            #  print(sl, sr)
            if sl == sr:
                resl = l
                resr = r
                l += 1
                r -= 1
                sl += w[l]
                sr += w[r]
            elif sl < sr:
                l += 1
                sl += w[l]
            elif sl > sr:
                r -= 1
                sr += w[r]

        res = 0 
        if resl > 0 or resr > 0:
            res = resl+1 + (n-resr) 
        #  print(resl, resr)
        print(res)

