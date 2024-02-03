#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;

#define MEM_SIZE (64 * 1024)
#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3

int log_level = ERROR;
byte mem[MEM_SIZE];
int set_log_level(int level);
void log_pdp(int level, const char *format, ...);
void load_file(const char *filename);
void mem_dump(Adress adr, int size);
void load_data();
void b_write(Adress adr, byte b);
byte b_read(Adress adr);
void w_write(Adress adr, word w);
word w_read(Adress a);
void test_mem()
{
    byte b0 = 0x0a;
    // пишем байт, читаем байт
    b_write(2, b0);
    byte b_res = b_read(2);
    log_pdp(DEBUG, "%02hhx = %02hhx\n", b_res, b0);
    assert(b_res == b0);

    Adress a = 4;
    byte b1 = 0xcb;
    b0 = 0x0a;
    word w = 0xcb0a;
    b_write(a, b0);
    b_write(a + 1, b1);
    word w_res = w_read(a);
    log_pdp(DEBUG, "ww/br \t %04hx= %02hhx%02hhx\n", w_res, b1, b0);
    assert(w == w_res);
}
void test_w_write()
{
    Adress a = 4;
    word s = 0xcb0a;
    w_write(a, s);
    log_pdp(DEBUG, "%02hhx : %02hhx\n", mem[4], mem[5]);
}
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        log_pdp(ERROR, "%s\n", "Using example ./a.out test.txt(file with data)");
        exit(1);
    }
    if (!strcmp("-d", argv[1]))
    {
        log_level = DEBUG;
    }
    load_file(argv[argc - 1]);
    mem_dump(0x40, 20);
    printf("\n");
    mem_dump(0x200, 0x26);
    // test_mem();
    // test_w_write();
    return 0;
}
void b_write(Adress adr, byte b)
{
    mem[adr] = b;
}
byte b_read(Adress adr)
{
    return mem[adr];
}
word w_read(Adress a)
{
    word w = ((word)mem[a + 1]) << 8;
    w = w | mem[a] & 0xFF;
    return w;
}
void w_write(Adress adr, word w)
{
    mem[adr] = (byte)w;
    mem[adr + 1] = (byte)(w >> 8);
}
void load_data()
{
    Adress a;
    byte n;
    byte b;
    while (scanf("%hx %hhx", &a, &n) != EOF)
    {
        for (byte i = 0; i < n; i++)
        {
            scanf("%hhx", &b);
            mem[a + i] = b;
        }
    }
}
void mem_dump(Adress adr, int size)
{
    for (int i = 0; i < size; i += 2)
    {
        word w = w_read(adr + i);
        log_pdp(DEBUG, "%06o: %06o %04x\n", adr + i, w, w);
    }
}
void load_file(const char *filename) // загрузка данных из файла
{
    FILE *fin = fopen(filename, "r");
    if (fin == NULL)
    {
        perror(filename);
        exit(errno);
    }
    Adress a;
    byte n;
    byte b;
    while (fscanf(fin, "%hx %hhx", &a, &n) != EOF)
    {
        for (byte i = 0; i < n; i++)
        {
            fscanf(fin, "%hhx", &b);
            mem[a + i] = b;
        }
    }
    fclose(fin);
}
void log_pdp(int level, const char *format, ...)
{
    if (log_level < level)
    {
        return;
    }
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}
int set_log_level(int level)
{
    int res = log_level;
    log_level = level;
    return res;
}