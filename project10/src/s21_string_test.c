#include "s21_string.h"

void s21_strlen_test()
{
    char *test_1 = "DAROVA BRATUHA";
    char *test_2 = "Щас бы шавухи";
    char *test_3 = "aaaaaaaaaaaaaaaaaaaa";
    int test_int_1 = 14;
    int test_int_2 = 15;
    int test_int_3 = 20;

    printf("%s\n", test_1);
    printf("%d\n", s21_strlen(test_1));
    printf("%s\n", test_int_1 == s21_strlen(test_1) ? "SUCCESS" : "FAIL");
    printf("%s\n", test_2);
    printf("%d\n", s21_strlen(test_2));
    printf("%s\n", test_int_2 == s21_strlen(test_2) ? "SUCCESS" : "FAIL");
    printf("%s\n", test_3);
    printf("%d\n", s21_strlen(test_3));
    printf("%s\n", test_int_3 == s21_strlen(test_3) ? "SUCCESS" : "FAIL");
}
void s21_strcmp_test()
{
    char *test_1_first = "abc";
    char *test_1_second = "abc";
    int res_1 = 0;
    char *test_2_first = "Sbc";
    char *test_2_second = "qwe";
    int res_2 = 0;
    char *test_3_first = "abc";
    char *test_3_second = "Abc";
    int res_3 = 1;
    printf("%s %s\n", test_1_first, test_1_second);
    printf("%d\n", s21_strcmp(test_1_first, test_1_second));
    printf("%s\n", res_1 == s21_strcmp(test_1_first, test_1_second) ? "SUCCESS" : "FAIL");
    printf("%s %s\n", test_2_first, test_2_second);
    printf("%d\n", s21_strcmp(test_2_first, test_2_second));
    printf("%s\n", res_2 == s21_strcmp(test_2_first, test_2_second) ? "SUCCESS" : "FAIL");
    printf("%s %s\n", test_3_first, test_3_second);
    printf("%d\n", s21_strcmp(test_3_first, test_3_second));
    printf("%s\n", res_3 == s21_strcmp(test_3_first, test_3_second) ? "SUCCESS" : "FAIL");
}
void s21_strcpy_test()
{
    char test_1_first[N];
    char *test_1_second = "abc";
    char test_2_first[N];
    char *test_2_second = "qwe";
    char test_3_first[N];
    char *test_3_second = "";
    printf("%s\n", test_1_second);
    printf("%s\n", s21_strcpy(test_1_first, test_1_second));
    printf("%s\n", s21_strcmp(test_1_first, test_1_second) == 0 ? "SUCCESS" : "FAIL");
    printf("%s\n", test_2_second);
    printf("%s\n", s21_strcpy(test_2_first, test_2_second));
    printf("%s\n", s21_strcmp(test_2_first, "HAHA") == 0 ? "SUCCESS" : "FAIL");
    printf("%s\n", test_3_second);
    printf("%s\n", s21_strcpy(test_3_first, test_3_second));
    printf("%s\n", s21_strcmp(test_3_first, test_3_second) == 0 ? "SUCCESS" : "FAIL");
}
void s21_strcat_test()
{
    char test_1_first[N] = "ABC";
    char *test_1_second = "abc";
    char test_2_first[N] = "oue";
    char *test_2_second = "qwe";
    char test_3_first[N] = "asdfgh";
    char *test_3_second = "qwertyuiopasd";
    char *res_1 = s21_strcat(test_1_first, test_1_second);
    char *res_2 = s21_strcat(test_2_first, test_2_second);
    char *res_3 = s21_strcat(test_3_first, test_3_second);
    printf("%s %s\n", test_1_first, test_1_second);
    printf("%s\n", res_1);
    printf("%s\n", s21_strcmp(res_1, "ABCabc") == 0 ? "SUCCESS" : "FAIL");
    printf("%s %s\n", test_2_first, test_2_second);
    printf("%s\n", res_2);
    printf("%s\n", s21_strcmp(res_2, "Bratishka") == 0 ? "SUCCESS" : "FAIL");
    printf("%s %s\n", test_3_first, test_3_second);
    printf("%s\n", res_3);
    printf("%s\n", s21_strcmp(res_3, "asdfghqwertyuiopasd") == 0 ? "SUCCESS" : "FAIL");
}
void s21_strchr_test()
{
    char *test_1_first = "abc";
    char test_1_second = 'a';
    char *test_2_first = "qwe";
    char test_2_second = 'c';
    char *test_3_first = "hello";
    char test_3_second = 'h';
    char *res_1 = s21_strchr(test_1_first, test_1_second);
    char *res_2 = s21_strchr(test_2_first, test_2_second);
    char *res_3 = s21_strchr(test_3_first, test_3_second);
    printf("%s %c\n", test_1_first, test_1_second);
    if (res_1)
        printf("%c\n", *res_1);
    printf("%s\n", res_1 ? "SUCCESS" : "FAIL");
    printf("%s %c\n", test_2_first, test_2_second);
    if (res_2)
        printf("%c\n", *res_2);
    printf("%s\n", res_2 ? "SUCCESS" : "FAIL");
    printf("%s %c\n", test_3_first, test_3_second);
    if (res_3)
        printf("%c\n", *res_3);
    printf("%s\n", res_3 ? "SUCCESS" : "FAIL");
}
void s21_strstr_test()
{
    char *test_1_first = "abcdefghq";
    char *test_1_second = "defg";
    char *test_2_first = "korzina";
    char *test_2_second = "dsa";
    char *test_3_first = "hello";
    char *test_3_second = "hello";
    char *res_1 = s21_strstr(test_1_first, test_1_second);
    char *res_2 = s21_strstr(test_2_first, test_2_second);
    char *res_3 = s21_strstr(test_3_first, test_3_second);
    printf("%s %s\n", test_1_first, test_1_second);
    if (res_1)
        printf("%s\n", res_1);
    printf("%s\n", res_1 ? "SUCCESS" : "FAIL");
    printf("%s %s\n", test_2_first, test_2_second);
    if (res_2)
        printf("%s\n", res_2);
    printf("%s\n", res_2 ? "SUCCESS" : "FAIL");
    printf("%s %s\n", test_3_first, test_3_second);
    if (res_3)
        printf("%s\n", res_3);
    printf("%s\n", res_3 ? "SUCCESS" : "FAIL");
}
