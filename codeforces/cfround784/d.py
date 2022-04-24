def check_bin(s):
    if s == '':
        return True
    if len(s) == 1:
        return False

    if len(set(s)) == 2:
        return True

    return False


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n = int(input())
        arr = list(input().split('W'))
        #  print(arr)

        ans = True 
        for s in arr:
            if not check_bin(s):
                ans=False

        if ans:
            print("YES")
        else:
            print("NO")


