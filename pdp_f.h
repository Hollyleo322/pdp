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