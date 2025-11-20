# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtereshc <dtereshc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 15:18:15 by olcherno          #+#    #+#              #
#    Updated: 2026/09/06 00:00:00 by dtereshc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                   PROJECT                                    #
# ============================================================================ #

NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
DEPFLAGS    := -MMD -MP
AR          := ar
ARFLAGS     := rcs
RM          := rm -rf

SRC_DIR     := src
OBJ_DIR     := obj
LIBFT_DIR   := libs/libft
PRINTF_DIR  := libs/libftprintf

LIBFT       := $(LIBFT_DIR)/libft.a
LIBFTPRINTF := $(PRINTF_DIR)/libftprintf.a

# ============================================================================ #
#                             PLATFORM DETECTION                               #
# ============================================================================ #
#  macOS ships libedit disguised as readline, which lacks rl_replace_line().
#  We therefore look for a real GNU readline (Homebrew) and fall back to the
#  system one on Linux, where it is already the genuine article.

UNAME       := $(shell uname -s)

RL_HINTS    := $(shell brew --prefix readline 2>/dev/null) \
               /opt/homebrew/opt/readline \
               /usr/local/opt/readline \
               $(HOME)/.brew/opt/readline \
               $(HOME)/homebrew/opt/readline
RL_PREFIX   := $(firstword $(foreach dir,$(RL_HINTS), \
                 $(if $(wildcard $(dir)/include/readline/readline.h),$(dir))))

ifneq ($(RL_PREFIX),)
 RL_INC     := -I$(RL_PREFIX)/include
 RL_LIB     := -L$(RL_PREFIX)/lib
endif

INCLUDES    := -I. -I$(SRC_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR) $(RL_INC)
LDFLAGS     := -L$(LIBFT_DIR) -L$(PRINTF_DIR) $(RL_LIB)
LDLIBS      := -lft -lftprintf -lreadline

# ============================================================================ #
#                                   SOURCES                                    #
# ============================================================================ #

SRC_CORE    := main.c main2.c main3.c main4.c utils.c signal.c \
               env_init.c do_env_array.c

SRC_LEXER   := tokenizer.c tokenizer_utils_0.c tokenizer_utils_1.c \
               tokenizer_utils_2.c

SRC_PARSER  := validate_input_0.c validate_input_1.c validate_input_2.c \
               validate_input_3.c validate_input_4.c \
               crt_cmnd_ls.c crt_cmnd_ls1.c \
               cmnd_ls_utils_0.c cmnd_ls_utils_1.c

SRC_EXPAND  := dollar_ls_0.c dollar_ls_1.c dollar_ls_2.c dollar_ls_utils.c

SRC_EXEC    := what_command.c what_command_utils.c \
               pipes.c pipes1.c pipes3.c \
               pipe_utils_0.c pipe_utils_1.c pipe_utils_2.c

SRC_REDIR   := implem_redir.c implem_redir2.c implem_redir3.c redir_utils.c \
               implem_heredoc.c process_heredocs.c

SRC_MEMORY  := free_funcs_0.c free_funcs_1.c free_funcs_2.c

SRC_BUILTIN := buildin_commands/echo_command_implementation.c \
               buildin_commands/cd_command_implementation.c \
               buildin_commands/cd_command_implementation2.c \
               buildin_commands/pwd_command_implementation.c \
               buildin_commands/export_command_implementation.c \
               buildin_commands/export_command_implementation2.c \
               buildin_commands/export_command_implementation3.c \
               buildin_commands/export_command_implementation33.c \
               buildin_commands/export_command_implementation4.c \
               buildin_commands/export_command_implementation5.c \
               buildin_commands/unset_command_implementation.c \
               buildin_commands/exit_command_implementation.c \
               buildin_commands/other_commands.c \
               buildin_commands/other_commands2.c \
               buildin_commands/other_commands22.c \
               buildin_commands/other_commands222.c \
               buildin_commands/other_commands3.c

SRC         := $(SRC_CORE) $(SRC_LEXER) $(SRC_PARSER) $(SRC_EXPAND) \
               $(SRC_EXEC) $(SRC_REDIR) $(SRC_MEMORY) $(SRC_BUILTIN)

SRCS        := $(addprefix $(SRC_DIR)/, $(SRC))
OBJS        := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEPS        := $(OBJS:.o=.d)

