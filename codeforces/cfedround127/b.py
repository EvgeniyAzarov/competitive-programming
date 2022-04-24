def solve():
    n = int(input())
    a = list(map(int, input().split()))


    k = a[-1] - a[0] - n + 1

    if k >= 3:
        print("NO")
    else:
        print("YES")

if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        solve()
