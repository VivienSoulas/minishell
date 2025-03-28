valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


TO DO:
check echo with multiple token ("echo hello there" should print "hello there")

check expansion variable with double quotes
check for unclosed quotes


check for exit status
norm
check for empty prompt after single cmd


cd
$? (printf actual program exit values)
	in the main loop, only exit should change exit_status in order to auit minishell


DONE:
export VAR=Vivien
$VAR --> Vivien
"$VAR" --> Vivien
'$VAR' --> $VAR

check for ""$VAR"" and "'$VAR'"