LIBFT_SRCS  := $(wildcard $(LIBFT_DIR)/*.c) $(wildcard $(LIBFT_DIR)/*.h)
PRINTF_SRCS := $(wildcard $(PRINTF_DIR)/*.c) $(wildcard $(PRINTF_DIR)/*.h)

# ============================================================================ #
#                                  COSMETICS                                   #
# ============================================================================ #

GREY        := \033[0;90m
RED         := \033[0;91m
GREEN       := \033[0;92m
YELLOW      := \033[0;93m
BLUE        := \033[0;94m
MAGENTA     := \033[0;95m
CYAN        := \033[0;96m
WHITE       := \033[0;97m
BOLD        := \033[1m
RESET       := \033[0m

TOTAL       := $(words $(SRC))
COUNT        = 0

# Verbose build:  make V=1
ifeq ($(V),1)
 Q          :=
else
 Q          := @
 MAKEFLAGS  += --no-print-directory
endif

# ============================================================================ #
#                                    RULES                                     #
# ============================================================================ #

.DEFAULT_GOAL := all

all: banner $(NAME)

$(NAME): $(LIBFT) $(LIBFTPRINTF) $(OBJS)
	$(Q)printf "$(CYAN)  linking   $(RESET)$(BOLD)$(NAME)$(RESET)\n"
	$(Q)$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(Q)printf "\n"
	$(Q)printf "$(GREEN)$(BOLD)   ▄▄▄▄▄▄  minishell is ready  ▄▄▄▄▄▄$(RESET)\n"
	$(Q)printf "$(GREY)   run it with  $(RESET)$(WHITE)./$(NAME)$(RESET)\n\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(Q)mkdir -p $(dir $@)
	$(Q)$(eval COUNT := $(shell echo $$(($(COUNT) + 1))))
	$(Q)printf "$(GREY)  [%3d/%3d]$(RESET) $(BLUE)compiling$(RESET) %-46s\r" \
		$(COUNT) $(TOTAL) "$<"
	$(Q)$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@ \
		|| (printf "\n$(RED)  ✗ failed: $<$(RESET)\n" && false)
	$(Q)if [ $(COUNT) -eq $(TOTAL) ]; then \
		printf "$(GREEN)  [%3d/%3d]$(RESET) $(GREEN)compiled  $(RESET)%-46s\n" \
		$(COUNT) $(TOTAL) "$(TOTAL) objects"; fi

$(LIBFT): $(LIBFT_SRCS)
	$(Q)printf "$(MAGENTA)  building  $(RESET)libft\n"
	$(Q)$(MAKE) -C $(LIBFT_DIR)

$(LIBFTPRINTF): $(PRINTF_SRCS)
	$(Q)printf "$(MAGENTA)  building  $(RESET)libftprintf\n"
	$(Q)$(MAKE) -C $(PRINTF_DIR)

banner:
	$(Q)printf "\n"
	$(Q)printf "$(CYAN)$(BOLD)"
	$(Q)printf "   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n"
	$(Q)printf "   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n"
	$(Q)printf "   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n"
	$(Q)printf "   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n"
	$(Q)printf "   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
	$(Q)printf "   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
	$(Q)printf "$(RESET)"
	$(Q)printf "$(GREY)   as beautiful as a shell  ·  42 Prague  ·  $(TOTAL) source files$(RESET)\n\n"

clean:
	$(Q)printf "$(YELLOW)  cleaning  $(RESET)object files\n"
	$(Q)$(RM) $(OBJ_DIR)
	$(Q)$(MAKE) -C $(LIBFT_DIR) clean
	$(Q)$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(Q)printf "$(YELLOW)  cleaning  $(RESET)binaries and archives\n"
	$(Q)$(RM) $(NAME)
	$(Q)$(MAKE) -C $(LIBFT_DIR) fclean
	$(Q)$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

# ---------------------------------------------------------------------------- #
#                              DEVELOPER TARGETS                               #
# ---------------------------------------------------------------------------- #

debug: CFLAGS += -g3 -DDEBUG
debug: re

fsanitize: CFLAGS += -g3 -fsanitize=address,undefined
fsanitize: LDFLAGS += -fsanitize=address,undefined
fsanitize: re

norm:
	$(Q)printf "$(BLUE)  norm      $(RESET)running norminette\n"
	$(Q)norminette $(SRC_DIR) *.h $(LIBFT_DIR) $(PRINTF_DIR) \
		|| printf "$(RED)  norminette reported errors$(RESET)\n"

run: all
	$(Q)./$(NAME)

leaks: debug
	$(Q)valgrind --leak-check=full --show-leak-kinds=all \
		--track-fds=yes --suppressions=readline.supp ./$(NAME)

info:
	$(Q)printf "$(BOLD)  target    $(RESET)$(NAME)\n"
	$(Q)printf "$(BOLD)  platform  $(RESET)$(UNAME)\n"
	$(Q)printf "$(BOLD)  compiler  $(RESET)$(CC) $(CFLAGS)\n"
	$(Q)printf "$(BOLD)  readline  $(RESET)$(if $(RL_PREFIX),$(RL_PREFIX),system)\n"
	$(Q)printf "$(BOLD)  sources   $(RESET)$(TOTAL) files\n"

help:
	$(Q)printf "\n$(BOLD)  minishell — available targets$(RESET)\n\n"
	$(Q)printf "  $(GREEN)make$(RESET)            build the shell\n"
	$(Q)printf "  $(GREEN)make clean$(RESET)      remove object files\n"
	$(Q)printf "  $(GREEN)make fclean$(RESET)     remove objects and binaries\n"
	$(Q)printf "  $(GREEN)make re$(RESET)         rebuild from scratch\n"
	$(Q)printf "  $(GREEN)make run$(RESET)        build, then launch the shell\n"
	$(Q)printf "  $(GREEN)make debug$(RESET)      rebuild with -g3 and DEBUG\n"
	$(Q)printf "  $(GREEN)make fsanitize$(RESET)  rebuild with ASan + UBSan\n"
	$(Q)printf "  $(GREEN)make leaks$(RESET)      run under valgrind\n"
	$(Q)printf "  $(GREEN)make norm$(RESET)       run norminette on the sources\n"
	$(Q)printf "  $(GREEN)make info$(RESET)       show the detected build setup\n"
	$(Q)printf "  $(GREY)make V=1 …$(RESET)      show the full command lines\n\n"

-include $(DEPS)

.PHONY: all clean fclean re banner debug fsanitize norm run leaks info help
