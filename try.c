#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **memory_aloc(int row, int col);
int input_array(double **matrix, int row, int col);
double deter(double **matrix, int row, double **t);

int main()
{
    int row, col;
    int check_scan = scanf("%d %d", &row, &col);
    if (row > 1 && col > 1 && row == col && check_scan == 2)
    {
        double **array = memory_aloc(row, col);
        int check_array = input_array(array, row, col);
        if (check_array == (row * col) && array != NULL)
        {
            double **t = memory_aloc(row, row);
            printf("%.6lf", deter(array, row, t));
            free(t);
        }
        else
            printf("n/a");
        free(array);
    }
    else
        printf("n/a");
    return 0;
}

double **memory_aloc(int row, int col)
{
    double **buf = malloc(sizeof(double *) * row + sizeof(double) * row * col);
    double *ptr = (double *)buf + row;
    for (int i = 0; i < row; i++)
    {
        buf[i] = ptr + i * col;
    }
    return buf;
}
int input_array(double **matrix, int row, int col)
{
    int res = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            res += scanf("%lf", &matrix[i][j]);
        }
    }
    return res;
}
double deter(double **matrix, int row, double **t)
{
    if (row == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    else
    {
        int a, b;
        double res = 0;

        for (int j = 0; j < row; j++)
        {
            a = 0;
            for (int k = 1; k < row; k++)
            {
                b = 0;
                for (int s = 0; s < row; s++)
                {
                    if (s != j)
                    {
                        t[a][b] = matrix[k][s];
                        b++;
                    }
                    a++;
                }
            }
            res += pow(-1, (double)j + 2) * matrix[0][j] * deter(t, row - 1);
        }
        return res;
    }
}