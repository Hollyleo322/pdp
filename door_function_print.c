#include <stdio.h>
#include <math.h>
#define Y 21
#define X 43
char graf[Y][X];

void init_xy()
{
    for (int i = 0; i < X - 1; i++)
    {
        if (i == X / 2)
        {
            graf[0][i] = '|';
            continue;
        }

        graf[0][i] = ' ';
    }
    graf[0][X] = '\0';
}
void print_graf()
{
    for (int i = 0; i < Y; i++)
        printf("%s", graf[i]);
}

double anesi(double x)
{
    double res = 1 / (1 + pow(x, 2));
    return res;
}
double bernuli(double x)
{
    double res = sqrt((1 + 2 * x) - pow(x, 2) - 1);
    // printf("bernuli = %.7lf\n", res);
    return res;
}
double giperbola(double x)
{
    double res = 1 / pow(x, 2);
    return res;
}

int main()
{
    double compare = 0.000000;
    double x = 3.1415927;
    double result = (x + x) / 41;
    double oops = -3.1415927;
    for (int i = 0; i < 42; i++)
    {
        printf("%.7lf | %.7lf |", oops, anesi(oops));
        if (bernuli(oops) > compare)
            printf(" %.7lf |", bernuli(oops));
        else
            printf(" - |");
        printf("%.7lf\n", giperbola(oops));
        double pios = oops + result;
        oops = pios;
    }
    init_xy();
    print_graf();
    return 0;
}