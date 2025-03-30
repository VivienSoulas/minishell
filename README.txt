valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell

test_input
$ARG="12 34" <infile grep    '$US<ER' "$USER"|wc  -l>outfile <<append                >>append echo -n "hello world   this" expdand $ARG dont_expand '$ARG' expand "$ARG"


TO DO:
norm
cd


modify expansion variable:
	export VAR=Vivien
	$VAR --> Vivien
	"$VAR" --> Vivien
	'$VAR' --> $VAR


check for exit status return