#include <stdio.h>

#define MULT_DAY 86400
#define MULT_HOUR 3600
#define MULT_MIN 60
typedef struct data
{
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    int seconds;
    int status;
    int code;
} data;
#define DEF_SIZE 1000
int count_time(data *first, data *second);
int count_sec(data *structura);
void output(FILE *file);
void sort(FILE *file, char *path);

int main(void)
{
    char path[DEF_SIZE];
    fscanf(stdin, "%s", path);
    FILE *binary_file = fopen(path, "rb+");
    if (binary_file)
    {
        int n;
        char c;
        scanf("%d%c", &n, &c);
        if (n == 0)
        {
            output(binary_file);
            fclose(binary_file);
        }
        else if (n == 1)
        {
            sort(binary_file, path);
            output(binary_file);
            fclose(binary_file);
        }
        else
            printf("n/a");
    }
    else
        printf("n/a");
    return 0;
}
void output(FILE *file)
{
    if (file == NULL)
        return;
    data res = {};
    while (fread(&res, sizeof(res), 1, file))
    {
        printf("%d %d %d %d %d %d %d %d\n", res.year, res.month, res.day, res.hour, res.minutes, res.seconds, res.status, res.code);
    }
}
void sort(FILE *file, char *path)
{
    data first;
    data second;
    int lenght = 0;
    data tmp_s;
    FILE *tmp;
    while (fread(&first, sizeof(first), 1, file))
    {
        lenght += 1;
    }
    // int count_ok = 0;
    printf("dlina = %d\n", lenght);
    tmp = fopen("tmp.bin", "wb");
    for (int i = 0; i < lenght; i++)
    {
        if (i != 0)
        {
            fclose(file);
            fclose(tmp);
            tmp = fopen("tmp.bin", "rb");
            file = fopen(path, "wb");
            while (fread(&tmp_s, sizeof(tmp_s), 1, tmp))
            {
                fwrite(&tmp_s, sizeof(tmp_s), 1, file);
            }
            fclose(file);
            fclose(tmp);
            file = fopen(path, "rb");
            tmp = fopen("tmp.bin", "wb");
        }
        fseek(file, 0, SEEK_SET);
        for (int j = i + 1; j < lenght; j++)
        {
            /*count_ok += 1;
            printf("0k %d\n", count_ok);*/
            fread(&first, sizeof(first), 1, file);
            fread(&second, sizeof(first), 1, file);
            int res = count_time(&first, &second);
            if (res < 0)
            {
                fwrite(&first, sizeof(first), 1, tmp);
                fseek(file, -32, SEEK_CUR);
            }
            else if (res > 0)
            {
                fwrite(&second, sizeof(second), 1, tmp);
                fseek(file, -32, SEEK_CUR);
            }
        }
    }
    fclose(tmp);
}
int count_time(data *first, data *second)
{
    int res = 0;
    if (first->year != second->year)
    {
        res = first->year - second->year;
    }
    else
    {
        if (first->month != second->month)
        {
            res = first->month - second->month;
        }
        else
        {
            res = count_sec(first) - count_sec(second);
        }
    }
    return res;
}
int count_sec(data *structura)
{
    int res = structura->day * MULT_DAY + structura->hour * MULT_HOUR + structura->minutes * MULT_MIN + structura->seconds;
    return res;
}
