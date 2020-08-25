#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *jpg=NULL;
    BYTE * arr=malloc(sizeof(BYTE)*512);
    char name[8];
    int count=0;
    while (fread(arr, 512, 1, file)==1)
    {
        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] & 0xf0) == 0xe0 )
        {
            if (count==0)
            {
                sprintf(name,"%03i.jpg",count);
                jpg=fopen(name, "w");
                fwrite(arr, 512, 1, jpg);
                count+=1;
            }
            else
            {
                fclose(jpg);
                sprintf(name,"%03i.jpg",count);
                jpg=fopen(name, "w");
                fwrite(arr, 512, 1, jpg);
                count+=1;
            }
        }
        else
        {
            if (jpg!=NULL)
            {
                fwrite(arr, 512, 1, jpg);
            }
        }
    }
    free(arr);
    fclose(jpg);
    fclose(file);
}
