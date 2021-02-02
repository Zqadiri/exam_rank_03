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

struct rectangle
{
    char r;     // the character r
    float x;    // horizontal position of the top left corner of the rectangle
    float y;    // vertical position of the top left corner of the rectangle
    float w;    // the width of the rectangle
    float h;    // the height of the rectangle
    char c;     // the char use to draw the rectangle
}       rec;

struct Rectangle
{
    char  R;    // the character r
    float X;    // horizontal position of the top left corner of the rectangle
    float Y;    // vertical position of the top left corner of the rectangle
    float W;    // the width of the rectangle
    float H;    // the height of the rectangle
    char  C;    // the char use to draw the rectangle
}       Rec;

int     quit(FILE *fp)
{
    write(1, "Error: Operation file corrupted\n", 32);
    if (fp)
        fclose(fp);
    return (1);
}

int     main(int argc, char **argv)
{
    char result[90000]; //300 * 300 
    struct data data;
    struct rectangle rec;
    struct Rectangle Rec; 
    FILE *fp;
    int  ret;

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
    {
        quit (fp);
        return (1);
    } 
    memset (result, data.c, data.w * data.h);
    /*
    **  Draw an empty rectangle
    */
    while ((ret = fscanf(fp, "%c %f %f %f %c\n", &rec.r, &rec.x, &rec.y,
    &rec.w, &rec.h, &rec.c)) == 5)
    {
        if (rec.w <= 0 || rec.h <= 0 || rec.r != 'r')
        {
            quit(fp);
            return (1);
        }
        if (Rec.W <= 0 || Rec.H <= 0 || Rec.R != 'R')
        {
            quit(fp);
            return (1);
        }
        if (rec.r == 'r')
            draw_empty_rectangle(&rec);
        else if (Rec.R == 'R')
            draw_filled_rectangle(&Rec);
        /*
        ** ... 
        */
    }
    for (int i = 0; i < data.h; i++)
	{
		write(1, result + data.w * i, data.w);
		write(1, "\n", 1);
	}
    return (1);
}