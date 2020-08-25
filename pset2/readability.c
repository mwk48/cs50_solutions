#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
int main(void)
{
    string s=get_string("Text: ");
    int n=strlen(s);
    /* f there is 70 space, there is 71 words So space is initialized as 1 */
    int space=1,letters=0,sentences=0;
    for (int i = 0; i<n;i++)
    {
        if (isblank(s[i]))
        {
            space+=1;
        }
        else if (isalnum(s[i]))
        {
            letters+=1;
        }
        else if (s[i]=='?' || s[i]=='.' || s[i]=='!')
        {
            sentences+=1;
        }
    }
    /* round off the Coleman-Liau index*/
    int index=round(0.0588 * (100*letters)/space - 0.296 * (100*sentences)/space - 15.8);
    if (index<=0)
    {
        printf("Before Grade 1\n");
    }
    else if (index>=1 && index <=15)
    {
        printf("Grade %i\n",index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}