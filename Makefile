NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -f

SRCS = executioners/arrayallocator.c \
       executioners/commandeparser.c \
       executioners/find_access.c \
       executioners/ft_split.c \
       executioners/ft_strdup.c \
       executioners/ft_strjoin.c \
       executioners/ft_strnstr.c \
       executioners/main.c \
       executioners/parserlexer.c\
       executioners/ft_strchr.c\
       executioners/ft_memset.c\
       executioners/debug.c\
       executioners/ft_strcmp.c\
       executioners/loader.c\
	executioners/p_com_split.c\
       executioners/leak_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	$(RM) $(OBJS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 

.PHONY: all clean fclean re
