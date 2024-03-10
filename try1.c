#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define speed_1 10000000
#define speed_2 300000
#define speed_3 500000
#define speed_4 700000
#define speed_5 1000000

#define Y 25
#define X 80

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
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++)
            scanf("%d", &pole[i][j]);
}
int count(int pole[][X])
{
    int res = 0;
    for (int i = 0; i < Y; i++)
        for (int j = 0; j < X; j++)
            res += pole[i][j];
    return res;
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
void show_pole(int pole[][X])
{
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            if (pole[i][j] == 0)
                printw(" ");
            else
                printw("*");
        }
        printw("\n");
    }
    refresh();
    step_pole(pole);
}
int check_speed(char ch, int *stop)
{
    int speed;
    if (ch == '1')
        speed = speed_1;
    else if (ch == '2')
        speed = speed_2;
    else if (ch == '3')
        speed = speed_3;
    else if (ch == '4')
        speed = speed_4;
    else if (ch == '5')
        speed = speed_5;
    else if (ch == 'q')
        *stop = 1;
    return speed;
}

// MAIN
// ---------------------------------------
int main()
{
    int pole[Y][X];
    int time_mili_sec = speed_1;
    int stop = 0;

    init_rand(pole);
    if (freopen("/dev/tty", "r", stdin))
        initscr(); // Инициализация ncurses
    nodelay(stdscr, true);
    noecho();
    curs_set(0);

    // Основной цикл игры
    while (stop != 1)
    {
        char control_button = getch();

        if (count(pole) == 0)
        {
            stop = 1;
        }

        time_mili_sec = check_speed(control_button, &stop);

        usleep(time_mili_sec);
        clear();
        show_pole(pole);
    }

    endwin(); // Выход из ncurses
    return 0;
}
