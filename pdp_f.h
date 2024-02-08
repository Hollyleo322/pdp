#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;
#define REG_SIZE 8
extern word reg[REG_SIZE];
#define pc reg[7]
#define MEM_SIZE (64 * 1024)
#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3
#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_N 4
#define HAS_R 8
#define HAS_XX 16
typedef struct
{
    word val; // значение аргумента
    word adr; // адресс аргумента

} Arg;
extern Arg ss;
extern Arg dd;
extern int log_level;
int set_log_level(int level);
void log_pdp(int level, const char *format, ...);
void load_file(const char *filename);
void mem_dump(Adress adr, int size);
void load_data();
void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress a);
void run();
Arg get_mr(word w);
void test_mov_command();
void cmd_parse(word w);
void test_moda1_command();
void test_moda1_command_reverse();
void test_moda1_command_reverse1();
void test_moda4_command();