import random

if __name__ == '__main__':
    t = 1
    n = 2 * 10 ** 5
    k = 1000

    with open("e.6.test", "w") as f:
        print(t, file=f)
        print(n, k, file=f)

        for i in range(n):
            #  print(10**8 + random.randint(0, k-1), end=" ", file=f)
            print(10**8 + k-1, end=" ", file=f)


