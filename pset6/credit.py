from cs50 import get_int
num=get_int("Number: ")
rec=len(str(num))
temp=int(str(num)[0:2])
total=0
count=1
comp=0
while num!=0:
    if count%2==1:
        total+=num%10
        num=num//10
    else:
        comp=2*(num%10)
        if comp>=10:
            total+=comp//10+comp%10
            num=num//10
        else:
            total+=comp%10
            num=num//10
    count+=1
if total%10==0 and count>=13:
    if temp==34 or temp==37:
        print("AMEX\n")
    elif temp>=51 and temp<=55:
        print("MASTERCARD\n");
    elif temp//10==4:
        print("VISA\n");
    else:
        print("INVALID\n");
else:
    print("INVALID\n");
