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
        string temp=argv[1];
        int temp_len=strlen(temp);
        /*if the len of argument is not 26*/
        /*print error message and return*/
        if (temp_len!=26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        for (int i = 0; i<temp_len;i++)
        {
            if (!isalpha(temp[i]))
            {
                /*if there is sth other than alphabetic letter*/
                /*print error message and return*/
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
            for (int j = i+1; j<temp_len;j++)
            {
                /*if there is repeated letter*/
                /*print error message and return*/
                if (temp[i]==temp[j])
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
        }
        printf("Success\n");
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string swift=argv[1];
    string plain=get_string("plaintext:  ");
    int n=strlen(plain);
    /*unified the substitution key*/
    for (int i = 0; i<26;i++)
    {
        swift[i]=toupper(swift[i]);
    }
   /*algorithm for substitution cipher*/
    for (int i = 0; i<n;i++)
    {
        if (islower(plain[i]))
        {
            plain[i]=tolower(swift[plain[i]-'a']);
        }
        else if (isupper(plain[i]))
        {
            plain[i]=swift[plain[i]-'A'];
        }
    }
    printf("ciphertext: %s\n",plain);
}