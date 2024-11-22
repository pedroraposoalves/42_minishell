#########COLORS##########
RESET			= \033[0m
BLACK			= \033[1;30m
RED				= \033[1;31m
GREEN			= \033[1;32m
YELLOW			= \033[1;33m
BLUE			= \033[1;34m
PURPLE			= \033[1;35m
CYAN			= \033[1;36m
WHITE			= \033[1;37m

##########FLAGS##########
CC				= cc
CPFLAGS			= -Wall -Wextra -Werror -g #-fsanitize=address
CPFLAGS_MAIN	= -Wall -Wextra -Werror -g -lreadline #-fsanitize=address
RM				= rm -rf
AR				= ar -rcs
MK				= --no-print-directory

##########LIBFT##########
LIBFT_PATH		= libft
LIBFT_LIB		= ${LIBFT_PATH}/libft.a
LIBFT			= -L ${LIBFT_PATH} -lft

##########FILES & FOLDERS##########
NAME			= minishell
SRC				= srcs
OBJ_DIR			= objs
BUILTINS_DIR	= builtins
CHECK_DIR		= check
ENV_DIR			= env
EXEC_DIR		= exec
PARSE_DIR		= parse
TOKEN_DIR		= tokenization
_FILES			= $(BUILTINS_DIR)/pwd $(BUILTINS_DIR)/bl_env $(BUILTINS_DIR)/echo $(BUILTINS_DIR)/unset $(BUILTINS_DIR)/exit $(BUILTINS_DIR)/cd \
				$(CHECK_DIR)/check_cmds_utils $(CHECK_DIR)/check_cmds \
				$(ENV_DIR)/env \
				$(EXEC_DIR)/exec_tre_aux $(EXEC_DIR)/exec_tree_utils $(EXEC_DIR)/exec_tree \
				$(PARSE_DIR)/create_nodes_tree $(PARSE_DIR)/parse_utils $(PARSE_DIR)/parse_utils2 \
				$(TOKEN_DIR)/get_token_amount $(TOKEN_DIR)/tokenize_aux $(TOKEN_DIR)/tokenize_utils $(TOKEN_DIR)/tokenize \
				cmp_env DEBUG_AUX expand free init_main join_tokens print_err signals utils_error

OBJS			= $(_FILES:%=%.o)
TARGET			= $(addprefix $(OBJ_DIR)/, $(OBJS))
DEPS			= includes


##########RULES##########
all				: 	$(NAME)

$(NAME)			:	${LIBFT_LIB} $(OBJ_DIR) $(TARGET) $(SRC)/main.c
					echo "[$(CYAN) Compiling $(RESET)] $(GREEN)Main$(RESET)"
					$(CC) $(CPFLAGS_MAIN) $(SRC)/main.c $(TARGET) $(LIBFT) -o $(NAME) -I $(DEPS)

					echo "$(GREEN)Done.$(RESET)"

${LIBFT_LIB}	:
					echo "[$(CYAN)Compiling$(RESET)] $(CPFLAGS) $(GREEN)LIBFT$(RESET)"
					@make bonus ${MK} -sC ${LIBFT_PATH}

$(OBJ_DIR)/%.o	:$(SRC)/%.c
					echo "[$(CYAN)Compiling$(RESET)] $(CPFLAGS) $(GREEN)$<$(RESET)"
					$(CC) $(CPFLAGS) -c $< -o $@ -I $(DEPS)

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)
					mkdir -p $(OBJ_DIR)/$(BUILTINS_DIR)
					mkdir -p $(OBJ_DIR)/$(CHECK_DIR)
					mkdir -p $(OBJ_DIR)/$(ENV_DIR)
					mkdir -p $(OBJ_DIR)/$(EXEC_DIR)
					mkdir -p $(OBJ_DIR)/$(PARSE_DIR)
					mkdir -p $(OBJ_DIR)/$(TOKEN_DIR)

clean			:
					${RM} minishell.o
					echo "[$(RED)Deleted$(RESET)] $(GREEN)MAIN$(RESET)"
					@make clean ${MK} -C ${LIBFT_PATH}
					echo "[$(RED)Deleted$(RESET)] $(GREEN)LIBFT$(RESET)"
					$(RM) $(OBJ_DIR)
					echo "[$(RED)Deleted$(RESET)] $(GREEN)OBJS$(RESET)"


fclean			: clean
					${RM} ${NAME}
					echo "[$(RED)Deleted$(RESET)] $(GREEN)${NAME}$(RESET)"
					@make fclean ${MK} -C ${LIBFT_PATH}
					echo "[$(RED)Deleted$(RESET)] $(GREEN)*.a Libs$(RESET)"

re				: fclean all

.PHONY:		all clean fclean re

.SILENT:
