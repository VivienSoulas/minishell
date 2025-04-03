valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell

test_input
$ARG="12 34" <infile grep    '$US<ER' "$USER"|wc  -l>outfile <<append                >>append echo -n "hello world   this" expdand $ARG dont_expand '$ARG' expand "$ARG"




TO DO:
norm
cd
check for input VAR= in copy_env/copy_str_delimiter

modify expansion variable:
        export VAR=Vivien
        $VAR --> Vivien
        "$VAR" --> Vivien
        '$VAR' --> $VAR
- echo $ should print $
                                - echo $$ should print PID
- export VAR=$USER
  echo $VAR = user variable value
- export VAR1=$USER
  export VAR2=$VAR1
  echo $VAR2 ---> USER_NAME

- export VAR="hello      world"
  echo $VAR --> hello world
  echo "$VAR" --> hello      world
- echo ""

- export Z=1 ZZ=2

(echo "HELLO"; echo "WORLD") ???

check for exit status return

cat<a2.txt >a3.txt >a4.txt