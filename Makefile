# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juljin <juljin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 20:13:40 by juljin            #+#    #+#              #
#    Updated: 2026/04/13 16:53:24 by juljin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════ #
#                           CONFIGURATION VARIABLES                            #
# ════════════════════════════════════════════════════════════════════════════ #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3

# Detect readline location on macOS
READLINE_DIR	= $(shell brew --prefix readline 2>/dev/null)
ifneq ($(READLINE_DIR),)
    CFLAGS += -I$(READLINE_DIR)/include
    LINKFLAGS += -L$(READLINE_DIR)/lib
endif

LINKFLAGS	+= -lreadline

RM			= rm -f

INCDIR		= includes
SRCDIR		= src

LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

# ════════════════════════════════════════════════════════════════════════════ #
#                                 SOURCE FILES                                 #
# ════════════════════════════════════════════════════════════════════════════ #

# Core files always present
CORE		= main.c \
			  core/shell_utils.c \
			  core/shell_input.c \
			  core/shell_input_utils.c \
			  core/shell_exec.c

# Subsystems always present
BI			= builtins/bi_cd.c \
			  builtins/bi_cd_utils.c \
			  builtins/bi_echo.c \
			  builtins/bi_env.c \
			  builtins/bi_exit.c \
			  builtins/bi_export.c \
			  builtins/bi_export_utils.c \
			  builtins/bi_pwd.c \
			  builtins/bi_unset.c \
			  builtins/bi_utils.c

ENV			= env/env.c \
			  env/env_clean.c \
			  env/env_conversion.c \
			  env/env_minimal.c \
			  env/env_list.c \
			  env/env_search.c \
			  env/shlvl.c

SIG			= signal/sig_handler.c \
			  signal/sig_setter.c

EXP_SHARED	= expander/expand_tilde.c \
			  expander/expand_variable.c \
			  expander/expand_utils.c \
			  expander/expand_heredoc.c

LEX_SHARED	= lexer/lexer_word.c \
			  lexer/lexer_word_quote.c \
			  lexer/lexer_list.c \
			  lexer/lexer_clean.c \
			  lexer/lexer.c \
			  lexer/lexer_operator.c

EXEC_SHARED	= exec/exec_dispatch.c \
			  exec/exec_cmd_utils.c \
			  exec/exec_error.c

PAR_SHARED	= parser/parse_cmd_utils.c

ERR_SHARED	= error/err_printer.c \
			  error/op_error_utils.c

# Base SRC (always present)
SRC			= $(CORE) $(BI) $(ENV) $(SIG) $(EXP_SHARED) $(LEX_SHARED) \
			  $(EXEC_SHARED) $(PAR_SHARED) $(ERR_SHARED) \
			  exec/exec.c \
			  exec/exec_single.c \
			  exec/exec_pipeline.c \
			  exec/exec_redir_apply.c \
			  exec/exec_redir_close.c \
			  exec/exec_redir_setup.c \
			  exec/exec_cleanup.c \
			  exec/heredoc.c \
			  lexer/lexer_utils.c \
			  expander/expander.c \
			  parser/parse_cmd.c \
			  parser/parse_redir.c \
			  error/op_error.c

OBJDIR		= objs
INCFLAGS	= -I$(INCDIR) -I$(LIBFTDIR)/includes

# ════════════════════════════════════════════════════════════════════════════ #
#                                OBJECT FILES                                  #
# ════════════════════════════════════════════════════════════════════════════ #

OBJS		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# ════════════════════════════════════════════════════════════════════════════ #
#                                PHONY TARGETS                                 #
# ════════════════════════════════════════════════════════════════════════════ #

.PHONY: all clean fclean re

# ════════════════════════════════════════════════════════════════════════════ #
#                                DEFAULT TARGET                                #
# ════════════════════════════════════════════════════════════════════════════ #

all: $(NAME)

# ════════════════════════════════════════════════════════════════════════════ #
#                                 BUILD RULES                                  #
# ════════════════════════════════════════════════════════════════════════════ #

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(INCFLAGS) $(OBJS) $(LIBFT) $(LINKFLAGS) -o $@
	@echo "✓ $(NAME) created successfully"

# ════════════════════════════════════════════════════════════════════════════ #
#                                CLEANUP RULES                                 #
# ════════════════════════════════════════════════════════════════════════════ #

clean:
	@$(MAKE) -C $(LIBFTDIR) clean
	$(RM) -r objs

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re: fclean all
