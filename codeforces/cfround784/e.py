if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n = int(input())
        d = {}
        for _ in range(n):
            s = input()
            d[s] = d.get(s, 0) + 1

        res = 0
        for a in d.keys():
            for b in d.keys():
                if b > a:
                    continue
                if (a[0] == b[0] and a[1] != b[1]) or (a[0] != b[0] and a[1] == b[1]):
                    res += d[a] * d[b]

        print(res)
