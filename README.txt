valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


TO DO:
check for unset
check for cd
check for $?

check for $ and export
handle variable expansion (echo)
	single dont expand '$USER' ==> stays $USER (single quote in order to keep special symboles as their original meanings)
	double quote to keep meaning of all char in the quote "$USER" ==> vsoulas
	

DONE:
check for consecutive operators
type assigment
check for echo
