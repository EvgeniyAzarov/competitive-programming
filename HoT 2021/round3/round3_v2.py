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

    
    dists = [[float('inf')] * n for _ in range(n)]

    for i in range(n):
        dists[i][i] = 0

    for i, j in edges:
        dists[i][j] = dists[j][i] = 1

    for l in range(n):
        for i in range(n):
            for j in range(n):
                d = dists[i][l] + dists[l][j]
                if dists[i][j] > d:
                    dists[i][j] = dists[j][i] = d

    maxdists = [(-1, None, None) for _ in range(k)]
    for i in range(n):
        for j in range(i+1, n):
            l = 0 
            while l < k and dists[i][j] > maxdists[l][0]:
                if l > 0:
                    maxdists[l-1] = maxdists[l]
                l += 1

            if l > 0:
                maxdists[l-1] = (dists[i][j], i, j)
    
    for md in maxdists:
        print(md[1]+1, md[2]+1)

