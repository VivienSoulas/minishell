NAME	=	minishell
SRC		=	minishell.c \
			assign_type.c \
			buildin.c \
			cd.c \
			cmds_free.c \
			copy_literals.c \
			cpy_env.c \
			cpy_export.c \
			echo.c \
			env_utils.c \
			error.c \
			exec.c \
			exec_utils.c \
			exit.c \
			export.c \
			export_equal.c \
			find_exec.c \
			free.c \
			free_e.c \
			heredoc.c \
			in_out.c \
			init_redirection.c \
			parsing.c \
			process.c \
			signals.c \
			split.c \
			state.c \
			token_to_command.c \
			unset.c \
			utils.c \
			utils_delimiter.c \
			utils_export.c \
			utils_heredoc.c \
			utils_list.c \
			utils_process.c \
			utils_split.c \
			utils_token_to_cmd.c \
			utils_variable_expansion.c \
			variable_expansion.c

OBJ_DIR	=	objects
OBJ		=	$(SRC:%.c=$(OBJ_DIR)/%.o)

CC		=	cc
CFLAGS	=	-Werror -Wall -Wextra -g
RDFLAG	=	-lreadline

# ANSI color codes
BLACK	=	\033[38;2;0;0;0m
RED		=	\033[38;2;255;0;0m
GREEN	=	\033[38;2;0;128;0m
YELLOW	=	\033[38;2;255;255;0m
BLUE	=	\033[38;2;0;0;255m
LIME	=	\033[38;2;0;255;0m
RESET	=	\033[0m # No Color

# compile source files into object files in a directory
$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# LIBft library
LIBFT		=	./libft
LIBFT_LIB	=	$(LIBFT)/libft.a

# instructions to make NAME
$(NAME): $(OBJ) $(LIBFT_LIB)
	@$(CC) $(OBJ) $(LIBFT_LIB) -o $(NAME) $(RDFLAG)
	@echo "$(LIME)==========================\nSUCCESS : Program compiled\n==========================\n$(RESET)"

# instructions to compile libft
$(LIBFT_LIB):
	@make -C $(LIBFT)
	@echo "$(BLUE)libft: libft.a created$(RESET)"

PHONY: all clean fclean re val

all: $(LIBFT_LIB) $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT) clean
	@echo "$(RED)/!\ Objects files removed /!\ $(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "$(RED)/!\ Executable removed /!\ $(RESET)"

re: fclean all

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=rl.supp --track-fds=yes ./minishell
