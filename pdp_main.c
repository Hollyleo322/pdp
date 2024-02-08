#include "pdp_f.h"
int log_level = ERROR;
Arg ss;
Arg dd;

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
    // load_file(argv[argc - 1]);
    /*mem_dump(0x40, 20);
    printf("\n");
    mem_dump(0x200, 0x26);*/
    // test_negative();
    //  test_mem();
    // test_w_write();
    // log_pdp(TRACE, "%o %o: %s\n");
    // run();
    // test_mov_command();
    // test_moda1_command();
    // test_moda1_command_reverse1();
    test_moda4_command();
    return 0;
}
