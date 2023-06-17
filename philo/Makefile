NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c \
	utils.c \
	ft_err.c \
	create_threads.c \
	routine_functions.c \
	monitor.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re