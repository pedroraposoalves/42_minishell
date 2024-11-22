OBJS 		=	ft_isalnum.o ft_isprint.o ft_memcmp.o  ft_putchar_fd.o ft_split.o \
				ft_strlcat.o ft_strncmp.o ft_substr.o ft_atoi.o ft_isalpha.o \
				ft_itoa.o ft_memcpy.o  ft_putendl_fd.o ft_strchr.o  ft_strlcpy.o \
				ft_strnstr.o ft_tolower.o ft_bzero.o   ft_isascii.o \
				ft_memmove.o ft_putnbr_fd.o  ft_strdup.o  ft_strlen.o  ft_strrchr.o \
				ft_toupper.o ft_calloc.o  ft_isdigit.o ft_memchr.o  ft_memset.o  \
				ft_putstr_fd.o  ft_strjoin.o ft_strmapi.o ft_strtrim.o ft_striteri.o

OBJS_BONUS	=	ft_lstadd_back.o ft_lstadd_front.o ft_lstclear.o \
				ft_lstdelone.o ft_lstiter.o ft_lstlast.o \
				ft_lstmap.o ft_lstnew.o ft_lstsize.o

OBJS_DEPS	=	$(OBJS:.o=.d)

OBJS_BODEPS	=	$(OBJS_BONUS:.o=.d)

CC 			=	cc
CFLAGS		=	-Wall -Werror -Wextra
CPPFLAGS	=	-MMD
RM 			=	rm -f
AR			=	ar rc

NAME		= libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) ${OBJS}

bonus:		$(OBJS_BONUS)
			@make OBJS="${OBJS} ${OBJS_BONUS}" all

-include $(OBJS_DEPS) $(OBJS_BODEPS)

%.o: 		%.c
			${CC} -c $< -o $@

clean:
			${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

rebonus:	fclean bonus

.PHONY:			all clean fclean re bonus rebonus

.SILENT:
