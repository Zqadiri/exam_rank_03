#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

struct  data
{
    int  w;
    int  h;
    char c;
}       data;

struct rectangle
{
    char  r;     // the character r
    float x;     // horizontal position of the top left corner of the rectangle
    float y;     // vertical position of the top left corner of the rectangle
    float w;     // the width of the rectangle
    float h;     // the height of the rectangle
    char  c;     // the char use to draw the rectangle
}       rec;

int     quit(FILE *fp)
{
    write(1, "Error: Operation file corrupted\n", 32);
    if (fp)
        fclose(fp);
    return (1);
}

int	 check_cor(float x, float y, float rec_x, float rec_y, float width, float height)
{
	if (x < rec_x || x > rec_x + width || y < rec_y || y > rec_y + height)
		return (0);
	else if (x - rec_x < 1.00000 || (rec_x + width) - x < 1.00000 ||
			y - rec_y < 1.00000 || (rec_y + height) - y < 1.00000)
		return (1);
	return (2);
}

int     main(int argc, char **argv)
{
    char result[90000]; //300 * 300 
    struct data data;
    struct rectangle rec;
    FILE *fp;
    int  ret;

    if (argc != 2)
    {
        write (1, "Error: arguments\n", 17);
        return (1);
    }
    if (!(fp = fopen(argv[1], "r")))
        return (quit(fp));
    if (fscanf(fp, "%d %d %c\n", &data.w, &data.h, &data.c) != 3)
        return (quit(fp));
    if (data.w < 0 || data.w > 300 || data.h < 0 || data.h > 300) 
        return (quit(fp));
    memset (result, data.c, data.w * data.h);
    while ((ret = fscanf(fp, "%c %f %f %f %f %c\n", &rec.r, &rec.x, &rec.y,
    &rec.w, &rec.h, &rec.c)) == 6)
    {
        if (rec.w <= 0 || rec.h <= 0 || (rec.r != 'r' && rec.r != 'R'))
            return (quit(fp));
        for (int y = 0; y < data.h; y++)
        {
            for (int x = 0; x < data.w ; x++)
            {
                int i = check_cor((float)x, (float)y, rec.x, rec.y, rec.w, rec.h);
                if (i == 1 || (i == 2 && rec.r == 'R'))
                    result[y * data.w + x] = rec.c;
            }
        }
    }
    if (ret != EOF)
        return (quit(fp));
    for (int i = 0; i < data.h; i++)
	{
		write(1, result + data.w * i, data.w);
		write(1, "\n", 1);
	}
    fclose (fp);
    return (1);
}