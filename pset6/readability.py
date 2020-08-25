from cs50 import get_string
s=get_string("Text: ")
sentence=0
word=1
letter=0
for i in s:
    if i==' ':
        word+=1
    elif i.isalpha():
        letter+=1;
    elif i=='?' or i=='.' or i=='!':
        sentence+=1;
index=round(0.0588 * letter/(word/100)- 0.296 /(word/100)* sentence - 15.8)
if index<1:
    print("Before Grade 1")
elif index>=1 and index<=15:
    print(f"Grade {index}")
elif index>=16:
    print("Grade 16+")