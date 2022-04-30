t = int(input())

for i in range(t):
    r, c = list(map(int, input().split()))
    
    print(f"Case #{i+1}")
    
    for m in range(2*r+1):
        if m < 2:
            print("..", end='')
        elif m % 2 == 0:
            print("+-", end='')
        else:
            print("|.", end='')
            
        for n in range(c-1):
            if m % 2 == 0:
                print("+-", end='')
            else:
                print("|.", end='')

        if m % 2 == 0:
            print("+", end='')
        else:
            print("|", end='')
        print()

