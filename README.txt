valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell



cat | cat | cat | echo hi	--> should print hi and wait
env | echo hi				--> shouldnt print a pipe

in the case of :
touch Permission
chmod 000 Permission
cat hello > Permission

(echo hi) | echo | bye 		--> break on ()
break on && and || ??


DONE :
echo hi > 1 > permission > 2 > 3 --> should stop on permission
echo hi > 1 > 2 > 3 > 4		--> should create all the files and onlu writte in the last one
CTL+C in heredoc should out of heredoc, CTL+D too, CTL+\ shouldnt do anything
CTL+C in nested minishells	--> should print new line after signal