def solve():
    n, x = list(map(int, input().split()))
    arr = sorted(list(map(int, input().split())))

    cumsum = 0 
    k = 0
    for i, a in enumerate(arr):
        if cumsum + a <= x:
            cumsum += a
            k = i + 1
        else:
            k = i
            break

    #  print(k, cumsum)

    #  print()
    res = 0
    ds = 0
    while k > 0:
        if cumsum > x:
            break

        days = (x - cumsum) // k + 1
        #  print(f"cumsum: {cumsum}")
        #  print(f"k: {k}; days: {days}")
        res += k * days 
        cumsum += ((k-1) * days) - (arr[k-1] + ds)
        ds += days
        k -= 1

        while cumsum > x:
            cumsum -= (arr[k-1] + ds)
            k -= 1

    print(res)


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        solve()
