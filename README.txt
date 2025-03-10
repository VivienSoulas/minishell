valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


TO DO:
check for unset
check for cd
check for $?

check for $ and export
handle variable expansion (expand $VAR"...")
	single dont expand '$ARG' ("$ARG" and $ARG expand !!)
	single quote in order to keep special symboles as their original meanings
	double quote to keep meaning of all char in the quote except "$ARG"
	ARG="..." --> $ARG  replace it by a specifique string stated betweem quotes

DONE:
check for consecutive operators
type assigment
check for echo
