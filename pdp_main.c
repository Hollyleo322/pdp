#include "pdp_f.h"
int log_level = ERROR;

void test_negative()
{
    Adress a = -100;
    byte b0 = 0x0a;
    // пишем байт, читаем байт
    b_write(a, b0);
    byte b_res = b_read(a);
    log_pdp(DEBUG, "%02hhx = %02hhx\n", b_res, b0);
}
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
    Adress a = 100;
    word s = 0xcb0a;
    w_write(a, s);
    log_pdp(DEBUG, "%04hx\n", s);
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
    if (!strcmp("-t", argv[1]))
    {
        log_level = TRACE;
    }
    load_file(argv[argc - 1]);
    /*mem_dump(0x40, 20);
    printf("\n");
    mem_dump(0x200, 0x26);*/
    // test_negative();
    //  test_mem();
    // test_w_write();
    // log_pdp(TRACE, "%o %o: %s\n");
    run();
    return 0;
}
