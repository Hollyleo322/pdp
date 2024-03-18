#include <stdio.h>
#include <stdlib.h>
#define LENFILE 1000
void cesar();
char *crypt(FILE *f, int n);

int main(void)
{
    int n;
    char c;
    char array_file[LENFILE];
    FILE * log = log_init("logger.txt");
    while (1)
    {
        scanf("%d%c", &n, &c);
        if (n == 1)
        {
            fscanf(stdin, "%s", array_file);
            FILE *ptr_file = fopen(array_file, "r");
            if (ptr_file)
            {
                logcat(log,"file is open")
                char a = fgetc(ptr_file);
                if (a != EOF)
                {
                    printf("%c", a);
                    char output[LENFILE];
                    while (fgets(output, LENFILE, ptr_file))
                    {
                        printf("%s", output);
                        printf("\n");
                    }
                    fclose(ptr_file);
                }
                else
                    printf("n/a\n");
            }
            else
                printf("n/a\n");
        }
        else if (n == 2)
        {
            char array_file_2[LENFILE];
            fgets(array_file_2, LENFILE, stdin);
            if (fopen(array_file, "r"))
            {
                FILE *ptr_file_2 = fopen(array_file, "a");
                if (ptr_file_2)
                {
                    fprintf(ptr_file_2, "%s", array_file_2);
                    fclose(ptr_file_2);
                    ptr_file_2 = fopen(array_file, "r");
                    char output_2[LENFILE];
                    while (fgets(output_2, LENFILE, ptr_file_2))
                    {
                        printf("%s", output_2);
                    }
                    fclose(ptr_file_2);
                }
                else
                    printf("n/a\n");
            }
            else
                printf("n/a\n");
        }
        else if (n == 3)
        {
            cesar();
        }
        else if (n == -1)
        {
            break;
        }
    }
    return 0;
}
void cesar()
{
    printf("Введите сдвиг\n");
    int n;
    if (scanf("%d", &n) == 1 && n != 0)
    {
        FILE *one_c = fopen("ai_modules/m1.c", "r");
        FILE *two_c = fopen("ai_modules/m2.c", "r");
        FILE *one_h = fopen("ai_modules/m1.h", "r");
        FILE *two_h = fopen("ai_modules/m2.h", "r");
        char c = fgetc(one_c);
        if (c != EOF)
        {
            char *res = crypt(one_c, n);
            fclose(one_c);
            one_c = fopen("ai_modules/m1.c", "w");
            fprintf(one_c, "%s", res);
            free(res);
            fclose(one_c);
        }
        c = fgetc(two_c);
        if (c != EOF)
        {
            char *res = crypt(two_c, n);
            fclose(two_c);
            two_c = fopen("ai_modules/m2.c", "w");
            fprintf(two_c, "%s", res);
            free(res);
            fclose(two_c);
        }
        c = fgetc(one_h);
        if (c != EOF)
        {
            fputs("", one_h);
        }
        c = fgetc(two_h);
        if (c != EOF)
        {
            fputs("", two_h);
        }
    }
    else
        printf("n/a\n");
}
char *crypt(FILE *f, int n)
{
    char *res = malloc(sizeof(char) * LENFILE);
    int i = 0;
    fseek(f, 0, SEEK_SET);
    char c = fgetc(f);
    while (c != EOF)
    {
        res[i] = (c + n) % 128;
        c = fgetc(f);
        i++;
    }
    return res;
}