#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n=get_int("Height: ");
    }
    while (n<1 || n>8);
    for (int i=0;i<n;i++)
    {
        /* print n-1 space start from the first line */
        for (int space=n;space>i+1;space--)
        {
           printf(" ");
        }
        /* print i star */
        for (int j=0;j<i+1;j++)
        {
           printf("#");
        }
        /* print 2 space every time*/
        for (int space=0;space<2;space++)
        {
           printf(" ");
        }
         /* print i star every time*/
        for (int j=0;j<i+1;j++)
        {
           printf("#");
        }
         /* add a new line */
        printf("\n");
    }
}