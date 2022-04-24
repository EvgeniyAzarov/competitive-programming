if __name__ == '__main__':
    n, m, k = map(int, input().split())

    g = [[] for _ in range(n)]
    edges = []

    for _ in range(m):
        x, y = map(int, input().split())
        x, y = x-1, y-1
        edges.append((x, y))
        g[x].append(y)
        g[y].append(x)

    paths = [[[-1]*(n+1) for j in range(n)] for i in range(n)]

    for i in range(n):
        paths[i][i] = [i]

    for i, j in edges:
        paths[i][j] = [i, j] 
        paths[j][i] = [j, i]

    for l in range(n):
        for i in range(n):
            for j in range(n):
                if len(paths[i][l]) + len(paths[l][j]) - 1 < len(paths[i][j]):
                    paths[i][j] = paths[j][i] = \
                            paths[i][l] + paths[l][j][1:]

    pairs = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(i+1, n):
            d = len(paths[i][j])
            l = len(paths[i][j]) - 1
            while l > 1:
                a, b = paths[i][j][l-2], paths[i][j][l]
                l -= 1

                impact = 1 / (d - 1) -  1 / d
                pairs[a][b] += impact 
                pairs[b][a] += impact 

    toadd = [(-1, None, None) for _ in range(k)]
    for a in range(n):
        for b in range(a+1, n):
            l = 0
            while l < k and pairs[a][b] > toadd[l][0]:
                l += 1
                if l > 1:
                    toadd[l-2] = toadd[l-1]
            if l > 0:
                toadd[l-1] = (pairs[a][b], a, b)
    
    for d, a, b in toadd:
        print(a+1, b+1)

