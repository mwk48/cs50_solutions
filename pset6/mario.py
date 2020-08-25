from cs50 import get_int
while True:
    n=get_int("Height: ")
    if n>=1 and n<=8:
        break
for i in range(n):
    for j in range(n-1,i,-1):
        print(" ",end="")
    for j in range(0,i+1):
        print("#",end="")
    for j in range(2):
        print(" ",end="")
    for j in range(0,i+1):
        print("#y",end="")
    print()