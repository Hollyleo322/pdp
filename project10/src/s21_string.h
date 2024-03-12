#pragma once
#include <stdio.h>
#define N 20

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
int s21_strlen(char *data);
int s21_strcmp(char *a, char *b);
char *s21_strcpy(char *dst, const char *src);
char *s21_strcat(char *dst, char *src);
void s21_strcat_test();
char *s21_strchr(char *src, int c);
void s21_strchr_test();
char *s21_strstr(char *str, char *substr);
void s21_strstr_test();