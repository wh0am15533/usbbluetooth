#include <stdio.h>
#include <argtable3.h>
#include <cwalk.h>
#include "cmd_list.h"
#include "cmd_reset.h"

#define REG_EXTENDED 1
#define REG_ICASE (REG_EXTENDED << 1)

int main(int argc, char *argv[])
{
    int exitcode = 0;

    // Get the program name...
    const char *progname = NULL;
    cwk_path_get_basename(argv[0], &progname, NULL);

    // List command table
    struct arg_rex *cmd_list_str = arg_rex1(NULL, NULL, "list", NULL, REG_ICASE, "list available devices");
    struct arg_end *cmd_list_end = arg_end(20);
    void *argtable_list[] = {cmd_list_str, cmd_list_end};

    // Reset command table
    struct arg_rex *cmd_reset_str = arg_rex1(NULL, NULL, "reset", NULL, REG_ICASE, "reset available devices");
    struct arg_end *cmd_reset_end = arg_end(20);
    void *argtable_reset[] = {cmd_reset_str, cmd_reset_end};

    // Other commands
    struct arg_lit *cmd_other_help = arg_litn("h", "help", 0, 1, "display this help and exit");
    struct arg_end *cmd_other_end = arg_end(20);
    void *argtable_other[] = {cmd_other_help, cmd_other_end};

    // Verify all argtable[] entries were allocated successfully...
    if (arg_nullcheck(argtable_list) != 0 || arg_nullcheck(argtable_reset) != 0 || arg_nullcheck(argtable_other) != 0)
    {
        // NULL entries were detected, some allocations must have failed...
        printf("%s: insufficient memory\n", progname);
        exitcode = 1;
        goto exit;
    }

    // Parse
    int nerrors_list = arg_parse(argc, argv, argtable_list);
    int nerrors_reset = arg_parse(argc, argv, argtable_reset);
    int nerrors_other = arg_parse(argc, argv, argtable_other);

    // Execute the corresponding command...
    if (nerrors_list == 0)
    {
        exitcode = cmd_list();
    }
    else if (nerrors_reset == 0)
    {
        exitcode = cmd_reset();
    }
    else if (nerrors_other == 0)
    {
        if (cmd_other_help->count > 0)
        {
            printf("Usage: %s", progname);
            arg_print_syntax(stdout, argtable_list, "\n");
            printf("       %s", progname);
            arg_print_syntax(stdout, argtable_reset, "\n");
            printf("       %s", progname);
            arg_print_syntax(stdout, argtable_other, "\n");
            printf("USB Bluetooth testing program.\n");
            arg_print_glossary(stdout, argtable_list, "      %-20s %s\n");
            arg_print_glossary(stdout, argtable_reset, "      %-20s %s\n");
            arg_print_glossary(stdout, argtable_other, "      %-20s %s\n");
        }
        else
        {
            printf("Try '%s --help' for more information.\n", progname);
            exitcode = 1;
        }
    }
    else
    {
        /* We get here if the command line matched none of the possible syntaxes */
        if (cmd_list_str->count > 0)
        {
            /* here the cmd1 argument was correct, so presume syntax 1 was intended target */
            arg_print_errors(stdout, cmd_list_end, progname);
            printf("usage: %s ", progname);
            arg_print_syntax(stdout, argtable_list, "\n");
            exitcode = 1;
        }
        else
        {
            /* no correct cmd literals were given, so we cant presume which syntax was intended */
            printf("%s: missing <list|other> command.\n", progname);
            printf("usage 1: %s ", progname);
            arg_print_syntax(stdout, argtable_list, "\n");
            printf("usage 2: %s ", progname);
            arg_print_syntax(stdout, argtable_reset, "\n");
            printf("usage 3: %s ", progname);
            arg_print_syntax(stdout, argtable_other, "\n");
            exitcode = 1;
        }
    }

exit:
    /* deallocate each non-null entry in each argtable */
    arg_freetable(argtable_list, sizeof(argtable_list) / sizeof(argtable_list[0]));
    arg_freetable(argtable_reset, sizeof(argtable_reset) / sizeof(argtable_reset[0]));
    arg_freetable(argtable_other, sizeof(argtable_other) / sizeof(argtable_other[0]));

    return exitcode;
}