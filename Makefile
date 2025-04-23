NAME	=	minishell
SRC		=	minishell.c \
			utils.c \
			utils_list.c \
			free.c \
			split.c \
			utils_split.c \
			exec.c \
			find_exec.c \
			token_to_command.c \
			cmds_free.c \
			variable_expansion.c \
			cpy_env.c \
			in_out.c \
			process.c \
			export.c \
			export_equal.c \
			env_utils.c \
			buildin.c \
			unset.c \
			error.c \
			utils_export.c \
			utils_variable_expansion.c \
			state.c \
			copy_literals.c \
			assign_type.c \
			utils_parsing.c \
			cd.c \
			utils_process.c \
			init_redirection.c 

OBJ_DIR	=	objects
OBJ		=	$(SRC:%.c=$(OBJ_DIR)/%.o)

CC		=	cc
CFLAGS	=	-Werror -Wall -g
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
	@mkdir -p $(OBJ_DIR)
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

PHONY: all clean fclean re run

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

run: all
	@./$(NAME)
