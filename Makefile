NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
RM = rm -f

PATH1 = ./parsing
PATH2 = ./execution

SRCS = $(PATH1)/arrayallocator.c \
       $(PATH1)/commandeparser.c \
       $(PATH1)/find_access.c \
       $(PATH1)/ft_split.c \
       $(PATH1)/ft_strdup.c \
       $(PATH1)/ft_strjoin.c \
       $(PATH1)/ft_strnstr.c \
       $(PATH1)/main.c \
       $(PATH1)/parserlexer.c\
       $(PATH1)/ft_strchr.c\
       $(PATH1)/ft_memset.c\
       $(PATH1)/debug.c\
       $(PATH1)/ft_strcmp.c\
       $(PATH1)/loader.c\
	$(PATH1)/p_com_split.c\
       $(PATH1)/leak_utils.c\

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
