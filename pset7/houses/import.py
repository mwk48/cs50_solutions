import csv
from sys import argv, exit
import cs50
if len(argv)!=2:
    print("error")
    exit()
open("students.db", "w").close()
db = cs50.SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")
with open(argv[1], "r") as csvfile:
    rows = csv.DictReader(csvfile)
    for row in rows:
        temp=row["name"].split()
        print(temp)
        if len(temp)==2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?)", temp[0] , temp[1], row["house"], int(row["birth"]))
        elif len(temp)==3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",temp[0] ,temp[1] , temp[2], row["house"], int(row["birth"]))