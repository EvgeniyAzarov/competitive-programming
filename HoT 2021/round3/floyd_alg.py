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
    paths = [[[-1]*n for j in range(n)] for i in range(n)]

    for i in range(n):
        paths[i][i] = [i]

    for i, j in edges:
        paths[i][j] = [i, j] 
        paths[j][i] = [j, i]

    for l in range(n):
        for i in range(n):
            for j in range(n):
                if len(paths[i][l]) + len(paths[l][j]) < len(paths[i][j]):
                    paths[i][j] = paths[j][i] = \
                            paths[i][l] + paths[l][j][1:]


    for i in range(n):
        for j in range(n):
            print(i, j, paths[i][j])

