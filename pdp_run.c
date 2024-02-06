#include "pdp_f.h"
typedef struct
{
    word mask;
    word opcode;
    char *name;
    void (*do_func)(void);
} Command;

void do_halt()
{
    log_pdp(TRACE, "%s\n", " THE END!!!!!!");
    exit(0);
}
void do_mov()
{
    log_pdp(TRACE, "%s", "mov\n");
}
void do_add()
{
    log_pdp(TRACE, "%s", "add\n");
}
void do_nothing()
{
    log_pdp(TRACE, "%s", "unknown command\n");
}
Command cmd[] = {
    {0170000, 0060000, "add", do_add},
    {0170000, 0010000, "mov", do_mov},
    {0177777, 0000000, "halt", do_halt},
    {0, 0, "unknown", do_nothing}};
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

                ptr = cmd[i].do_func;
                ptr();
                break;
            }
        }
    }
}