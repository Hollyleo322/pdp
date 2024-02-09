#include "pdp_f.h"
typedef struct
{
    word mask;
    word opcode;
    char *name;
    void (*do_func)(void);
    char params;
} Command;
word check_byte = 0100000;
int byte_status = 0;

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
    w_write(dd.adr, ss.val);
    log_pdp(TRACE, "%s", "mov\n");
}
void do_add()
{
    w_write(dd.adr, ss.val + dd.val);
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
    b_write(dd.adr, ss.val);
    log_pdp(TRACE, "%s", "movb\n");
}
void do_clear()
{
    dd.val = 0;
    log_pdp(TRACE, "%s", "clear\n");
}
Command cmd[] = {
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0177000, 0077000, "sob", do_sob, HAS_R | HAS_N},
    {0170000, 0110000, "movb", do_movb, HAS_SS | HAS_DD},
    {0177700, 0005000, "clear", do_clear, HAS_DD},
    {0, 0, "unknown", do_nothing, NO_PARAMS}};
void run()
{
    void (*ptr)(void);
    pc = 01000;

    while (1)
    {
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
                ptr = cmd[i].do_func;
                log_pdp(DEBUG, "reg[0] = %o\n", reg[0]);
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