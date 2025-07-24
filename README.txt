valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell


free memory of heredoc on CTL+C during heredoc


DONE :
cat < missing | echo hi		--> should print "file not found" AND print hi (double free !)
heredoc exit status --> 130
echo hi > 1 > permission > 2 > 3 --> should stop on permission
echo hi > 1 > 2 > 3 > 4		--> should create all the files and onlu writte in the last one
CTL+C in heredoc should out of heredoc, CTL+D too, CTL+\ shouldnt do anything
CTL+C in nested minishells	--> should print new line after signal
in the case of :
touch Permission
chmod 000 Permission
cat hello > Permission
exit 2 3 		--> shouldnt exit
echo when not in first arg:
		cat | cat | cat | echo hi	--> should print hi and wait
		env | echo hi				--> shouldnt print a pipe
echo memory leak