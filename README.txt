valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell

test_input
$ARG="12 34" <infile grep    '$US<ER' "$USER"|wc  -l>outfile <<append                >>append echo -n "hello world   this" expdand $ARG dont_expand '$ARG' expand "$ARG"


TO DO:
cd
check for exit status return
expand on command to token


exec should send to echo the args it needs to print (including -n if present)
as well as the fd correstion to the pipe/redirection/stdout




done/working:
- echo $$$$
- echo $?
- export Z=$invalid
- export Z
- export Z=
- export Z=$valid Z=$invalid etc
- export VAR=$USER
  echo $VAR = user variable value
- export VAR1=$USER
  export VAR2=$VAR1
  echo $VAR2 ---> USER_NAME
- export VAR=Vivien
  $VAR --> Vivien
  "$VAR" --> Vivien
  '$VAR' --> $VAR
- echo ""
- export VAR or VAR= gives VAR=''
- echo "'$USER'"
  $USER"   -----> 'vsoulas'
- echo "''$USER''"
  $USER"   -----> ''vsoulas''
- export VAR='$USER'
  look at ft_no_expansion for export (removing the ' and ")



cat<a2.txt >a3.txt >a4.txt