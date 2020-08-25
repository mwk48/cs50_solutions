#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, string argv[])
{
    /*check if contain exactly 2 arguments*/
    if (argc==2)
    {
        /*check if string is composed of digit, not english letters*/
        string temp=argv[1];
        int temp_len=strlen(temp);
        for (int i = 0; i<temp_len;i++)
        {
            /*if there is sth other than digit*/
            /*print error message and return*/
            if (isdigit(temp[i])==false)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        printf("Success\n");
        }
    }
    /*if the length of arguments is not 2*/
    /*print error message and return*/
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    /*atoi: string to integer*/
    int swift=atoi(argv[1]);
    string plain=get_string("plaintext:  ");
    int n=strlen(plain);
   /*algorithm for caesar cipher. Range of %26: 0-25(inclusive)*/
    for (int i = 0; i<n;i++)
    {
        if (isalpha(plain[i]))
        {
            if (islower(plain[i]))
            {
                plain[i]='a'+(plain[i]-'a'+swift)%26;
            }
            else
            {
                plain[i]='A'+(plain[i]-'A'+swift)%26;
            }
        }
    }
    printf("ciphertext: %s\n",plain);
}