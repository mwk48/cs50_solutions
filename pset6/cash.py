from cs50 import get_float
s=get_float("Change owed: ")
temp=int(s*100)
count=0
while temp!=0:
    while temp>=25:
        count+=1
        temp-=25
    while temp>=10:
        count+=1
        temp-=10
    while temp>=5:
        count+=1
        temp-=5
    while temp>=1:
        count+=1
        temp-=1
print(count)