# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juljin <juljin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 21:53:49 by juljin            #+#    #+#              #
#    Updated: 2025/12/11 16:29:03 by juljin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════ #
#                         CONFIGURATION VARIABLES                              #
# ════════════════════════════════════════════════════════════════════════════ #

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I ../../includes
AR			= ar rcs
RM			= rm -f

# ════════════════════════════════════════════════════════════════════════════ #
#                           SOURCE FILES                                       #
# ════════════════════════════════════════════════════════════════════════════ #

# Core functions
CORE		= core/dispatcher.c \
			  core/ft_printf.c \
			  core/utils.c

# Parsing functions
PARSE		= parsing/parse.c \
			  parsing/parse_utils.c

# Printer functions
PRINT		= printers/print_char.c \
			  printers/print_hex.c \
			  printers/print_hex_utils.c \
			  printers/print_nbr.c \
			  printers/print_nbr_utils.c \
			  printers/print_nbr_utils2.c \
			  printers/print_str.c \
			  printers/print_unsign.c \
			  printers/print_unsign_utils.c

# ════════════════════════════════════════════════════════════════════════════ #
#                           OBJECT FILES                                       #
# ════════════════════════════════════════════════════════════════════════════ #

SRC			= $(CORE) $(PARSE) $(PRINT)

OBJS		= $(SRC:.c=.o)

# ════════════════════════════════════════════════════════════════════════════ #
#                           PHONY TARGETS                                      #
# ════════════════════════════════════════════════════════════════════════════ #

.PHONY: all clean fclean re

# ════════════════════════════════════════════════════════════════════════════ #
#                            DEFAULT TARGET                                    #
# ════════════════════════════════════════════════════════════════════════════ #

all: $(NAME)

# ════════════════════════════════════════════════════════════════════════════ #
#                            BUILD RULES                                       #
# ════════════════════════════════════════════════════════════════════════════ #

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Library creation
$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "✓ $(NAME) created successfully"

# ════════════════════════════════════════════════════════════════════════════ #
#                            CLEANUP RULES                                     #
# ════════════════════════════════════════════════════════════════════════════ #

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
