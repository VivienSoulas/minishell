valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell

test_input
$ARG="12 34" <infile grep    '$US<ER' "$USER"|wc  -l>outfile <<append                >>append echo -n "hello world   this" expdand $ARG dont_expand '$ARG' expand "$ARG"

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

  to do:
  leaks when execve exits



  exit via ctl+D doesn't print exit
  exit needs to print exit in all cases
  env with arguments should just display simple error message - too many arguments
  exit error statements to give more detailed info
  export without any arguments should display declare -x before variables and their values