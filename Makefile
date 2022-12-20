CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS =	leaks.c

HEADERS_DIR = ./

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
