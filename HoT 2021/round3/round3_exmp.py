n, m, k = map(int, input().split())
g = []
for _ in range(n):
    g += [[0] * n]

for _ in range(m):
    x, y = map(int, input().split()) 
    x -= 1
    y -= 1
    g[x][y] = g[y][x] = 1

for i in range(n):
    for j in range(i + 1, n):
        if k > 0 and g[i][j] == 0:
            print(i + 1, j + 1)
            k -= 1

