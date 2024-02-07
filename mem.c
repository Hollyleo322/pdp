#include "pdp_f.h"
static byte mem[MEM_SIZE];

word reg[REG_SIZE];

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
    if (a < 8)
    {
        return reg[a];
    }
    if (a % 2 == 1)
    {
        log_pdp(ERROR, "%s\n", "adress can't be odded");
        exit(1);
    }
    word w = ((word)mem[a + 1]) << 8;
    w = w | mem[a];
    return w;
}
void w_write(Adress adr, word w)
{
    if (adr < 8)
    {
        reg[adr] = w;
        return;
    }
    if (adr % 2 == 1)
    {
        log_pdp(ERROR, "%s\n", "adress can't be odded");
        exit(1);
    }
    mem[adr] = (byte)w;
    mem[adr + 1] = (byte)(w >> 8);
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