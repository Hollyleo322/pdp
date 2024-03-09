#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define Y 80
#define X 25

int get_y(int i)
{
    return (i + Y) % Y;
}
int get_x(int j)
{
    return (j + X) % X;
}
void copy_pole(int src[][X], int dst[][X])
{
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++)
            dst[i][j] = src[i][j];
}
void init_rand(int pole[][X])
{
    srand(time(NULL));
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++)
            pole[i][j] = rand() % 2;
}
int count(int pole[][X])
{
    int res = 0;
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++)
            res += pole[i][j];
    return res;
}
void show_pole(int pole[][X])
{
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            if (pole[i][j] == 0)
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
    }
}
void step_pole(int pole[][X])
{
    int pole_cpy[Y][X];
    copy_pole(pole, pole_cpy);
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            /* (i-1 , j-1) (i -1, j) ( i -1 , j + 1)
                (i, j - 1)  (i, j + 1)
                (i+1 , j-1) (i+1, j) ( i + 1 , j + 1)*/
            int count_neig = 0;
            count_neig += pole_cpy[get_y(i - 1)][get_x(j - 1)];
            count_neig += pole_cpy[get_y(i - 1)][get_x(j)];
            count_neig += pole_cpy[get_y(i - 1)][get_x(j + 1)];
            count_neig += pole_cpy[get_y(i)][get_x(j - 1)];
            count_neig += pole_cpy[get_y(i)][get_x(j + 1)];
            count_neig += pole_cpy[get_y(i + 1)][get_x(j - 1)];
            count_neig += pole_cpy[get_y(i + 1)][get_x(j)];
            count_neig += pole_cpy[get_y(i + 1)][get_x(j + 1)];
            if ((pole_cpy[i][j] == 0) && (count_neig == 3))
                pole[i][j] = 1;
            else if (count_neig < 2 || count_neig > 3)
                pole[i][j] = 0;
        }
    }
}
int main()
{
    int pole[Y][X];
    init_rand(pole);
    while (1)
    {
        show_pole(pole);
        step_pole(pole);
        usleep(100000);
        if (!count(pole))
            break;
        system("clear");
    }
    return 0;
}