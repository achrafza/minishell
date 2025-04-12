NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
RM = rm -f

PARSE_DIR = ./parsing
EXEC_DIR = ./execution
UTILS_DIR = ./utils

SRCS = $(PARSE_DIR)/arrayallocator.c \
       $(PARSE_DIR)/commandeparser.c \
       $(PARSE_DIR)/main.c \
       $(PARSE_DIR)/parserlexer.c\
       $(PARSE_DIR)/debug.c\
       $(PARSE_DIR)/loader.c\
	$(PARSE_DIR)/p_com_split.c\
       $(PARSE_DIR)/leak_utils.c\
       $(EXEC_DIR)/env.c\
       $(EXEC_DIR)/env_utils.c\
       $(EXEC_DIR)/pwd.c\
       $(EXEC_DIR)/cd.c\
       $(EXEC_DIR)/unset.c\
       $(EXEC_DIR)/find_access.c \
       $(EXEC_DIR)/execute.c \
       $(UTILS_DIR)/ft_strcmp.c\
       $(UTILS_DIR)/ft_strchr.c\
       $(UTILS_DIR)/ft_memset.c\
       $(UTILS_DIR)/ft_split.c \
       $(UTILS_DIR)/ft_strdup.c \
       $(UTILS_DIR)/ft_strjoin.c \
       $(UTILS_DIR)/ft_strnstr.c \
       $(UTILS_DIR)/ft_strncmp.c \


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
