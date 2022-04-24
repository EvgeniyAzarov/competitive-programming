if __name__ == '__main__':
    t = int(input())

    for _ in range(t):
        n = int(input())
        arr = list(map(int, input().split()))

        d = {}
        for a in arr:
            d[a] = d.get(a, 0) + 1
            if d[a] >= 3:
                print(a)
                break
        else:
            print(-1)


