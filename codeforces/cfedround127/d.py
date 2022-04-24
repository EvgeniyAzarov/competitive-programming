def solve():
    n, x = list(map(int, input().split()))
    arr = list(map(int, input().split()))

    #  print()
    #  print(arr)

    res = 0
    for i in range(1, len(arr)):
        res += abs(arr[i] - arr[i-1])

    amin = min(arr)
    amax = max(arr)

    if x > amax:
        res += min((x - amax) + (x-amax+1) - 1, (x-arr[-1]), x-arr[0])

    if amin > 1:
        res += min((amin-1) + (amin-1+1) - 1, arr[0] - 1, arr[-1] -1 )

    print(res)


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        solve()
