#include "pdp_f.h"
int flag_V = 0; // overflow знакое переполнение
int flag_Z = 0; // zero
int flag_N = 0; // negative
int flag_C = 0; // carry , переполнение
void do_halt()
{
    log_pdp(TRACE, "%s", "halt\n");
    for (int i = 0; i < REG_SIZE; i++)
    {
        log_pdp(TRACE, "r%d:%o ", i, reg[i]);
    }
    printf("\n");
    log_pdp(TRACE, "%s\n", "THE END!!!!!!");
    exit(0);
}
void do_mov()
{
    word res = ss.val;
    w_write(dd.adr, ss.val);
    if (res == 0)
    {
        set_flag_z();
    }
    else
        clear_flag_z();
    if ((res & 0200) == 0200)
    {
        set_flag_n();
    }
    else
        clear_flag_n();
    log_pdp(TRACE, "%s", "mov\n");
}
void do_add()
{
    word res = ss.val + dd.val;
    w_write(dd.adr, ss.val + dd.val);
    if (res == 0)
    {
        set_flag_z();
    }
    if (((res >> 8) & 0200) == 0200)
    {
        set_flag_n();
    }
    if (((res >> 8) & 0400) == 0400)
    {
        set_flag_c();
    }
    log_pdp(TRACE, "%s", "add\n");
}
void do_nothing()
{
    log_pdp(TRACE, "%s", "unknown command\n");
}
void do_sob()
{
    reg[ss.adr] -= 1;
    if (reg[ss.adr])
    {
        pc = pc - (dd.val * 2);
        log_pdp(TRACE, "%s", "sob\n");
    }
    else
        printf("\n");
    return;
}
void do_movb()
{
    byte res = ss.val;
    b_write(dd.adr, ss.val);
    clear_flag_v();
    if (res == 0)
    {
        set_flag_z();
    }
    else
        clear_flag_z();
    if ((res & 0200) == 0200)
    {
        set_flag_n();
    }
    else
        clear_flag_n();

    log_pdp(TRACE, "%s", "movb\n");
}
void do_clear()
{
    dd.val = 0;
    log_pdp(TRACE, "%s", "clear\n");
}
void clear_all_flags()
{
    flag_C = 0;
    flag_N = 0;
    flag_V = 0;
    flag_Z = 0;
}
void clear_flag_z()
{
    flag_Z = 0;
}
void clear_flag_c()
{
    flag_C = 0;
}
void clear_flag_v()
{
    flag_V = 0;
}
void clear_flag_n()
{
    flag_N = 0;
}
void set_all_flags()
{
    flag_C = 1;
    flag_N = 1;
    flag_V = 1;
    flag_Z = 1;
}
void set_flag_z()
{
    flag_Z = 1;
}
void set_flag_c()
{
    flag_C = 1;
}
void set_flag_v()
{
    flag_V = 1;
}
void set_flag_n()
{
    flag_N = 1;
}
void do_br()
{
    pc = pc + XX * 2;
    if (flag_Z != 1)
        log_pdp(TRACE, "%s %06o\n", "br", pc);
}
void do_beq()
{
    log_pdp(TRACE, "%s %06o\n", "beq", pc + XX * 2);
    if (flag_Z == 1)
    {
        do_br();
    }
}
void do_testb()
{
    byte res = dd.val;
    clear_flag_v();
    clear_flag_c();
    if (res == 0)
    {
        set_flag_z();
    }
    else
        clear_flag_z();
    if ((res & 0200) == 0200)
    {
        set_flag_n();
    }
    else
        clear_flag_n();
    log_pdp(TRACE, "%s\n", "testb");
}
void do_bpl()
{
    log_pdp(TRACE, "%s %06o\n", "bpl", pc + XX * 2);
    if (flag_N == 0)
        do_br();
}
void do_jsr()
{
    sp -= 2;
    w_write(sp, reg[registr]);
    reg[registr] = pc;
    pc = dd.adr;
    log_pdp(TRACE, "%s\n", "jsr");
}
void do_rts()
{
    pc = reg[registr];
    reg[registr] = w_read(sp);
    sp += 2;
    log_pdp(TRACE, "%s\n", "rts");
}