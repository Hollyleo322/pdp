#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **memory_aloc(int row, int col);
int input_array(double **matrix, int row, int col);
double deter(double **matrix, int row);
void clear_arr(double **matrix, int row);
void get_matr(double **matr, int n, double **temp_matr, int row, int col);
void print_array(double **arr, int row, int col);

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
            double check_deter = deter(array, row);
            if ((int)check_deter)
            {
                double **inv_array = memory_aloc(row, col);
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < row; j++)
                    {
                        int m = row - 1;
                        double **tmp_matr = malloc(sizeof(double *) * m);
                        for (int k = 0; k < m; k++)
                        {
                            tmp_matr[k] = malloc(sizeof(double) * m);
                        }
                        get_matr(array, row, tmp_matr, i, j);
                        inv_array[i][j] = pow(-1.0, i + j + 2) * deter(tmp_matr, m) / check_deter;
                        clear_arr(tmp_matr, m);
                        print_array(inv_array, row, col);
                        free(inv_array);
                    }
                }
            }
            else
                printf("n/a");
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
double deter(double **matrix, int row)
{
    if (row == 1)
    {
        return matrix[0][0];
    }
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
            double **t = malloc(sizeof(double *) * (row - 1));
            for (int i = 0; i < row - 1; i++)
            {
                t[i] = malloc(sizeof(double) * (row - 1));
            }
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
                }
                a++;
            }
            res += pow(-1, (double)j + 2) * matrix[0][j] * deter(t, row - 1);
            clear_arr(t, row - 1);
        }
        return res;
    }
}

void clear_arr(double **matrix, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
void get_matr(double **matr, int n, double **temp_matr, int row, int col)
{
    int ki = 0;
    int kj = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != row)
        {
            for (int j = 0; j < n; j++)
            {
                if (j != col)
                {
                    temp_matr[ki][kj] = matr[i][j];
                    kj++;
                }
            }
            ki++;
        }
    }
}
void print_array(double **arr, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%.6lf", arr[i][j]);
        }
        printf("\n");
    }
}