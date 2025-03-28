valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


TO DO:
check echo with multiple token ("echo hello there" should print "hello there")
export with same VAR to override
		// check for already existing var name and replace its value
		// export : name=value, neeeds to split !!

check expansion variable with double quotes
check for exit status
norm




check for unclosed quotes
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

check for ""$VAR"" and "'$VAR'"