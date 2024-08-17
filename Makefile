NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror  -ggdb3 -fsanitize=address

SRCS = main.c parsing.c init.c utils.c monitoring.c forks.c

OBJ = $(SRCS:.c=.o)

AR  = ar rcs

RM = rm -rf 

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o philo

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
		@$(RM) $(OBJ) 

fclean :
		@$(RM) $(OBJ) $(NAME)

re : fclean all
