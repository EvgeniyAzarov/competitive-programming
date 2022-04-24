def solve():
    s = input()
    s = s + 'x'
    cc = s[0]
    cl = 0
    mark = True

    for c in s:
        #  print(cl)
        if c == cc:
            cl += 1
        else:
            if cl == 1:
                mark = False
                break
            cc = c
            cl = 1

    if mark:
        print('YES')
    else:
        print('NO')

if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        solve()
