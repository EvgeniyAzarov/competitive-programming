t = int(input())

for i in range(t):
    print(f"Case #{i+1}: ", end="")
    n = int(input())
    s = list(map(int, input().split()))
    s = sorted(s)

    #  print(s)
    cur = 1
    for k in s:
        if k >= cur:
            cur += 1
    
    print(cur - 1)
