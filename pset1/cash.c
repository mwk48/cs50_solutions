#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    int n, count=0;
    float cash;
    do
    {
        cash = get_float("Change owed: ");
    }
    while (cash<=0);
    n = round(0.41 * 100);
    while (n>0)
    {
        if (n>=25)
        {
            n-=25;
            count+=1;
        }
        else if (n>=10)
        {
            n-=10;
            count+=1;
        }
        else if (n>=5)
        {
            n-=5;
            count+=1;
        }
        else if (n>=1)
        {
            n-=1;
            count+=1;
        }
    }
    printf("%i\n",count);
}