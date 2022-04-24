def check_parity(arr):
    if len(arr) == 0:
        return True
    x = arr[0] % 2
    for a in arr:
        if a % 2 != x:
            return False
    return True


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n = int(input())
        arr = list(map(int, input().split()))

        cond = False

        if len(arr) < 2: 
            cond=True
        else:
            cond = check_parity(arr[::2]) and check_parity(arr[1::2])

        if cond:
            print('YES')
        else:
            print('NO')


