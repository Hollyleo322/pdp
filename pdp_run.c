#include "pdp_f.h"
char XX = 0;
int registr = 0;
int byte_status = 0;
word check_byte = 0100000;
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
            reg[r] += 1;
            byte_status = 0; // todo += 1
        }
        if (r == 6 && byte_status == 1)
            reg[r] += 1;
        if (r == 7)
            log_pdp(TRACE, "#%06o ", res.val);
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
            byte_status = 0;
        }
        if (r == 6 && byte_status == 1)
            reg[r] += 1;
        log_pdp(TRACE, "-(R%d) ", r);
        break;
    case 5:
        reg[r] -= 2;
        res.adr = reg[r];
        res.adr = w_read(res.adr);
        res.val = w_read(res.adr);
        log_pdp(TRACE, "@-(R%d) ", r);
        break;
    case 6:
        word x = w_read(pc);
        pc += 2;
        res.adr = reg[r];
        res.adr = res.adr + x;
        res.val = w_read(res.adr);
        if (r == 7)
            log_pdp(TRACE, "%06o ", res.adr);
        else
            log_pdp(TRACE, "X(R%d) ", r);
        break;
    case 7:
        word tmp = w_read(pc);
        pc += 2;
        res.adr = reg[r];
        res.adr = res.adr + tmp;
        res.adr = w_read(res.adr);
        res.val = w_read(res.adr);
        if (r == 7)
            log_pdp(TRACE, " @%06o ", res.val);
        else
            log_pdp(TRACE, "@XR(%d) ", r);
        break;
    default:
        log_pdp(ERROR, "Mode %d not implemented yet!\n", m);
        exit(1);
        break;
    }
    return res;
}
Command cmd[] = {
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0177000, 0077000, "sob", do_sob, HAS_R | HAS_N},
    {0170000, 0110000, "movb", do_movb, HAS_SS | HAS_DD},
    {0177700, 0005000, "clear", do_clear, HAS_DD},
    {0177700, 0001400, "beq", do_beq, HAS_XX},
    {0177700, 0105700, "testb", do_testb, HAS_DD},
    {0177000, 0100000, "bpl", do_bpl, HAS_XX},
    {0177000, 0004000, "jsr", do_jsr, HAS_R | HAS_DD},
    {0177770, 0000200, "rts", do_rts, HAS_R},
    {0177000, 0000000, "br", do_br, HAS_XX},
    {0, 0, "unknown", do_nothing, NO_PARAMS}};
void run()
{
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
                if (cmd[i].params == (HAS_R | HAS_DD))
                {
                    dd = get_mr(w);
                    registr = (w >> 6) & 7;
                }
                if (cmd[i].params == HAS_R)
                    registr = (w & 7);
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