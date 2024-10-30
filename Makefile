# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malves-b <malves-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 17:50:15 by malves-b          #+#    #+#              #
#    Updated: 2024/10/26 12:18:04 by malves-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = minishell

FILES = $(wildcard srcs/*.c libft/*.c tokenization/*.c check/*.c)

OBJS = $(patsubst srcs/%.c, objs/srcs/%.o, $(wildcard srcs/*.c)) \
       $(patsubst libft/%.c, objs/libft/%.o, $(wildcard libft/*.c)) \
       $(patsubst check/%.c, objs/check/%.o, $(wildcard check/*.c)) \
       $(patsubst tokenization/%.c, objs/tokenization/%.o, $(wildcard tokenization/*.c))

CC = cc -g
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

GREEN = \033[1;32m
BROWN = \033[1;33m
P = \033[1;31m

TOTAL_FILES := $(words $(OBJS))
COMPILED_FILES := 0

all: create_objs $(TARGET)

create_objs:
	@mkdir -p objs/srcs objs/libft objs/tokenization objs/check

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lreadline
	@echo "$(GREEN)\nCOMPILED$(R)"

define compile_template
	@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
	@printf "$(P)\rCOMPILING: $$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES)))%%$(R)"
	@$(CC) $(CFLAGS) -c $< -o $@
endef

objs/srcs/%.o: srcs/%.c
	$(compile_template)

objs/libft/%.o: libft/%.c
	$(compile_template)

objs/tokenization/%.o: tokenization/%.c
	$(compile_template)

objs/check/%.o: check/%.c
	$(compile_template)

clean:
	@$(RM) $(OBJS)
	@echo "$(BROWN)OBJS REMOVED$(R)"

fclean: clean
	@$(RM) $(TARGET)
	@echo "$(BROWN)EXE REMOVED$(R)"

re: fclean all

.PHONY: all clean fclean re
