#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

struct  data
{
    int     w;
    int     h;
    char    c;
}       data;

struct  circle
{
    float X;    // a float, the horizontal position of the center of the circle
    float Y;    // a float, the vertical position of the center of the circle
    float R;    // RADIUS: a positive float but not 0, the radius of the circle
    char  C;    // the character c
    char CHAR;  // the char use to draw the circle  
}       circle;


int     quit(FILE *fp)
{
    write(1, "Error: Operation file corrupted\n", 32);
    if (fp)
        fclose(fp);
    return (1);
}

int fill_circle(int x, int y, struct circle *circle)
{
    float x1 = x;
    float x2 = y;
    float xb = circle->X;
    float yb = circle->Y;

    
    return (1);
}


int main(int argc, char **argv)
{
    struct circle circle;
    struct data data;
    char result[100000];
    FILE *fp;
    int ret = 0; // fscanf returns the number of items of the argument list successfully filled.

    if (argc != 2)
    {
      	write(1, "Error: argument\n", 16);
		return (1);
    }
    (!(fp = fopen(argv[1] ,"r"))) ? quit(fp) : 1;
    /*
    ** Parsing :
    */

    /*
    ** int fscanf(FILE *stream, const char *format, ...)
    ** stream Pointer to a FILE object that identifies the input stream to read data from.
    ** 
    ** WIDTH HEIGHT BACKGROUND_CHAR 
    */
    if (fscanf(fp, "%d %d %c\n", &data.w, &data.h, &data.c) != 3)
        quit(fp);
    printf ("%d\n", data.h);
    printf ("%d\n", data.w);
    printf ("%c\n", data.c);
    if (data.w < 0 || data.w > 300 || data.h < 0 || data.h > 300)   
        quit (fp);
    // fill the background
    memset (result, data.c, data.w * data.h);
    while ((ret = fscanf(fp, "%c %f %f %f %c", &circle.C, &circle.X,
    &circle.Y, &circle.R, &circle.CHAR)) == 5)
    {
        printf ("%c\n", circle.C );
        printf ("%f\n", circle.X );
        printf ("%f\n", circle.Y );
        printf ("%f\n", circle.R );
        printf ("%c\n", circle.CHAR );
        if (circle.R < 0 || (circle.C != 'c' && circle.C != 'C'))
            quit (fp);
        for (int y = 0; y < data.h; y++)
        {
            for (int x = 0; x < data.w; x++)
            {
                if (fill_circle(x, y, &circle))
                    result[y * data.w + x]  = circle.CHAR;
            }
        }
    }
    for (int i = 0; i < data.h; i++)
	{
		write(1, result + data.w * i, data.w);
		write(1, "\n", 1);
	}
    fclose(fp);
    return (0);
}