import csv
from sys import argv, exit
import cs50
if len(argv)!=2:
    print("error")
    exit()
db = cs50.SQL("sqlite:///students.db")
record=argv[1]
temp=db.execute("SELECT * FROM students where house=? ORDER BY last, first",record)
comp=[]
result=[]
for i in temp:
    if not i["middle"]:
        comp.append(i["first"]+" "+i["last"])
        comp.append("born" + " "+str(i["birth"]))
    else:
        comp.append(i["first"]+" "+i["middle"]+" "+i["last"])
        comp.append("born" + " "+str(i["birth"]))
    result.append(comp)
    comp=[]
for i in result:
    print(f"{i[0]}, {i[1]}")

