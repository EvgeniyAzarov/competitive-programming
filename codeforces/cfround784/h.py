if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n, k = list(map(int, input().split()))
        arr = list(map(int, input().split()))

        d = {}
        for pos in range(31):
            for i, a in enumerate(arr):
                if (a >> pos) & 1 == 0:
                    d[pos] = d.get(pos, []) + [i] 

        for pos in range(30, -1, -1):
            if 0 < len(d.get(pos, [])) <= k:
                for i in d.get(pos):
                    arr[i] = arr[i] | (1 << pos)
                    k -= 1 
                d[pos] = []

        res = arr[0] 
        if len(arr) > 1:
            for a in arr[1:]:
                res &= a
        print(res)

