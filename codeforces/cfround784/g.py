if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n, m = list(map(int, input().split()))
        a = []
        for _ in range(n):
            a.append(list(input()))

        for c in range(m):
            e = len(a) - 1
            for r in range(len(a)-1, -1, -1):
                if a[e][c] != '.' and a[r][c] == '.':
                    e = r
                if a[r][c] == '*':
                    if a[e][c] == '.':
                        a[e][c] = "*"
                        a[r][c] = "."
                        e -= 1  
                    else:
                        e = r
                if a[r][c] == "o":
                    e = r
        #  print()
        for row in a:
            print("".join(row))
