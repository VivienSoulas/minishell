valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


TO DO:
echo and echo -n
unset
export
cd
$? (printf actual program exit values)
	in the main loop, only exit should change exit_status in order to auit minishell


DONE:
export VAR=Vivien
$VAR --> Vivien
"$VAR" --> Vivien
'$VAR' --> $VAR
	to check for last '

check for ""$VAR"" and "'$VAR'"