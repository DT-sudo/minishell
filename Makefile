CC = gcc
CFLAGS = -Wall -Wextra -Werror 
RFLAGS =  -lreadline
INCLUDES = -I./

# Executable name
NAME = minishell

# Dirs
SRCDIR = src
OBJDIR = obj

SRC = main.c parsing.c utils.c
OBJS = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
SRCS = $(addprefix $(SRCDIR)/,$(SRC))

all: $(NAME)

# Link the final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(RFLAGS) -o $(NAME)

# Compile source objects from src/
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re