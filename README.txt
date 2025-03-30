valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell

test_input
$ARG="12 34" <infile grep    '$US<ER' "$USER"|wc  -l>outfile <<append                >>append echo -n "hello world   this" expdand $ARG dont_expand '$ARG' expand "$ARG"


TO DO:
norm
cd

export VAR without = sign to add in env withou value

modify expansion variable:
	export VAR=Vivien
	$VAR --> Vivien
	"$VAR" --> Vivien
	'$VAR' --> $VAR


check for exit status return





today i have looked into norminette, i have normalised minishell.c, export.c, parsing.h, buildin.c
i have also looked into the env printing (if we export variable withou value they shouldnt print when we call env)
i have looked into the export rules to make sure it copies the original shell behaviour (export variable needs to start with a letter or underscore, caontains only letter, num and underscores)
i have modified the echo function for it to mimic the original one (not printing spaces at the end of the string, skipping any unasigned variables passed down like $ABC or $123 etc)
i have tried and look into potential memory leaks and fixed if i have found any
i have also looked into the different malloc fail check to make sure they give the same error message as well as closing the minishell program gracefully

i have created the export printing function (that prints env in alphabetic order and also prints the variable without set value) in order to copy the behaviour of the original shell
