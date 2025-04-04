valgrind memory leaks without the readline still reacheable showing:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes --trace-children=yes ./minishell

test_input
$ARG="12 34" <infile grep    '$US<ER' "$USER"|wc  -l>outfile <<append                >>append echo -n "hello world   this" expdand $ARG dont_expand '$ARG' expand "$ARG"


export Z
export Z=$fesghr

TO DO:
norm
cd

check if is_valid function needed
check for memory leaks

modify expansion variable:
        export VAR=Vivien
        $VAR --> Vivien
        "$VAR" --> Vivien
        '$VAR' --> $VAR

- echo $$$$

- export VAR=$USER
  echo $VAR = user variable value
  
- export VAR1=$USER
  export VAR2=$VAR1
  echo $VAR2 ---> USER_NAME

- export VAR="hello      world"
  echo $VAR --> hello world
  echo "$VAR" --> hello      world

- echo ""

(echo "HELLO"; echo "WORLD") ???

check for exit status return

cat<a2.txt >a3.txt >a4.txt



pseudo code expansion variable :

function ft_variable_expansion(token, env, exit_stat):
    result = empty string
    i = 0
    state = UNQUOTED  # Possible states: UNQUOTED, SINGLE_QUOTE, DOUBLE_QUOTE

    while i < length of token.input:
        if state == UNQUOTED:
            if token.input[i] == "'":  # Enter single quotes
                state = SINGLE_QUOTE
                i++
            else if token.input[i] == '"':  # Enter double quotes
                state = DOUBLE_QUOTE
                i++
            else if token.input[i] == '$':  # Expand variable
                var_name, i = extract_variable_name(token.input, i + 1)
                var_value = get_env_value(env, var_name)
                append var_value (or empty string if not found) to result
            else:  # Regular character
                append token.input[i] to result
                i++

        else if state == SINGLE_QUOTE:
            if token.input[i] == "'":  # Exit single quotes
                state = UNQUOTED
                i++
            else:  # Literal character inside single quotes
                append token.input[i] to result
                i++

        else if state == DOUBLE_QUOTE:
            if token.input[i] == '"':  # Exit double quotes
                state = UNQUOTED
                i++
            else if token.input[i] == '$':  # Expand variable inside double quotes
                var_name, i = extract_variable_name(token.input, i + 1)
                var_value = get_env_value(env, var_name)
                append var_value (or empty string if not found) to result
            else:  # Regular character inside double quotes
                append token.input[i] to result
                i++

    replace token.input with result
    return 0