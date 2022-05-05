if __name__ == '__main__':
    n = 10000
    with open('c.2.test', 'w') as f:
        print(n, file=f)
        for i in range(n+1):
            print(i, file=f)

