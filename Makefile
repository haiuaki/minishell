# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sopelet <sopelet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 20:13:40 by juljin            #+#    #+#              #
#    Updated: 2026/02/05 15:17:53 by sopelet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════ #
#                           CONFIGURATION VARIABLES                            #
# ════════════════════════════════════════════════════════════════════════════ #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g3 -I$(INCDIR) -I$(LIBFTDIR)/includes
LINKFLAGS	= -lreadline

RM			= rm -f

INCDIR		= includes
SRCDIR		= src
OBJDIR		= objs

LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

# ════════════════════════════════════════════════════════════════════════════ #
#                                SOURCE FILES                                  #
# ════════════════════════════════════════════════════════════════════════════ #

CORE		= main.c

BI			= builtins/bi_cd.c \
			  builtins/bi_echo.c \
			  builtins/bi_env.c \
			  builtins/bi_exit.c \
			  builtins/bi_export.c \
			  builtins/bi_pwd.c \
			  builtins/bi_unset.c \

ENV			= env/env.c \
			  env/env_utils.c \
			  env/env_clean.c \
			  env/env_conversion.c \

SIG			= signal/signal.c

ERR			= error/err_printer.c

SRC			= $(addprefix $(SRCDIR)/, $(CORE) $(BI) $(ENV) $(SIG) $(ERR))

# ════════════════════════════════════════════════════════════════════════════ #
#                                OBJECT FILES                                  #
# ════════════════════════════════════════════════════════════════════════════ #

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

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
	$(MAKE) -C $(LIBFTDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/builtins/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/env/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/signal/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/error/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LINKFLAGS) $(OBJS) $(LIBFT) -o $@
	@echo "✓ $(NAME) created successfully"

# ════════════════════════════════════════════════════════════════════════════ #
#                                CLEANUP RULES                                 #
# ════════════════════════════════════════════════════════════════════════════ #

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) -r $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re: fclean all