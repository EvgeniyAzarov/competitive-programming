from collections import deque

if __name__ == '__main__':
    n, m, k = map(int, input().split())

    g = [[] for _ in range(n)]

    for _ in range(m):
        x, y = map(int, input().split())
        x, y = x-1, y-1
        g[x].append(y)
        g[y].append(x)


    added = []

    while k > 0:
        k -= 1

        s = None 
        md = float('inf') 
        for t in range(n):
            if len(g[t]) < md:
                md = len(g[t])
                s = t
                #print(md, s)
        
        queue = deque()
        queue.append((s, 0))
        visited = [False for i in range(n)]

        maxl = 0 
        ends = []
        while queue:
            v, l = queue.popleft()
            visited[v] = True

            if l > maxl: 
                ends = [v]
                maxl = l
            elif l == maxl:
                ends.append(v)

            for u in g[v]:
                if not visited[u]:
                    queue.append((u, l+1))


        mind = float('inf') 
        end = None
        for e in ends:
            if len(g[e]) < mind:
                end = e
                mind = len(g[e])

        g[s].append(end)
        g[end].append(s)
        added.append((s, end))


    for a, b in added:
        print(a + 1, b + 1)
