# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juljin <juljin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/04 13:29:07 by juljin            #+#    #+#              #
#    Updated: 2026/01/03 22:17:34 by juljin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ════════════════════════════════════════════════════════════════════════════ #
#                         CONFIGURATION VARIABLES                              #
# ════════════════════════════════════════════════════════════════════════════ #

NAME		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -I$(INCDIR)
AR			= ar rcs
RM			= rm -f

INCDIR		= includes
SRCDIR		= src
OBJDIR		= objs

# ════════════════════════════════════════════════════════════════════════════ #
#                           SOURCE FILES                                       #
# ════════════════════════════════════════════════════════════════════════════ #

# Conversion functions
CONV_SRC	= conversion/ft_atoi.c \
			  conversion/ft_atol.c \
			  conversion/ft_itoa.c \
			  conversion/ft_strtoul.c

# Character type functions
CTYPE_SRC	= ctype/ft_abs.c \
			  ctype/ft_isalnum.c \
			  ctype/ft_isalpha.c \
			  ctype/ft_isascii.c \
			  ctype/ft_isdigit.c \
			  ctype/ft_isprint.c \
			  ctype/ft_isspace.c \
			  ctype/ft_tolower.c \
			  ctype/ft_toupper.c

# Input/Output functions
IO_SRC		= io/ft_putchar_fd.c \
			  io/ft_putendl_fd.c \
			  io/ft_putnbr_fd.c \
			  io/ft_putstr_fd.c \

# List functions
LIST_SRC	= list/ft_lstadd_back.c \
			  list/ft_lstadd_front.c \
			  list/ft_lstclear.c \
			  list/ft_lstdelone.c \
			  list/ft_lstiter.c \
			  list/ft_lstlast.c \
			  list/ft_lstmap.c \
			  list/ft_lstnew.c \
			  list/ft_lstsize.c

# Memory functions
MEM_SRC		= memory/ft_bzero.c \
			  memory/ft_calloc.c \
			  memory/ft_memchr.c \
			  memory/ft_memcmp.c \
			  memory/ft_memcpy.c \
			  memory/ft_memmove.c \
			  memory/ft_memset.c

# String functions
STR_SRC		= string/ft_free_array.c \
			  string/ft_split.c \
			  string/ft_strchr.c \
			  string/ft_strdup.c \
			  string/ft_striteri.c \
			  string/ft_strjoin.c \
			  string/ft_strlcat.c \
			  string/ft_strlcpy.c \
			  string/ft_strlen.c \
			  string/ft_strmapi.c \
			  string/ft_strncmp.c \
			  string/ft_strnstr.c \
			  string/ft_strrchr.c \
			  string/ft_strtrim.c \
			  string/ft_substr.c

# Printf functions
PRINTF_CORE	= ft_printf/core/dispatcher.c \
			  ft_printf/core/ft_printf.c \
			  ft_printf/core/utils.c

PRINTF_PARSE = ft_printf/parsing/parse.c \
			   ft_printf/parsing/parse_utils.c

PRINTF_PRINT = ft_printf/printers/print_char.c \
			   ft_printf/printers/print_hex.c \
			   ft_printf/printers/print_hex_utils.c \
			   ft_printf/printers/print_nbr.c \
			   ft_printf/printers/print_nbr_utils.c \
			   ft_printf/printers/print_nbr_utils2.c \
			   ft_printf/printers/print_str.c \
			   ft_printf/printers/print_unsign.c \
			   ft_printf/printers/print_unsign_utils.c

FT_PRINTF	= $(PRINTF_CORE) $(PRINTF_PARSE) $(PRINTF_PRINT)

# Get Next Line functions
GNL			= get_next_line/get_next_line.c \
			  get_next_line/get_next_line_utils.c
# ════════════════════════════════════════════════════════════════════════════ #
#                           OBJECT FILES                                       #
# ════════════════════════════════════════════════════════════════════════════ #

SRC			= $(addprefix $(SRCDIR)/, $(CONV_SRC) $(CTYPE_SRC) $(IO_SRC) $(LIST_SRC) \
			  $(MEM_SRC) $(STR_SRC) $(FT_PRINTF) $(GNL))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

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

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compilation rules
$(OBJDIR)/%.o: $(SRCDIR)/conversion/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/ctype/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/io/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/list/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/memory/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/string/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/ft_printf/core/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/ft_printf/parsing/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/ft_printf/printers/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/get_next_line/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Library creation
$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "✓ $(NAME) created successfully"

# ════════════════════════════════════════════════════════════════════════════ #
#                            CLEANUP RULES                                     #
# ════════════════════════════════════════════════════════════════════════════ #

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all