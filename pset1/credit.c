#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    long long n;
    int count=1, check_type,total =0, comp;
    n = get_long("Number: ");
    while (n>0)
    {
        /* extract the first two digits for credit card number */
        if (n>=10 && n<100)
        {
            check_type=n;
        }
        if (count%2==1)
        {
            total+=n%10;
            n=n/10;
        }
        else
        {
            comp=2*(n%10);
            /* if comp==10, total+=1, if comp==12, total+=3
             * total += digit sum of comp
             */
            if (comp>=10)
            {
                total+=floor(comp/10)+comp%10;
            }
            else
            {
                total+=comp;
            }
            n=n/10;
        }
        count+=1;
    }
    /*check if number is a valid credit card number */
    if (total%10==0 && count>=13)
    {
        if (check_type==34 || check_type==37)
        {
            printf("AMEX\n");
        }
        else if (check_type>=51 && check_type<=55)
        {
            printf("MASTERCARD\n");
        }
        else if (round(check_type/10)==4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}