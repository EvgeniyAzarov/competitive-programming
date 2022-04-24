import numpy as np

if __name__ == '__main__':
    N = 20
    testfiles = [f'tests/test{i}' for i in range(N)]
    
    for testfile in testfiles:
        print(testfile)
        
        with open(testfile) as tin:
            n, m, k = map(int, tin.readline().split())

            g = [[] for _ in range(n)]
            edges = []

            for _ in range(m):
                x, y = map(int, tin.readline().split())
                x, y = x-1, y-1
                edges.append((x, y))
                g[x].append(y)
                g[y].append(x)

        deg = [0] * n
        n_edges = 0
        for i, j in edges:
            deg[i] += 1
            deg[j] += 1
            n_edges += 1

        print(f'vertexes: {n} \t mean deg: {np.array(deg).mean()}')
        print(f'edges: {n_edges} / {n*(n-1)/2};\t dens: {n_edges / (n*(n-1)/2)}')
        print()


     
