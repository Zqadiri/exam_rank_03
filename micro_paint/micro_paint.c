#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

struct  data
{
    int w;
    int h;
    char c;
}       data;

int     quit(FILE *fp)
{
    write(1, "Error: Operation file corrupted\n", 32);
    if (fp)
        fclose(fp);
    return (1);
}

int     main(int argc, char **argv)
{
    FILE *fp;

    if (argc != 2)
    {
        write (1, "Error: arguments\n", 16);
        return (1);
    }
    if (!(fp = fopen(argv[1], "r")))
        quit(fp);
    /*
    **  Parsing :
    */
    if (fscanf(fp, "%d %d %c\n", &data.w, &data.h, &data.c) != 3)
        quit(fp);
    printf ("h : %d\n", data.h);
    printf ("w : %d\n", data.w);
    printf ("c : %c\n", data.c);
    if (data.w < 0 || data.w > 300 || data.h < 0 || data.h > 300)   
        quit (fp);
    return (1);
}