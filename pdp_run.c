#include "pdp_f.h"
typedef struct
{
    word mask;
    word opcode;
    char *name;
    void (*do_func)(void);
    char params;
} Command;
char XX = 0;
int byte_status = 0;
int flag_V = 0; // overflow знакое переполнение
int flag_Z = 0; // zero
int flag_N = 0; // negative
int flag_C = 0; // carry , переполнение
Arg get_mr(word w)
{
    Arg res;
    int r = w & 7;        // узнаем номер регистра
    int m = (w >> 3) & 7; // узнаем номер моды
    switch (m)
    {
    case 0:
        res.adr = r;
        res.val = reg[r];
        log_pdp(TRACE, "R%d ", r);
        break;
    case 1:
        res.adr = reg[r];
        res.val = w_read(res.adr); // todo b_read
        log_pdp(TRACE, "(R%d) ", r);
        break;
    case 2:
        if (byte_status == 0)
        {
            res.adr = reg[r];
            res.val = w_read(res.adr); // todo b_read
            reg[r] += 2;               // todo += 1
        }
        else
        {
            res.adr = reg[r];
            res.val = b_read(res.adr); // todo b_read
            reg[r] += 1;               // todo += 1
        }
        if (r == 7)
            log_pdp(TRACE, "#%o ", res.val);
        else
            log_pdp(TRACE, "(R%d)+ ", r);
        break;
    case 3:
        res.adr = reg[r];
        res.adr = w_read(res.adr);
        res.val = w_read(res.adr);
        reg[r] += 2;
        if (r == 7)
            log_pdp(TRACE, "@#%o ", res.val);
        else
            log_pdp(TRACE, "@(R%d)+ ", r);
        break;
    case 4:
        if (byte_status == 0)
        {
            reg[r] -= 2;
            res.adr = reg[r];
            res.val = w_read(res.adr);
        }
        else
        {
            reg[r] -= 1;
            res.adr = reg[r];
            res.val = b_read(res.adr);
        }
        log_pdp(TRACE, "-(R%d) ", r);
        break;
    case 5:
        reg[r] -= 2;
        res.adr = reg[r];
        res.adr = w_read(res.adr);
        res.val = w_read(res.adr);
        log_pdp(TRACE, "@-(R%d) ", r);
        break;
    default:
        log_pdp(ERROR, "Mode %d not implemented yet!\n", m);
        exit(1);
        break;
    }
    return res;
}
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
    byte res = b_read(dd.adr);
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
}
void do_bpl()
{
    log_pdp(TRACE, "%s %06o\n", "bpl", pc + XX * 2);
    if (flag_Z == 0)
        do_br();
}
Command cmd[] = {
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0177000, 0077000, "sob", do_sob, HAS_R | HAS_N},
    {0170000, 0110000, "movb", do_movb, HAS_SS | HAS_DD},
    {0177700, 0005000, "clear", do_clear, HAS_DD},
    {0177700, 0001400, "beq", do_beq, HAS_XX},
    {0177000, 0000000, "br", do_br, HAS_XX},
    {0177700, 0105700, "testb", do_testb, HAS_DD},
    {0177700, 0100000, "bpl", do_bpl, HAS_XX},
    {0, 0, "unknown", do_nothing, NO_PARAMS}};
void run()
{
    word check_byte = 0100000;
    void (*ptr)(void);
    pc = 01000;

    while (1)
    {
        unsigned char output = b_read(odata);
        if (output <= 127)
        {
            printf("%c", output);
            b_write(odata, 130);
        }
        word w = w_read(pc);
        log_pdp(TRACE, "%06o %06o: ", pc, w);
        pc += 2;
        if ((w & check_byte) == check_byte)
            byte_status = 1;
        for (int i = 0;; i++)
        {
            if ((w & cmd[i].mask) == cmd[i].opcode)
            {
                if (cmd[i].params == HAS_DD)
                {
                    dd = get_mr(w);
                }
                if (cmd[i].params == (HAS_SS | HAS_DD))
                {
                    ss = get_mr(w >> 6);
                    dd = get_mr(w);
                }
                if (cmd[i].params == (HAS_R | HAS_N))
                {
                    ss = get_mr((w & 0170777) >> 6);
                    dd.val = w & 0000077;
                }
                if (cmd[i].params == HAS_XX)
                {
                    XX = (w & 0000777) - 0000400;
                }
                ptr = cmd[i].do_func;
                ptr();
                break;
            }
        }
    }
}
void cmd_parse(word w)
{
    void (*ptr)(void);
    for (int i = 0;; i++)
    {
        if ((w & cmd[i].mask) == cmd[i].opcode)
        {
            if (cmd[i].params == 3)
            {
                ss = get_mr(w >> 6);
                dd = get_mr(w);
            }
            ptr = cmd[i].do_func;
            ptr();
            break;
        }
    }
}