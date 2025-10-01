cmake_minimum_required(VERSION 4.0)
project(shell C)

set(CMAKE_C_STANDARD 99)

add_executable(shell main.c
        cmd_quit.c
        cmd_open.c
        cmd_listopen.c
        cmd_infosys.c
        cmd_historic.c
        cmd_help.c
        cmd_getpid.c
        cmd_getcwd.c
        cmd_dup.c
        cmd_date.c
        cmd_close.c
        cmd_chdir.c
        cmd_authors.c
        trocearCadena.c
        list_file.c
        list_cmd.c
        main.h
        cmd_erase.c
        cmd_writestr.c
)
