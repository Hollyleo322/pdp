#include <stdio.h>
#include <assert.h>

typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;

#define MEM_SIZE (64 * 1024)

byte mem[MEM_SIZE];
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
    printf("%02hhx = %02hhx\n", b_res, b0);
    assert(b_res == b0);

    Adress a = 4;
    byte b1 = 0xcb;
    b0 = 0x0a;
    word w = 0xcb0a;
    b_write(a, b0);
    b_write(a + 1, b1);
    word w_res = w_read(a);
    printf("ww/br \t %04hx= %02hhx%02hhx\n", w_res, b1, b0);
    assert(w == w_res);
}
void test_w_write()
{
    Adress a = 4;
    word s = 0xcb0a;
    w_write(a, s);
    printf("%02hhx : %02hhx\n", mem[4], mem[5]);
}
int main()
{
    load_data();

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
    for (int i = 0; i < size; i++)
    {
        printf("%06o: %06o %04x", adr + i, mem[adr + i], mem[adr + i]);
        printf("\n");
    }
}