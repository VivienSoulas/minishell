valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


TO DO:
check echo with multiple token ("echo hello there" should print "hello there")



memory leak at in exit:
==91484== 4 bytes in 1 blocks are definitely lost in loss record 1 of 67
==91484==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==91484==    by 0x40393E: copy_str_delimiter (cpy_env.c:23)
==91484==    by 0x4044BD: add_export_to_envp (export.c:32)
==91484==    by 0x404468: ft_export_check (export.c:18)
==91484==    by 0x40153A: ft_parse_input (minishell.c:97)
==91484==    by 0x4013B3: main (minishell.c:60)






check expansion variable with double quotes
check for unclosed quotes


check for exit status
norm
check for empty prompt after single cmd
echo memory problem
unset memory problem

cd
$? (printf actual program exit values)
	in the main loop, only exit should change exit_status in order to auit minishell


DONE:
export VAR=Vivien
$VAR --> Vivien
"$VAR" --> Vivien
'$VAR' --> $VAR

check for ""$VAR"" and "'$VAR'"
