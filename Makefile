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
ENV_DIR			= env
EXEC_DIR		= exec
HERE_DIR		= heredoc
INIT_DIR		= init
PARS_DIR		= parsing
SIGNALS_DIR		= signals
UTILS_DIR		= utils
HERE_DIR		= heredoc
_FILES			= $(BUILTINS_DIR)/pwd $(BUILTINS_DIR)/bl_env $(BUILTINS_DIR)/echo $(BUILTINS_DIR)/unset $(BUILTINS_DIR)/exit $(BUILTINS_DIR)/cd $(BUILTINS_DIR)/export \
				$(ENV_DIR)/env $(ENV_DIR)/cmp_env\
				$(EXEC_DIR)/exec_tre_aux $(EXEC_DIR)/exec_tree_utils $(EXEC_DIR)/exec_tree $(EXEC_DIR)/exit_signals \
				$(HERE_DIR)/heredoc \
				$(INIT_DIR)/init $(INIT_DIR)/create_nodes_tree \
				$(PARS_DIR)/check_cmds $(PARS_DIR)/tokenize_aux $(PARS_DIR)/tokenize $(PARS_DIR)/utils $(PARS_DIR)/utils2 $(PARS_DIR)/expand $(PARS_DIR)/join_tokens $(PARS_DIR)/check_cmds_utils \
			  $(SIGNALS_DIR)/signals $(SIGNALS_DIR)/signals_utils \
				$(UTILS_DIR)/sort_char_tab $(UTILS_DIR)/utils_error $(UTILS_DIR)/matrix_handle $(UTILS_DIR)/string_utils $(UTILS_DIR)/free $(UTILS_DIR)/support

OBJS			= $(_FILES:%=%.o)
TARGET			= $(addprefix $(OBJ_DIR)/, $(OBJS))
DEPS			= includes

##########RULES##########
all				: 	$(NAME)

$(NAME)			:	${LIBFT_LIB} $(OBJ_DIR) $(TARGET) $(SRC)/minishell.c
					echo "[$(CYAN) Compiling $(RESET)] $(GREEN)Main$(RESET)"
					$(CC) $(CPFLAGS) $(SRC)/minishell.c $(TARGET) $(LIBFT) -o $(NAME) -I $(DEPS) -lreadline

					echo "$(GREEN)Done.$(RESET)"

${LIBFT_LIB}	:
					echo "[$(CYAN)Compiling$(RESET)] $(CPFLAGS) $(GREEN)LIBFT$(RESET)"
					@make bonus ${MK} -sC ${LIBFT_PATH}

$(OBJ_DIR)/%.o	:$(SRC)/%.c
					echo "[$(CYAN)Compiling$(RESET)] $(CPFLAGS) $(GREEN)$<$(RESET)"
					$(CC) $(CPFLAGS) -c $< -o $@ -I $(DEPS)

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)
					mkdir -p $(OBJ_DIR)/$(INIT_DIR)
					mkdir -p $(OBJ_DIR)/$(BUILTINS_DIR)
					mkdir -p $(OBJ_DIR)/$(ENV_DIR)
					mkdir -p $(OBJ_DIR)/$(EXEC_DIR)
					mkdir -p $(OBJ_DIR)/$(HERE_DIR)
					mkdir -p $(OBJ_DIR)/$(PARS_DIR)
					mkdir -p $(OBJ_DIR)/$(SIGNALS_DIR)
					mkdir -p $(OBJ_DIR)/$(UTILS_DIR)
					mkdir -p $(OBJ_DIR)/$(HERE_DIR)

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
