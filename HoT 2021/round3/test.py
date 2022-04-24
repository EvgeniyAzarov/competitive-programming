import sys
import subprocess
import time



def run_prog(command, testfile):
    start_time = time.time()
    with open(testfile) as test_input:
        proc = subprocess.run(
            command,
            stdin=test_input,
            capture_output=True)
    end_time = time.time()

    out = proc.stdout.decode('utf-8')
    res = []
    for line in out.split('\n'):
        if line: 
            edge = tuple(map(lambda x: x-1, map(int, line.split())))
            res.append(edge)

    return res, end_time - start_time


if __name__ == '__main__':
    runcommand = None
    if len(sys.argv) > 1:
        pfile = sys.argv[1]
        if len(pfile.split('.')) > 1:
            command = f'python {pfile}'
        else:
            command = f'./{pfile}'

    verbose = False
    if len(sys.argv) > 2:
        test = sys.argv[2]
        testfiles = [f'tests/test{test}']
        verbose = True
    else:
        N = 22
        testfiles = [f'tests/test{i}' for i in range(N)]

    
    for testfile in testfiles:
        edges_to_add, runtime = run_prog(command, testfile) 
        
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
        
        skipTest = False
        for x, y in edges_to_add:
            if y not in g[x]:
                edges.append((x, y))
                g[x].append(y)
                g[y].append(x)
            else:
                print(testfile, 'Wrong answer')
                print(x+1, y+1)
                skipTest = True
                break

        if skipTest:
            continue

        paths = [[[-1]*n for j in range(n)] for i in range(n)]

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


        score = 0
        for i in range(n):
            for j in range(i+1, n):
                score += 1 / (len(paths[i][j]) - 1)
                #  print(i, j, paths[i][j])

        score = int((score * 2 / (n * (n-1))) * 10 ** 7)
        print(f"{testfile}: {score}\t (time {runtime})\t (input {n}, {m}, {k})")
        if verbose:
            for x, y in edges_to_add:
                print(x+1, y+1)
            print()



