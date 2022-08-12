CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS =	srcs/ft_parse_format.c \
		srcs/ft_printchar.c \
		srcs/ft_printdec.c \
		srcs/ft_printf.c \
		srcs/ft_printptr.c \
		srcs/ft_printstr.c \
		srcs/ft_utohex.c \
		srcs/ft_printudec.c \
		srcs/ft_printhex.c \
		srcs/ft_itoa.c \
		srcs/ft_putchar_fd.c \
		srcs/ft_putstr_fd.c \
		srcs/ft_strlen.c \
		srcs/ft_toupper.c \
		srcs/ft_utoa.c \
		srcs/leaks.c

HEADERS_DIR = includes/

OBJS = $(SRCS:.c=.o)

NAME = libleaks.a

.c.o:
				@printf "\e[34mCompiling file %s...\e[0m\n" $<
				@$(CC) $(CFLAGS) -c -I$(HEADERS_DIR) $< -o $(<:.c=.o)

all:		$(NAME)			

$(NAME):	$(OBJS)
				@printf "\e[34mCreating library %s...\e[0m\n" ${NAME}
				@ar -crs $(NAME) $(OBJS)
				@ranlib $(NAME)

clean:
				@printf "\e[34mRemoving object files...\e[0m\n"
				@rm -f $(OBJS)

fclean:		clean
				@printf "\e[34mRemoving library...\e[0m\n"
				@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
