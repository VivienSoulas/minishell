valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


TO DO:
norm
cd

export : can only be CAP letters for names of VAR
check expansion variable with double quotes
echo $UNDEFINED to sort out



check for exit status

DONE:
export VAR=Vivien
$VAR --> Vivien
"$VAR" --> Vivien
'$VAR' --> $VAR

check for ""$VAR"" and "'$VAR'"