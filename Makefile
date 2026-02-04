# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juljin <juljin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 20:13:40 by juljin            #+#    #+#              #
#    Updated: 2026/01/27 01:09:27 by juljin           ###   ########.fr        #
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

<<<<<<< HEAD
BI			= builtins/bi_cd.c \
			  builtins/bi_echo.c \
			  builtins/bi_env.c \
			  builtins/bi_exit.c \
			  builtins/bi_export.c \
			  builtins/bi_pwd.c \
			  builtins/bi_unset.c \

=======
>>>>>>> 22a6687 (feat(env): implement environment parsing into linked list)
ENV			= env/env.c \
			  env/env_utils.c \
			  env/env_clean.c

SIG			= signal/signal.c

<<<<<<< HEAD
ERR			= error/err_printer.c

SRC			= $(addprefix $(SRCDIR)/, $(CORE) $(BI) $(ENV) $(SIG) $(ERR))
=======
SRC			= $(addprefix $(SRCDIR)/, $(CORE) $(ENV) $(SIG))
>>>>>>> 22a6687 (feat(env): implement environment parsing into linked list)

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

<<<<<<< HEAD
$(OBJDIR)/%.o: $(SRCDIR)/builtins/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

=======
>>>>>>> 22a6687 (feat(env): implement environment parsing into linked list)
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