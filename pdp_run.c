#include "pdp_f.h"
typedef struct
{
    word mask;
    word opcode;
    char *name;
    void (*do_func)(void);
    char params;
} Command;

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
        res.adr = reg[r];
        res.val = w_read(res.adr); // todo b_read
        reg[r] += 2;               // todo += 1
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
        reg[r] -= 2;
        res.adr = reg[r];
        res.val = w_read(res.adr);
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
Command cmd[] = {
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
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