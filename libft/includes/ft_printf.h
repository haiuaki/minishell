/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:58:54 by juljin            #+#    #+#             */
/*   Updated: 2025/12/04 10:27:04 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h> // for write()
# include <stdarg.h> // for va_list(), va_start(), va_end() & va_copy()

/* ------------------------------- STRUCTURE ------------------------------- */

typedef struct s_flags
{
	int	hyphen;
	int	plus;
	int	zero;
	int	width;
	int	dot;
	int	precision;
	int	blank;
	int	hash;
}		t_flags;

/* ------------------------------- FT_PRINTF ------------------------------- */

int		ft_printf(const char *str, ...);

void	dispatcher(char c, va_list *args, int *count, t_flags *f);

void	parse_flags(const char **str, va_list *args, t_flags *f);

/* ---------------------------- PRINT FUNCTIONS ---------------------------- */

int		print_char(char c, t_flags *f);
int		print_str(char *s, t_flags *f);
int		print_nbr(int nbr, t_flags *f);
int		print_unsign(unsigned int nbr, t_flags *f);
int		print_hex(unsigned long nbr, char c, t_flags *f);

/* --------------------------------- UTILS --------------------------------- */

int		is_digit(char c);
int		ft_putchar(char c);
int		ft_getlen(char *s);
int		ft_putstr(char *s);

/* ------------------------------ PARSE UTILS ------------------------------ */

void	initialiser(t_flags *f);
int		is_cspec(char c);
void	get_width(const char **str, va_list *args, t_flags *f);
int		simple_atoi(const char **str);

/* ------------------------------- HEX UTILS ------------------------------- */

int		hex_count(unsigned long nbr);
void	hex_init(unsigned long nbr, t_flags *f, int *hexlen, int *hexprefix);
int		hex_width(int hexlen, int hexfix, t_flags *f);
int		hex_padding(int hexlen, int hexfix, t_flags *f);
int		hex_zero_padding(int hexlen, int hexfix, t_flags *f);

/* ------------------------------- NBR UTILS ------------------------------- */

long	nbr_abs(int nbr);
int		nbr_count(long nb);
char	nbr_sign(int nbr, t_flags *f);
int		nbr_recursive(int nbr);
int		nbr_recursive_digits(long nb);

void	nbr_initializer(int nbr, long *nb, int *nbrlen, t_flags *f);

/* ---------------------------- UNSIGNED UTILS ----------------------------- */

int		unsign_count(unsigned int nbr);
int		unsign_recursive(unsigned int nbr);

#endif
