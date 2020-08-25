import csv
from sys import argv, exit
if len(argv)!=3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()
result=[]
temp=[]
with open(argv[1], newline='') as csvfile:
    rows = csv.reader(csvfile)
    for row in rows:
        temp.append(row)
    result.extend(temp)
    temp=[]
file = open(argv[2], "r")
text=""
for sequence in file:
    text+=sequence
file.close()
compare=[]
compare_string=""
index=1
while True:
    try:
        compare_string=result[0][index]
        while True:
            if text.count(compare_string)==0:
                compare.append(len(compare_string)//len(result[0][index])-1)
                break
            compare_string+=result[0][index]
        index+=1
    except:
        break
for i in range(1,len(result)):
    for j in range(1,len(result[1])):
        if int(result[i][j])!=compare[j-1]:
            break
        else:
            if j==len(result[1])-1:
                print(result[i][0])
                exit()
print("No match")
