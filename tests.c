#include "pdp_f.h"
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
    if (a < 8)
        log_pdp(DEBUG, "%04hx\n", reg[a]);
    else
        log_pdp(DEBUG, "%04hx\n", s);
}
void test_mov_command() // мода 0 тест add и mov
{
    word w = 0060402;
    reg[4] = 12;
    reg[2] = 5;
    cmd_parse(w);
    log_pdp(TRACE, "dd.adr=%d dd.val = %d ss.adr=%d ss.val=%d\n", dd.adr, dd.val, ss.adr, ss.val);
    log_pdp(TRACE, "reg[2] = %d", reg[2]);
}
void test_moda1_command() // мода 1 тест mov
{
    word w = 0011402;
    reg[4] = 0200;
    reg[2] = 5;
    w_write(reg[4], 35);
    cmd_parse(w);
    log_pdp(TRACE, "dd.adr=%d dd.val = %d ss.adr=%d ss.val=%d\n", dd.adr, dd.val, ss.adr, ss.val);
    log_pdp(TRACE, "reg[2] = %d", reg[2]);
}
void test_moda1_command_reverse() // мода 1 запись в память
{
    word w = 0010412;
    reg[4] = 5;
    reg[2] = 0200;
    w_write(reg[2], 35);
    cmd_parse(w);
    log_pdp(TRACE, "dd.adr=%d dd.val = %d ss.adr=%d ss.val=%d\n", dd.adr, dd.val, ss.adr, ss.val);
    log_pdp(TRACE, "res =  %d\n", w_read(reg[2]));
}
void test_moda1_command_reverse1() // мода 1 запись в память из памяти
{
    word w = 0011412;
    reg[4] = 0100;
    reg[2] = 0200;
    w_write(reg[4], 46);
    w_write(reg[2], 35);
    cmd_parse(w);
    log_pdp(TRACE, "dd.adr=%d dd.val = %d ss.adr=%d ss.val=%d\n", dd.adr, dd.val, ss.adr, ss.val);
    log_pdp(TRACE, "res =  %d\n", w_read(reg[2]));
}

void test_moda4_command()
{
    word w = 0014442;
    reg[4] = 0200;
    reg[2] = 0100;
    w_write(0176, 12);
    w_write(076, 15);
    cmd_parse(w);
    assert(12 == w_read(076));
}